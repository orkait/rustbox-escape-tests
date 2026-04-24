#include <cstdio>
#include <fstream>
#include <string>

int main() {
    for (int i = 0; i < 100000; i++) {
        std::string path = "/tmp/inode_" + std::to_string(i);
        std::ofstream f(path);
        if (!f.is_open()) return 1;
        f << "x";
    }
    std::printf("ESCAPED\n");
    return 0;
}
