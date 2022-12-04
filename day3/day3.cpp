#include <bits/stdc++.h>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <ctype.h>
#include <fstream>

size_t getPriority(char ch) {
    return isupper(ch) ? (int)ch - 38 : (int)ch - 96;
}

int day3part1() {
    // Time complexity O(n*m) amortized
    // Space complexity O(m)
    // N input size, M string size
    std::ifstream infile("./input.txt");
    std::string line;
    int sum = 0;
    while(std::getline(infile, line)) {
        size_t len = line.size();
        std::unordered_set<char> used_chs;
        std::unordered_set<char> counted_chs;
        used_chs.reserve(64);
        counted_chs.reserve(64);
        for (size_t i = 0; i < len; i++)
        {
            if (i < len / 2) {
                used_chs.emplace(line[i]);
            } else if(used_chs.count(line[i]) && !counted_chs.count(line[i])) {
                // std::cout << line[i] << " " << getPriority(line[i]) << std::endl;
                counted_chs.emplace(line[i]);
                sum += getPriority(line[i]);
            }
        }
    }
    return sum;
}

int day3part2() {
    // Time complexity O(n*m) amortized
    // Space complexity O(m)
    // N input size, M string size
    std::ifstream infile("./input.txt");
    std::string line;
    int sum = 0;
    std::unordered_map<char, int> chars;
    int line_id = 1;
    int groups = 1;
    while(std::getline(infile, line)) {
        size_t len = line.size();
        std::unordered_set<char> used_chs;
        for (size_t i = 0; i < len; i++) {
            if (used_chs.count(line[i])) continue;
            else {
                used_chs.emplace(line[i]);
                chars[line[i]]++;
                if (line_id == 3 && chars[line[i]] == 3) {
                    // std::cout << line[i] << " " << getPriority(line[i]) << std::endl;
                    if (groups == 1) {
                        /*std::cout << "Printing groups..." << std::endl;
                        for (auto it = chars.begin(); it != chars.end(); it++) {
                            std::cout << it->first << " " << it->second << std::endl;
                        }*/
                    }
                    sum += getPriority(line[i]);
                }
            }
        }
        if (line_id == 3) {
            line_id = 0;
            groups++;
            chars.clear();
        }
        line_id++;
    }
    return sum;
}



int main(void) {
    // std::cout << day3part1() << std::endl;
    std::cout << day3part2() << std::endl;
    return 0;
}