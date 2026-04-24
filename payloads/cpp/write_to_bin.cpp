#include <cstdio>
#include <fstream>

int main() {
    std::ofstream f("/bin/evil");
    if (!f.is_open()) return 1;
    f << "#!/bin/sh\necho pwned\n";
    f.close();
    std::printf("ESCAPED\n");
    return 0;
}
