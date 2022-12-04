#include <bits/stdc++.h>
#include <fstream>
#include <string>


bool checkInclusion(int a, int b, int c, int d) {
    // O(1)
    // a and b are for the first range, c and d for the second range
    if ((c >= a && d <= b) || (a >= c && b <= d)) return true;
    return false;
}

bool checkOverlap(int a, int b, int c, int d) {
    // O(1)
    if ((c >= a && c <= b) || (a >= c && a <= d)) return true;
    return false;
}


int day4part(uint8_t part) {
    // O(n)
    std::ifstream infile("./test.txt");
    std::string line;
    int pairs = 0;
    while(std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string r1, r2;
        std::getline(ss, r1, ',');
        std::getline(ss, r2, ',');
        std::stringstream ssr1(r1);
        std::stringstream ssr2(r2);
        std::string as, bs, cs, ds;
        std::getline(ssr1, as, '-');
        std::getline(ssr1, bs, '-');
        std::getline(ssr2, cs, '-');
        std::getline(ssr2, ds, '-');
        int a = stoi(as), b = stoi(bs), c = stoi(cs), d = stoi(ds);
        if (part == 1 && checkInclusion(a, b, c, d)) {
            pairs++;
        }
        if (part == 2 && checkOverlap(a, b, c, d)) {
            pairs++;
        }
    }
    return pairs;
}


int main(void) {
    std::cout << day4part(1) << std::endl;
    std::cout << day4part(2) << std::endl;

    return 0;
}