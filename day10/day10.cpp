#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <utility>

#define WIDTH 40
#define HEIGHT 6

// make cout and cin as fast as stdio
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();


long check(const int reg, const int num, const int cycle, std::string &command) {
    if (cycle == num || (cycle + 1 == num && command.compare("noop") != 0)) {
        return reg * num;
    } else {
        return 0;
    }
}

bool checkSpritePixel(int pixel_x, int sprite) {
    // sprite's middle position and pixel
    return abs(sprite - pixel_x) <= 1;
}

std::pair<int, int> unravel(const int pixel) {
    int j = pixel % WIDTH;
    int i = pixel / WIDTH;
    return std::make_pair(i, j);
}


void draw(const int pixel, const int sprite) {
    // pixel == cycle
    auto pr = unravel(pixel);
    // std::cout << pr.first << " " << pr.second << std::endl;
    if (checkSpritePixel(pr.second, sprite)) {
        std::cout << "#";
    } else {
        std::cout << ".";
    }
    if (pr.second == WIDTH - 1) {
        std::cout << std::endl;
    }
}

void handleDrawing(const int cycle, const int reg, const std::string &command) {
    draw(cycle, reg);
    if (command.compare("noop") != 0) {
        draw(cycle+1, reg);
    }
}


void day10(char* test_file) {
    std::ifstream infile(test_file);
    std::string command, previous_command;
    long long signal_strength = 0;
    int reg = 1, cycle = 1; // reg = center of the sprite
    while(std::getline(infile, command)) {
        handleDrawing(cycle - 1, reg, command);
        signal_strength += check(reg, 20, cycle, command);
        signal_strength += check(reg, 60, cycle, command);
        signal_strength += check(reg, 100, cycle, command);
        signal_strength += check(reg, 140, cycle, command);
        signal_strength += check(reg, 180, cycle, command);
        signal_strength += check(reg, 220, cycle, command);
        std::string comm;
        std::istringstream iss(command);
        iss >> comm;
        if (comm.compare("noop") != 0) {
            int val;
            iss >> val;
            reg += val;
            cycle += 2;
        } else {
            ++cycle;
        }
        previous_command = command;
    }
    std::cout << "Part1: " << signal_strength << std::endl;
}



int main(int argc, char* argv[]) {
    day10(argv[1]);
    return 0;
}