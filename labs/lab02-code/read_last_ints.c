#include <stdio.h>
#include <stdlib.h>

/*
 * Read the last integers from a binary file
 *   'num_ints': The number of integers to read
 *   'file_name': The name of the file to read from
 * Returns 0 on success and -1 on error
 */
int read_last_ints(const char *file_name, int num_ints) {
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return -1;
    }
    int buffer[4096];
    size_t total_ints = 0;
    size_t n;
    while ((n = fread(buffer, sizeof(int), 4096, fp)) > 0) {
        total_ints += n;
    }
    if (ferror(fp)) {
        perror("Failed to read file");
        fclose(fp);
        return -1;
    }
    if (fseek(fp, (long) ((total_ints - num_ints) * sizeof(int)), SEEK_SET) != 0) {
        perror("Failed to find to starting position");
        fclose(fp);
        return -1;
    }
    size_t ints_read = fread(buffer, sizeof(int), (size_t) num_ints, fp);
    for (size_t i = 0; i < ints_read; ++i) {
        printf("%d\n", buffer[i]);
    }

    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <file_name> <num_ints>\n", argv[0]);
        return 1;
    }

    const char *file_name = argv[1];
    int num_ints = atoi(argv[2]);
    if (read_last_ints(file_name, num_ints) != 0) {
        printf("Failed to read last %d ints from file %s\n", num_ints, file_name);
        return 1;
    }
    return 0;
}
