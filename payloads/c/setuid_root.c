#include <stdio.h>
#include <unistd.h>

int main(void) {
    if (setuid(0) != 0) {
        perror("setuid(0) blocked");
        return 1;
    }
    printf("ESCAPED\n");
    return 0;
}
