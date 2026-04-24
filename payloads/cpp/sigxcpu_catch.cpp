#include <cstdio>
#include <csignal>

int main() {
    std::signal(SIGXCPU, SIG_IGN);
    while (1);
    std::printf("ESCAPED\n");
    return 0;
}
