#include <stdio.h>
#include <netdb.h>

int main(void) {
    struct addrinfo *res = NULL;
    int err = getaddrinfo("google.com", "80", NULL, &res);
    if (err != 0) {
        fprintf(stderr, "dns lookup blocked: %s\n", gai_strerror(err));
        return 1;
    }
    freeaddrinfo(res);
    printf("ESCAPED\n");
    return 0;
}
