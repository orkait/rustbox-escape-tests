#include <cstdio>
#include <unistd.h>

int main() {
    while (1) {
        pid_t p = fork();
        if (p < 0) {
            return 1;
        }
    }
    std::printf("ESCAPED\n");
    return 0;
}
