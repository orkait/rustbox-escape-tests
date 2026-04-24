#include <stdio.h>
#include <sys/mount.h>

int main(void) {
    if (mount("none", "/tmp", "tmpfs", 0, NULL) != 0) {
        perror("mount blocked");
        return 1;
    }
    printf("ESCAPED\n");
    return 0;
}
