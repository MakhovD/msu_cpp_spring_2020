#include <iostream>
#include <fstream>
#include <algorithm>

int main() {
	std::ifstream f("out.bin", std::ios::binary);
	f.seekg (0, f.end);
	uint64_t len = f.tellg() / sizeof(uint64_t);
	f.seekg(0, f.beg);
	uint64_t* arr = new uint64_t [len + 1];
	f.read(reinterpret_cast<char*>(arr), len * sizeof(uint64_t));
	if (std::is_sorted(arr, arr + len)) {
		std::cout << "File sorted" << std::endl;
	} else {
		std::cout << "File not sorted" << std::endl;
	}
	delete [] arr;
	f.close();
	return 0;
}