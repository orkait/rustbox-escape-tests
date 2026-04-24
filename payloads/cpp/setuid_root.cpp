#include <cstdio>
#include <unistd.h>

int main() {
    int ret = setuid(0);
    if (ret == 0 && getuid() == 0) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
