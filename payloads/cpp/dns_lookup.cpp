#include <cstdio>
#include <netdb.h>

int main() {
    struct addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo* res = nullptr;
    int ret = getaddrinfo("google.com", "80", &hints, &res);
    if (ret == 0 && res != nullptr) {
        freeaddrinfo(res);
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
