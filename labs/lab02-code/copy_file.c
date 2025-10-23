#include <stdio.h>

#define BUF_SIZE 4096

/*
 * Copy the contents of one file into another file
 *   source_file: Name of the source file to copy from
 *   dest_file: Name of the destination file to copy to
 * The destination file is overwritten if it already exists
 * Returns 0 on success and -1 on error
 */
int copy_file(const char *source_file, const char *dest_file) {
    FILE *src = fopen(source_file, "rb");
    if (src == NULL) {
        printf("Failed to open source file %s\n", source_file);
        return -1;
    }
    FILE *dst = fopen(dest_file, "wb");
    if (dst == NULL) {
        printf("Failed to open destination file %s\n", dest_file);
        fclose(src);
        return -1;
    }
    char buffer[BUF_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUF_SIZE, src)) > 0) {
        size_t bytesWritten = fwrite(buffer, 1, bytesRead, dst);
        if (bytesWritten < bytesRead) {
            printf("Error writing to dst file");
            fclose(src);
        }
    }
    fclose(src);
    fclose(dst);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <source> <dest>\n", argv[0]);
        return 1;
    }

    if (copy_file(argv[1], argv[2]) != 0) {
        return 1;
    }
    return 0;
}
