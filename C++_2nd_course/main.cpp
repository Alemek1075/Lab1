#include <iostream>
#include <fstream>
#include <vector>
#include <random>

//123


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "Error while trying to open input file.\n";
        return 1;
    }
}
