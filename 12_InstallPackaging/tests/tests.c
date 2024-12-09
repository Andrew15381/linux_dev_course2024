#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/binsearch.h"

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

    TEST("roman_to_int", roman_to_int("XLIII") == 43)
    TEST("int_to_roman", strcmp(int_to_roman(43), "XLIII") == 0)
    TEST("int_to_str_decimal", strcmp(int_to_str(10, 0), "10") == 0)
    TEST("int_to_str_roman", strcmp(int_to_str(10, 1), "X") == 0)
}
