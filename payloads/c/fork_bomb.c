#include <stdio.h>
#include <unistd.h>

int main(void) {
    while (1) {
        if (fork() < 0) {
            perror("fork blocked");
            return 1;
        }
    }
    printf("ESCAPED\n");
    return 0;
}
