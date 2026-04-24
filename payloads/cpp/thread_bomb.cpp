#include <cstdio>
#include <thread>
#include <vector>

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 1000000; i++) {
        try {
            threads.emplace_back([] { while (1); });
        } catch (...) {
            return 1;
        }
    }
    std::printf("ESCAPED\n");
    return 0;
}
