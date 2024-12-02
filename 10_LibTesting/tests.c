#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

static jmp_buf escape;

static void
test_abort(void)
{
    longjmp(escape, 1);
}

#define BUF_ABORT test_abort()
#include "buf.h"

char* test;

#define TEST(s, x)                                                             \
    if (strcmp(s, test) == 0) {                                                \
        if (x) {                                                               \
            exit(0);                                                           \
        } else {                                                               \
            exit(1);                                                           \
        }                                                                      \
    }

int main(int argc, char** argv) {
    test = argv[1];

    /* initialization, buf_free() */
    float* a = 0;
    TEST("capacity_init", buf_capacity(a) == 0);
    TEST("size_init", buf_size(a) == 0);
    buf_push(a, 1.3f);
    TEST("size_1", buf_size(a) == 1);
    TEST("value", a[0] == (float)1.3f);
    buf_clear(a);
    TEST("clear", buf_size(a) == 0);
    TEST("clear_not_free", a != 0);
    buf_free(a);
    TEST("free", a == 0);

    /* Clearing an NULL pointer is a no-op */
    buf_clear(a);
    TEST("clear_empty", buf_size(a) == 0);
    TEST("clear_nop", a == 0);

    /* buf_push(), [] operator */
    long* ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    TEST("size_10000", buf_size(ai) == 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    TEST("match_10000", match == 10000);
    buf_free(ai);

    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
    TEST("grow_1000", buf_capacity(ai) == 1000);
    TEST("size_0_grow", buf_size(ai) == 0);
    buf_trunc(ai, 100);
    TEST("trunc_100", buf_capacity(ai) == 100);
    buf_free(ai);

    /* buf_pop() */
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    TEST("size_4", buf_size(a) == 4);
    TEST("pop_3", buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    TEST("size_3", buf_size(a) == 3);
    TEST("pop_2", buf_pop(a) == (float)1.3f);
    buf_pop(a);
    TEST("pop_1", buf_pop(a) == (float)1.2f);
    buf_pop(a);
    TEST("pop_0", buf_pop(a) == (float)1.1f);
    buf_pop(a);
    TEST("size_0_pop", buf_size(a) == 0);

    buf_free(a);
}
