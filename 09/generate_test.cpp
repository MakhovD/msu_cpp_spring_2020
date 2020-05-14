#include <iostream>
#include <fstream>


int main() {
    std::ofstream f("test", std::ios::binary);
    for (size_t i = 0; i < 5 * 1024 * 1024; ++i) {
        uint64_t r = rand();
        f.write(reinterpret_cast<const char*>(&r), sizeof(uint64_t));
    }
    f.close();
    return 0;
}