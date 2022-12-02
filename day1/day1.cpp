#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

int day1part1() {
  // Time complexity: O(n)
  // Space complexity: O(1)
  std::ifstream infile("./input.txt");
  std::string line;
  int cache = 0;
  int max = 0;
  while(std::getline(infile, line)) {
    if (line == "") {
      if (cache > max) max = cache;
      cache = 0;
    } else {
      cache += stoi(line);
    }
  }
  return max;
}

int day1part2() {
  // Time complexity: O(nlogk)
  // Space complexity: O(k)
  std::ifstream infile("./input.txt");
  std::string line;
  int cache = 0;
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  while(std::getline(infile, line)) {
    if (line == "") {
      pq.push(cache);
      cache = 0;
      if (pq.size() > 3) { // O(nlogk)
        pq.pop();
      }
    } else {
      cache += stoi(line);
    }
  }
  int res = 0;
  while (!pq.empty()) { // O(klogk)
    res += pq.top();
    pq.pop();
  }
  return res;
}

int main(void) {
  
  int part1 = day1part1(); 
  int part2 = day1part2();
  std::cout << "Max is: " << part1 <<  std::endl;
  std::cout << "Top three: " << part2 << std::endl;

  return 0;
}
