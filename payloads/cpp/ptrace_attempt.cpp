#include <cstdio>
#include <sys/ptrace.h>

int main() {
    long ret = ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
    if (ret == 0) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
