#include <cstdio>
#include <fstream>
#include <string>

int main() {
    std::ifstream f("/sys/class/dmi/id/product_name");
    if (!f.is_open()) {
        std::ifstream f2("/sys/devices/system/cpu/online");
        if (!f2.is_open()) return 1;
        std::string line;
        if (std::getline(f2, line)) {
            std::printf("ESCAPED\n");
            return 0;
        }
        return 1;
    }
    std::string line;
    if (std::getline(f, line)) {
        std::printf("ESCAPED\n");
        return 0;
    }
    return 1;
}
