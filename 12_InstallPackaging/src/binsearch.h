#include <string.h>

/// @brief Roman integers translation table
static const char* roman_integers[] = {
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
static const char* decimal_integers[] = {
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
