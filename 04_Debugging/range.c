#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: range - prints help\n"
               "       range N - prints [0, N) in column\n"
               "       range M N - prints [M, N) in column\n"
               "       range M N S - prints [M, N) with step S in column\n"
               "Unknown arguments are ignored\n");
        return 0;
    }

    long M = 0, N = 0, S = 1;

    if (argc == 2) {
        N = strtol(argv[1], 0, 10);
    } else if (argc > 2) {
        M = strtol(argv[1], 0, 10);
        N = strtol(argv[2], 0, 10);
        if (argc > 3) {
            S = strtol(argv[3], 0, 10);
        }
    }
        
    for (long i = M; i < N; i += S) {
        printf("%ld", i);
    }
}
