#include <stdio.h>
#include <sys/resource.h>

int main(void) {
    struct rlimit r;
    int bad = 0;

    if (getrlimit(RLIMIT_FSIZE, &r) != 0 || r.rlim_cur != 1024 * 1024) {
        printf("ESCAPED fsize=%lu\n", (unsigned long)r.rlim_cur);
        bad++;
    }
    if (getrlimit(RLIMIT_NPROC, &r) != 0 || r.rlim_cur != 8) {
        printf("ESCAPED nproc=%lu\n", (unsigned long)r.rlim_cur);
        bad++;
    }
    if (getrlimit(RLIMIT_NOFILE, &r) != 0 || r.rlim_cur != 32) {
        printf("ESCAPED nofile=%lu\n", (unsigned long)r.rlim_cur);
        bad++;
    }
    if (getrlimit(RLIMIT_CORE, &r) != 0 || r.rlim_cur != 0) {
        printf("ESCAPED core=%lu\n", (unsigned long)r.rlim_cur);
        bad++;
    }

    if (bad == 0) {
        printf("CONTAINED rlimits match config\n");
    }
    return 0;
}
