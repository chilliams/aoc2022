#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const int *a, const int *b) {
    return *b - *a;
}

int main() {
    size_t elf_count = 1;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    char *ptr;
    size_t size;
    FILE *copy = open_memstream(&ptr, &size);

    while ((linelen = getline(&line, &linecap, stdin)) > 0) {
        fprintf(copy, "%s", line);
        if (strlen(line) == 1) {
            elf_count += 1;
        }
    }

    fclose(copy);

    int* cals = calloc(elf_count, sizeof(int));

    copy = fmemopen(ptr, size, "r");

    {
        int i = 0;
        while ((linelen = getline(&line, &linecap, copy)) > 0) {
            if (strlen(line) == 1) {
                i += 1;
            } else {
                int c;
                sscanf(line, "%d", &c);
                cals[i] += c;
            }
        }
    }

    fclose(copy);

    qsort(cals, elf_count, sizeof(int), (void*)cmp);

    int best3 = 0;
    for (int i = 0; i < 3; i++) {
        best3 += cals[i];
    }

    printf("%d\n", best3);

    return 0;
}
