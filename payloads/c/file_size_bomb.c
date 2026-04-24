#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("/tmp/bomb.dat", "w");
    if (!f) {
        perror("fopen /tmp/bomb.dat blocked");
        return 1;
    }
    char buf[1024 * 1024];
    memset(buf, 'A', sizeof(buf));
    size_t written = 0;
    while (written < (size_t)1024 * 1024 * 1024) {
        size_t n = fwrite(buf, 1, sizeof(buf), f);
        if (n == 0) {
            fprintf(stderr, "write blocked after %zu MB\n", written / (1024 * 1024));
            fclose(f);
            return 1;
        }
        written += n;
    }
    fclose(f);
    printf("ESCAPED\n");
    return 0;
}
