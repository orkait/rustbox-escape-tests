#include <stdio.h>
#include <signal.h>

int main(void) {
    signal(SIGXCPU, SIG_IGN);
    signal(SIGKILL, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    while (1);
    printf("ESCAPED\n");
    return 0;
}
