#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <bits/stdc++.h>

struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);

    if (hash1 != hash2) return hash1 ^ hash2;
    else return hash1;
  }
};

int day2part2() {
  // A = rock
  // B = paper
  // C = scissors
  // X = rock, lose
  // Y = paper, draw
  // Z = scissors, win
  // Time complexity: O(n)
  // Space complexity: O(1)
  std::ifstream infile("./input.txt");
  std::string line;
  
  std::unordered_map<std::pair<char, char>, int, hash_pair> win_rounds = {
  {{'A', 'X'}, 0 + 3},
  {{'A', 'Y'}, 3 + 1},
  {{'A', 'Z'}, 6 + 2},
  {{'B', 'X'}, 0 + 1},
  {{'B', 'Y'}, 3 + 2},
  {{'B', 'Z'}, 6 + 3},
  {{'C', 'X'}, 0 + 2},
  {{'C', 'Y'}, 3 + 3},
  {{'C', 'Z'}, 6 + 1}
  };
  int points = 0;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    char player, status;
    iss >> player >> status;
    points += win_rounds[{player, status}];
  }
  return points;
}

int day2part1() {
  // A = rock
  // B = paper
  // C = scissors
  // X = rock
  // Y = paper
  // Z = scissors
  // Time complexity: O(n)
  // Space complexity: O(1)
  std::ifstream infile("./input.txt");
  std::string line;
  
  std::unordered_map<char, int> shape_points = {{'X', 1}, {'Y', 2}, {'Z', 3}};
  std::unordered_map<std::pair<char, char>, int, hash_pair> win_rounds = {
  {{'A', 'X'}, 3},
  {{'A', 'Y'}, 6},
  {{'A', 'Z'}, 0},
  {{'B', 'X'}, 0},
  {{'B', 'Y'}, 3},
  {{'B', 'Z'}, 6},
  {{'C', 'X'}, 6},
  {{'C', 'Y'}, 0},
  {{'C', 'Z'}, 3}
  };
  int points = 0;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    char player, me;
    iss >> player >> me;
    points += shape_points[me] + win_rounds[{player, me}];
  }
  return points;
}


int main(void) {
  int res = day2part1();
  int res2 = day2part2();
  std::cout << "Res is: " << res << " Res2: " << res2 << std::endl;
  return 0;
}


