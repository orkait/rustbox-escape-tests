#include <cstdio>
#include <sched.h>

int main() {
    int ret = unshare(CLONE_NEWUSER);
    if (ret == 0) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
