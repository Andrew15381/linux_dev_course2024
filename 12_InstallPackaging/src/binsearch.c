#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binsearch.h"

/// @brief Gettext transaltion macro
#define _(STRING) gettext(STRING)

/// @brief Starts game main loop, prints help.
int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("binsearch", INSTALL_PREFIX "/../share/locale");
    textdomain("binsearch");
    
    int use_roman = 0;
    
    // parsing exclusive args
    if (argc > 1) {
        if (strncmp(argv[1], "-r", 2) == 0) {
            use_roman = 1;
        } else if (strncmp(argv[1], "--help", 6) == 0) {
            printf(_("Number guessing game\n"
                     "Usage: binsearch [-r | --help]\n"
                     "Options:\n"
                     "-r - use roman integers (uppercase)\n"
                     "--help - print this message\n"));
            return 0;
        } else {
            printf(_("Failed parsing arguments, unknown argument: %s\n"), argv[1]);
            return 0;
        }
    }

    int low = 1;
    int high = 100;
    int mid = (low + high) / 2;

    printf(_("Pick a number between %s and %s\n"), int_to_str(low, use_roman), int_to_str(high, use_roman));

    while (low != high) {
        printf(_("Is it greater than %s (y/n)?\n"), int_to_str(mid, use_roman));

        size_t answer_size = 0;
        char* answer = 0;

        int err = 0;
        while ((err = getline(&answer, &answer_size, stdin)) != -1) {
            if (strncmp(answer, _("y"), strlen(answer) - 1) == 0) {
                low = mid + 1;
                break;
            } else if (strncmp(answer, _("n"), strlen(answer) - 1) == 0) {
                high = mid;
                break;
            } else {
                printf(_("Invalid answer, use (y/n)\n"));
            }
        }

        free(answer);

        if (err == -1) {
            printf(_("Failed reading answer\n"));
            break;
        }

        mid = (low + high) / 2;
    }

    printf(_("You picked %s\n"), int_to_str(mid, use_roman));

    return 0;
}
