#include <stdio.h>
#include <unistd.h>

int main(void) {
    if (setgid(0) != 0) {
        perror("setgid(0) blocked");
        return 1;
    }
    printf("ESCAPED\n");
    return 0;
}
