#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*unlink_t)(const char* pathname);

int unlink(const char* pathname) {
    if (strstr(pathname, "PROTECT") != NULL) {
        return 0;
    }
    
    unlink_t unlink_func = dlsym(RTLD_NEXT, "unlink");

    return unlink_func(pathname);
}
