#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

int main(void) {
    struct utsname u;
    if (uname(&u) != 0) {
        printf("ESCAPED uname failed\n");
        return 0;
    }
    if (strcmp(u.nodename, "rustbox-sandbox") == 0) {
        printf("CONTAINED nodename=rustbox-sandbox\n");
    } else {
        printf("ESCAPED nodename=%s\n", u.nodename);
    }
    return 0;
}
