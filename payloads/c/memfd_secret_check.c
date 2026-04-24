#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(void) {
    long fd = syscall(447, 0);
    if (fd == -1 && errno == EPERM) {
        printf("CONTAINED memfd_secret EPERM\n");
    } else if (fd == -1 && errno == ENOSYS) {
        printf("CONTAINED memfd_secret ENOSYS\n");
    } else if (fd == -1) {
        printf("CONTAINED memfd_secret errno=%d\n", errno);
    } else {
        printf("ESCAPED memfd_secret fd=%ld\n", fd);
    }
    return 0;
}
