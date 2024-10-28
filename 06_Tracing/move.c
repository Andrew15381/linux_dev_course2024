#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


int log_system_error(const char* msg) {
  perror(msg);
  return errno;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        return 1;
    }

    const char* infile = argv[1];
    const char* outfile = argv[2];

    struct stat infile_stat;
    if (stat(infile, &infile_stat) == -1) {
        return log_system_error("Unable to stat infile");
    }

    if (!S_ISREG(infile_stat.st_mode)) {
        fprintf(stderr, "Infile is not regular");
        return 2;
    }

    struct stat outfile_stat;
    if (stat(outfile, &outfile_stat) != -1) {
        if (!S_ISREG(outfile_stat.st_mode)) {
            fprintf(stderr, "Outfile exists, but is not regular");
            return 3;
        }

        if (infile_stat.st_ino == outfile_stat.st_ino) {
            fprintf(stderr, "Infile and oufile are the same");
            return 4;
        }
    }

    int infile_fd = open(infile, O_RDONLY);
    if (infile_fd == -1) {
        return log_system_error("Unable to open infile");
    }

    int outfile_fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if (outfile_fd == -1) {
        return log_system_error("Unable to open outfile");
    }

    if (infile_stat.st_size != 0) {
        if (pwrite(outfile_fd, "", 1, infile_stat.st_size - 1) == -1) {
            return log_system_error("Unable to resize outfile");
        }

        char* infile_map = mmap(0, infile_stat.st_size, PROT_READ, MAP_SHARED, infile_fd, 0);
        if (infile_map == MAP_FAILED) {
            return log_system_error("Unable to map infile");
        }

        char* outfile_map = mmap(0, infile_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, outfile_fd, 0);
        if (outfile_map == MAP_FAILED) {
            return log_system_error("Unable to map outfile");
        }

        memcpy(outfile_map, infile_map, infile_stat.st_size);

        if (munmap(infile_map, infile_stat.st_size) == -1) {
            return log_system_error("Unable to unmap infile");
        }

        if (munmap(outfile_map, infile_stat.st_size) == -1) {
            return log_system_error("Unable to unmap outfile");
        }
    }

    if (close(infile_fd) == -1) {
        return log_system_error("Unable to close infile");
    }

    if (close(outfile_fd) == -1) {
        return log_system_error("Unable to close outfile");
    }

    if (unlink(infile) == -1) {
        return log_system_error("Unable to unlink infile");
    }

    return 0;
}

