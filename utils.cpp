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

std::vector<std::string> splitByString(std::string s, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> results;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        results.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return results;
}