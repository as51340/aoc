#include <bits/stdc++.h>

#define printVar(x) std::cout << (#x) << " " << (x) << std::endl

static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();

// move it to the utils
template <typename Container>
void print(const Container & c, std::ostream & out = std::cout)
{
    typename Container::const_iterator itr;
    for( itr=c.begin(); itr!=c.end(); ++itr) {
        out << *itr;
        if (std::next(itr) != c.end()) {
            std::cout << " ";
        }
    }
    out << std::endl;
}

// copy by reference so you don't destroy the original stack
template <typename StackType>
void printStack(std::stack<StackType> stack) {
    std::cout << "TOP->BOTTOM SIZE: " << stack.size() << std::endl;
    while (stack.size() > 1) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    if(!stack.empty()) {
        std::cout << stack.top() << std::endl;
    }
}

template <typename StackType>
void printStacks(const std::vector<std::stack<StackType>> &stacks) {
    for (auto stack: stacks) {
        printStack(stack);
    }
}


template <typename StackType>
void reverseStack(std::stack<StackType> &stack) {
    std::stack<StackType> tmpStack;
    // from original to empty
    while (!stack.empty()) {
        tmpStack.push(stack.top());
        stack.pop();
    }
    stack = tmpStack;
}

template <typename StackType>
void reverseStacks(std::vector<std::stack<StackType>> &stacks) {
    for (auto &stack: stacks) {
        reverseStack<StackType>(stack);
    }
}

// Move it all to the utils
const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

// String s is not destroyed
// TODO: Move it to the utils
void splitByString(std::string s, std::string delimiter, std::vector<std::string> &results) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        results.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    results.emplace_back(s);
}

template <typename StackType>
void moveBetweenStacks(std::vector<std::stack<StackType>> &stacks, int n, int src, int dest) {
    // O(n)
    for (int i = 0; i < n; i++) {
        stacks[dest].push(stacks[src].top());
        stacks[src].pop();
    }
}

template <typename StackType>
void moveBetweenStacksAdv(std::vector<std::stack<StackType>> &stacks, int n, int src, int dest) {
    // O(n)
    std::stack<StackType> tmpStack;
    // First to the empty stack
    for (int i = 0; i < n; ++i) {
        tmpStack.push(stacks[src].top());
        stacks[src].pop();
    }
    while (!tmpStack.empty()) {
        stacks[dest].push(tmpStack.top());
        tmpStack.pop();
    }
}


void processLine(std::vector<std::stack<char>> &stacks, std::string line) {
    int cnt = 0;
    int stack_id = 0;
    int line_size = line.size();
    while (cnt < line_size) {
        std::string extr = line.substr(cnt, 3);
        if (extr != "   ") {
            stacks[stack_id].push(extr[1]);
        }
        cnt += 4;
        ++stack_id;
    }
}

void processCmdLine(std::string cmdLine, int &q, int &src, int &dest) {
    // printVar(cmdLine);
    std::istringstream iss(cmdLine);
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
    iss >> q;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
    iss >> src;
    --src;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
    iss >> dest;
    --dest;
}

std::string day5(char part) {
    std::ifstream infile("./input.txt");
    std::string line;

    std::vector<std::string> stacks_description;
    // process stack creation
    while(std::getline(infile, line) && !line.empty()) {
        stacks_description.emplace_back(line);
    }
    // get number of stacks
    std::vector<std::string> results;
    splitByString(ltrim(stacks_description.back()), "   ", results);
    stacks_description.pop_back();
    int numStacks = std::stoi(results.back());

    // Process finally input stack
    std::vector<std::stack<char>> stacks(numStacks);
    for (const std::string& line: stacks_description) {
        processLine(stacks, line);
    }
    reverseStacks<char>(stacks);

    // Starting reading commands
    while(std::getline(infile, line)) {
        int q, src, dest;
        processCmdLine(line, q, src, dest);
        if (part == '1') {
            moveBetweenStacks<char>(stacks, q, src, dest);
        } else {
            moveBetweenStacksAdv<char>(stacks, q, src, dest);
        }
    }

    // create final solution
    std::string sol = "";
    for (const auto& stack: stacks) {
        if (!stack.empty()) sol += stack.top();
    }
    return sol;
}


int main(void) {

    std::cout << day5('1') << std::endl;
    std::cout << day5('2') << std::endl;

    return 0;
}


