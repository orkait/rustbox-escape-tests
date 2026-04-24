#include <stdio.h>

int main(void) {
    FILE *f = fopen("/bin/evil", "w");
    if (!f) {
        perror("fopen /bin/evil blocked");
        return 1;
    }
    fprintf(f, "#!/bin/sh\necho pwned\n");
    fclose(f);
    printf("ESCAPED\n");
    return 0;
}
