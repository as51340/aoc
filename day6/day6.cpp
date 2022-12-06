#include <string>
#include <fstream>
#include <unordered_set>
#include <iostream>

int day6(int diffs, std::string test_file) {
    std::ifstream infile(test_file);
    std::string line;
    std::getline(infile, line);
    int line_size = line.size();
    for (int i = diffs-1; i < line_size; i++) {
        std::unordered_set<char> seen;
        seen.reserve(32); // no need to reserve memory several times
        bool duplicates = false;
        for (int j = i - diffs + 1; j <= i; j++) {
            if (!seen.emplace(line[j]).second) {
                duplicates = true;
                break;
            }
        }
        if (!duplicates) return i+1;
    }
    return -1;
}


int main(int argc, char* argv[]) {
    std::cout << day6(14, argv[1]) << std::endl;
    return 0;
}