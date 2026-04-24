#include <cstdio>
#include <vector>

int main() {
    std::vector<char> v;
    while (1) {
        v.push_back('A');
        v.resize(v.size() * 2);
    }
    std::printf("ESCAPED\n");
    return 0;
}
