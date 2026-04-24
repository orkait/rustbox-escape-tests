#include <stdio.h>
#include <string.h>

extern char **environ;

int main(void) {
    const char *forbidden_substrs[] = {
        "RUSTBOX_", "TOKEN", "SECRET", "PASSWORD",
        "AWS_", "CF_", "DATABASE_URL", "REDIS_URL",
        NULL,
    };

    int leaks = 0;
    for (char **e = environ; *e; e++) {
        for (int i = 0; forbidden_substrs[i]; i++) {
            if (strstr(*e, forbidden_substrs[i]) != NULL) {
                printf("LEAK %s\n", *e);
                leaks++;
                break;
            }
        }
    }

    if (leaks == 0) {
        printf("CONTAINED no parent env secrets present\n");
    } else {
        printf("ESCAPED %d leaked env vars\n", leaks);
    }
    return 0;
}
