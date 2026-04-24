#include <stdio.h>
#include <sys/ptrace.h>

int main(void) {
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        perror("ptrace blocked");
        return 1;
    }
    printf("ESCAPED\n");
    return 0;
}
