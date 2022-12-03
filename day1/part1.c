#include <stdio.h>
#include <string.h>

int main() {
    int elf = 0;
    int most = 0;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, stdin)) > 0) {
        if (strlen(line) == 1) {
            if (elf > most) {
                most = elf;
            }
            elf = 0;
        } else {
            int c;
            sscanf(line, "%d", &c);
            elf += c;
        }
    }
    printf("%d\n", most);
    return 0;
}
