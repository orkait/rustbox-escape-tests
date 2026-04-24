#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

int main(void) {
    if (unshare(CLONE_NEWUSER) != 0) {
        perror("unshare CLONE_NEWUSER blocked");
        return 1;
    }
    printf("ESCAPED\n");
    return 0;
}
