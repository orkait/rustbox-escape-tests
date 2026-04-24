#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t total = 0;
    while (1) {
        void *p = malloc(1024 * 1024);
        if (!p) {
            fprintf(stderr, "malloc blocked after %zu MB\n", total / (1024 * 1024));
            return 1;
        }
        memset(p, 0x41, 1024 * 1024);
        total += 1024 * 1024;
    }
    printf("ESCAPED\n");
    return 0;
}
