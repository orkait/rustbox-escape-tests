#include <stdio.h>
#include <unistd.h>

int main(void) {
    for (int i = 0; i < 20; i++) {
        if (chdir("..") != 0) {
            perror("chdir blocked");
            return 1;
        }
    }
    FILE *f = fopen("etc/passwd", "r");
    if (!f) {
        perror("fopen etc/passwd blocked after chroot escape");
        return 1;
    }
    char buf[4096];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[n] = '\0';
    printf("ESCAPED\n%s\n", buf);
    return 0;
}
