#include <stdio.h>

int main(void) {
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) {
        perror("fopen /proc/cpuinfo blocked");
        return 1;
    }
    char buf[4096];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[n] = '\0';
    printf("ESCAPED\n%s\n", buf);
    return 0;
}
