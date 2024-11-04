#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <rhash.h>
#include <errno.h>

#define MAX_DIGEST_SIZE 64
#define MAX_OUTPUT_SIZE 130

#ifdef ENABLE_READLINE
#include <readline/readline.h>

int iterate(char** line) {
    *line = readline(NULL);
    return *line != NULL;
}
#else
int iterate(char** line) {
    size_t len = 0;
    return getline(&line, len, stdin) != -1;
}
#endif

int main(int argc, char** argv) {
    unsigned char digest[MAX_DIGEST_SIZE];
    char output[MAX_OUTPUT_SIZE];

    rhash_library_init();

    char* line;
    char sep = ' ';
    char* hash_str;
    char* param_str;
    int hash_type;
    int output_type;
    while(iterate(&line)) {
        hash_str = strtok(line, &sep);
        param_str = strtok(NULL, &sep);

        if (hash_str == NULL || param_str == NULL) {
            fprintf(stderr, "Failed parsing command\n");
            continue;
        }

        if (strcasecmp(hash_str, "sha1") == 0) {
            hash_type = RHASH_SHA1;
        } else if (strcasecmp(hash_str, "md5") == 0) {
            hash_type = RHASH_MD5;
        } else if (strcasecmp(hash_str, "tth") == 0) {
            hash_type = RHASH_TTH;
        } else {
            fprintf(stderr, "Unknown hashing function\n");
            continue;
        }

        if(isupper(hash_str[0])) {
            output_type = RHPR_HEX;
        } else {
            output_type = RHPR_BASE64;
        }

        if (param_str[0] == '"') {
            ++param_str;
            size_t len = strlen(param_str) - 1;
            param_str[len] = '\0';
            if(rhash_msg(hash_type, param_str, len, digest) < 0) {
                fprintf(stderr, "Failed hashing message\n");
                continue;
            }
        } else {
            if(rhash_file(hash_type, param_str, digest) < 0) {
                fprintf(stderr, "Failed hashing file: %s\n", strerror(errno));
                continue;
            }
        }
        
        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type), output_type);
        printf("%s\n", output);

        free(line);
    }

    return 0;
}
