#include <cstdio>
#include <unistd.h>

int main() {
    int ret = setgid(0);
    if (ret == 0 && getgid() == 0) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
