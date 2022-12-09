#include <bits/stdc++.h>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <unordered_set>

#define NUM_KNOTS 10

struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);

    if (hash1 != hash2) return hash1 ^ hash2;
    else return hash1;
  }
};

// make cout and cin as fast as stdio
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();

bool areTouching(std::pair<int, int> &head, std::pair<int, int> &tail) {
    return abs(head.first - tail.first) <=1 && abs(head.second - tail.second) <= 1;
}

// returns false if no update was required, true otherwisw
bool compareAndAdjust(std::pair<int, int> &head, std::pair<int, int> &tail) {
    if (areTouching(head, tail)) {
        return false; // check if they are touching
    }
    bool sameRow = head.second == tail.second; // in the same row
    bool sameCol = head.first == tail.first; // in the same col
    if (sameRow) {
        if (head.first > tail.first) { // head is right to the tail
            tail.first += 1;
        } else { // head must be left to the tail
            tail.first -= 1;
        }
    } else if (sameCol) {
        if (head.second > tail.second) { // head is above tail
            tail.second += 1;
        } else { // head must be below tail
            tail.second -= 1;
        }
    } else { // some diagonal things
        if (head.first > tail.first && head.second > tail.second) { // head is top right to the tail
            tail.first += 1;
            tail.second += 1;
        } else if (head.first < tail.first && head.second > tail.second) { // head is top left to the tail
            tail.first -= 1;
            tail.second += 1;
        } else if (head.first < tail.first && head.second < tail.second) { // head is down left to the tail
            tail.first -= 1;
            tail.second -= 1;
        } else if (head.first > tail.first && head.second < tail.second) { // head is down right to the tail
            tail.first += 1;
            tail.second -= 1;
        }
    }
    return true;
}

void printAllPositions(std::vector<std::pair<int, int>> &knots) {
    for (int i = 0; i < NUM_KNOTS; ++i) {
        std::cout << "(" << knots[i].first << " " << knots[i].second << ")";
        if (i != NUM_KNOTS - 1) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}


void parseCommandPart2(const std::string &command, std::vector<std::pair<int, int>> &knots, std::unordered_set<std::pair<int, int>, hash_pair> &tail_positions) {
    std::string direction;
    int steps;
    std::istringstream iss(command);
    iss >> direction >> steps;
    std::pair<int, int> &head = knots.front();
    for (int i = 0; i < steps; ++i) {
        if (direction == "R") {
            head.first += 1;
        } else if (direction == "L") {
            head.first -= 1;
        } else if (direction == "U") {
            head.second += 1;
        } else {
            head.second -= 1;
        }
        for (int j = 0; j < NUM_KNOTS - 1; ++j) {
            std::pair<int, int> &local_head = knots[j], &local_tail = knots[j+1];
            if (!compareAndAdjust(local_head, local_tail)) break; // if no update was necessary then continue;
        }
        tail_positions.emplace(knots[NUM_KNOTS-1]);
    }
}


void parseCommandPart1(const std::string &command, std::pair<int, int> &head, std::pair<int, int> &tail, std::unordered_set<std::pair<int, int>, hash_pair> &tail_positions ) {
    std::string direction;
    int steps;
    std::istringstream iss(command);
    iss >> direction >> steps;
    for (int i = 0; i < steps; ++i) {
        if (direction == "R") {
            head.first += 1;
        } else if (direction == "L") {
            head.first -= 1;
        } else if (direction == "U") {
            head.second += 1;
        } else {
            head.second -= 1;
        }
        compareAndAdjust(head, tail);
        tail_positions.emplace(tail);
    }
}


void day9part1(char* test_file) {
    std::ifstream infile(test_file);
    std::string command;
    std::pair<int, int> head = {0, 0}, tail = {0, 0};
    std::unordered_set<std::pair<int, int>, hash_pair> tail_positions;
    while (std::getline(infile, command)) {
        parseCommandPart1(command, head, tail, tail_positions);
    }
    std::cout << "Part1: " << tail_positions.size() << std::endl;
}

void day9part2(char* test_file) {
    std::ifstream infile(test_file);
    std::string command;
    std::unordered_set<std::pair<int, int>, hash_pair> tail_positions;
    std::vector<std::pair<int, int>> knots;
    for (int i = 0; i < NUM_KNOTS; ++i) {
        knots.push_back({0, 0});
    }
    while (std::getline(infile, command)) {
        parseCommandPart2(command, knots, tail_positions);
    }
    std::cout << "Part2: " << tail_positions.size() << std::endl;
}


int main(int argc, char* argv[]) {
    // day9part1(argv[1]);
    day9part2(argv[1]);
    return 0;
}