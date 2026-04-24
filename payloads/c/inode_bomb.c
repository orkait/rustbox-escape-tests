#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char path[256];
    int count = 0;
    for (int i = 0; i < 100000; i++) {
        snprintf(path, sizeof(path), "/tmp/inode_%d", i);
        int fd = open(path, O_CREAT | O_WRONLY, 0644);
        if (fd < 0) {
            fprintf(stderr, "inode bomb blocked after %d files\n", count);
            return 1;
        }
        close(fd);
        count++;
    }
    printf("ESCAPED\n");
    return 0;
}
