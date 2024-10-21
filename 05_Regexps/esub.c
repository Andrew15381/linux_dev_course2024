#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10
#define ERRSIZE 128

void print_err(int err, regex_t* regex, char* err_msg) {
    regerror(err, regex, err_msg, ERRSIZE);
    fprintf(stderr, "%s\n", err_msg);
}

void print_bag(char* text, regmatch_t* bag) {
    printf("%.*s", bag->rm_eo - bag->rm_so, text + bag->rm_so);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regexp> <pattern> <text>\n", argv[0]);
        return 0;
    }

    char* regexp = argv[1];

    char* pattern = argv[2];
    int pattern_len = strlen(pattern);

    char* text = argv[3];
    int text_len = strlen(text);

    int err;
    char err_msg[ERRSIZE];

    regex_t regex;
    err = regcomp(&regex, argv[1], REG_EXTENDED);
    if (err) {
        print_err(err, &regex, err_msg);
        return 0;
    }

    regmatch_t bags[MAXGR];
    err = regexec(&regex, argv[3], MAXGR, bags, 0);
    if (err) {
        if (err == REG_NOMATCH) {
            printf("%s\n", argv[3]);
        } else {
            print_err(err, &regex, err_msg);
        }
        regfree(&regex);
        return 0;
    }

    printf("%.*s", bags[0].rm_so, text);

    for (int j = 0; j < pattern_len; ++j) {
        if (j < pattern_len - 1 && pattern[j] == '\\') {
            char next = pattern[j + 1];
            if ('0' <= next && next <= '9') {
                int bg = pattern[j + 1] - '0';
                if (bags[bg].rm_so == -1) {
                    fprintf(stderr, "Unknown group, bg=%d\n", bg);
                    regfree(&regex);
                    return 0;
                }
                print_bag(text, &bags[bg]);
                ++j;
            } else if (next == '\\') {
                putchar('\\');
                ++j;
            }
        } else {
            putchar(pattern[j]);
        }
    }
    
    printf("%.*s\n", text_len - bags[0].rm_eo + 1, text + bags[0].rm_eo);

    regfree(&regex);
    return 0;
}
