#include <cstdio>
#include <fstream>
#include <string>

int main() {
    std::ofstream f("/tmp/bomb");
    if (!f.is_open()) return 1;
    std::string chunk(1024 * 1024, 'A');
    for (int i = 0; i < 10240; i++) {
        f << chunk;
        if (f.fail()) return 1;
    }
    f.close();
    std::printf("ESCAPED\n");
    return 0;
}
