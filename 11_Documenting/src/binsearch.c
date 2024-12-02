#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Gettext transaltion macro
#define _(STRING) gettext(STRING)

/// @brief Roman integers translation table
const char* roman_integers[] = {
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII",
    "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII",
    "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI",
    "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX",
    "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII",
    "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII",
    "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII",
    "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV",
    "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII",
    "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX",
    "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII",
    "XCIX", "C"
};

/// @brief Decimal integers translation table
const char* decimal_integers[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13",
    "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25",
    "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37",
    "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61",
    "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73",
    "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85",
    "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97",
    "98", "99", "100"
};

/// @brief Converts decimal to roman.
/// @param i Decimal int (between 1 and 100).
/// @return Roman int.
const char* int_to_roman(int i) {
    return roman_integers[i - 1];
}

/// @brief Converts roman to decimal.
/// @param roman Roman int.
/// @return Decimal int (between 1 and 100, or -1 on failure).
int roman_to_int(const char* roman) {
    for (int i = 0; i < 100; ++i) {
        if (strcmp(roman_integers[i], roman) == 0) {
            return i + 1;
        }
    }
    return -1;
}

/// @brief Converts integer to string.
/// @param i Integer.
/// @param use_roman Whether to use roman or decimal.
/// @return String representation.
const char* int_to_str(int i, int use_roman) {
    if (use_roman) {
        return int_to_roman(i);
    } else {
        return decimal_integers[i - 1];
    }
}

/// @brief Starts game main loop, prints help.
int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("binsearch", "../share/locale");
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
