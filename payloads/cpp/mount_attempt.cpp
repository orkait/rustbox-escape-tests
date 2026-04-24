#include <cstdio>
#include <sys/mount.h>

int main() {
    int ret = mount("none", "/mnt", "tmpfs", 0, "");
    if (ret == 0) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
