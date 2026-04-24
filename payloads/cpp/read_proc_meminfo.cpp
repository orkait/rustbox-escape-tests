#include <cstdio>
#include <fstream>
#include <string>

int main() {
    std::ifstream f("/proc/meminfo");
    if (!f.is_open()) return 1;
    std::string line;
    if (std::getline(f, line)) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
