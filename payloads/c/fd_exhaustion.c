#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(void) {
    int count = 0;
    while (1) {
        int fd = open("/dev/null", O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "fd exhaustion hit after %d fds: %s\n", count,
                    errno == EMFILE ? "EMFILE" : "other error");
            return 1;
        }
        count++;
    }
    printf("ESCAPED\n");
    return 0;
}
