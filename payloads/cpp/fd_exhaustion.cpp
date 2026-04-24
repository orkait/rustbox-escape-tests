#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int count = 0;
    while (1) {
        int fd = open("/dev/null", O_RDONLY);
        if (fd < 0) return 1;
        count++;
        if (count > 1000000) {
            std::printf("ESCAPED\n");
            return 0;
        }
    }
}
