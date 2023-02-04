#include <bits/stdc++.h>
#include <fstream>
#include <ios>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#define STARTING_ITEMS_DISCARD 18
#define OPERATION_DISCARD 23
#define DIVISIBLE_DISCARD 21
#define AFFIRMATIVE_COMMAND_DISCARD 29
#define NEGATIVE_COMMAND_DISCARD 30


// make cout and cin as fast as stdio
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();

template <typename Type>
void printVector(const std::deque<Type> &items) {
    for (const auto& item: items) {
        std::cout << item;
        if (&item != &items.back()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

std::vector<std::string> splitByString(std::string s, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> results;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        results.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    results.emplace_back(s);
    return results;
}

enum Operator {PLUS, MULT};

class Monkey {
public:
    long long id, divisible_arg, pos_monkey_id, neg_monkey_id, inspected_items_counter = 0;
    std::string op_arg;
    std::deque<long long> items;
    Operator op;


    Monkey(long long id) : id(id) {};

    void performOperation() {
        long long op_arg1;
        if (this->op_arg == "old") {
            op_arg1 = items[0];
        } else {
            op_arg1 = std::stoi(this->op_arg);
        }
        if (op == MULT) {
            items[0] *= op_arg1;
            // std::cout << "    Worry level is multiplied by " << op_arg1 << " to " << items[0] << std::endl;
        } else {
            items[0] += op_arg1;
            // std::cout << "    Worry level increased by " << op_arg1 << " to " << items[0] << std::endl;
        }
    }

    void gotBored() {
        items[0] = items[0] / 3;
        // std::cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << items[0] << std::endl;
    }

    bool test() {
        return items[0] % divisible_arg == 0;
    }


    void print() {
        std::cout << "Monkey " << this->id << ": ";
        std::cout << "Current items: ";
        printVector(this->items);
        /*std::cout << "Operator: " << this->op << " Op arg: " << this->op_arg << std::endl;
        std::cout << "Divisible arg: " << this->divisible_arg << std::endl;
        std::cout << "Positive monkey: " << this->pos_monkey_id << std::endl;
        std::cout << "Negative monkey: " << this->neg_monkey_id << std::endl;*/
    }
};


std::deque<long long> parseStartingItemsLine(std::string &line) {
    std::vector<std::string> items = splitByString(line.substr(STARTING_ITEMS_DISCARD), ", ");
    std::deque<long long> long_items;
    for (auto &item: items) {
        long_items.emplace_back(std::stoi(item));
    }
    return long_items;
}

// can return old or long long
std::string parseOperation(std::string &line, Operator &op) {
    line = line.substr(OPERATION_DISCARD);
    std::istringstream iss(line);
    std::string op_str;
    std::string op_arg;
    iss >> op_str >> op_arg;
    if (op_str == "*") {
        op = MULT;
    } else if (op_str == "+") {
        op = PLUS;
    } else {
        std::cout << "Please no" << std::endl;
    }
    return op_arg;
}

long long parseDivisible(std::string &line) {
    // return string and then let monkey play with it
    return std::stoi(line.substr(DIVISIBLE_DISCARD));
}

long long parseBool(std::string &line, bool status_command) {
    if (status_command) {
        return std::stoi(line.substr(AFFIRMATIVE_COMMAND_DISCARD));
    } else {
        return std::stoi(line.substr(NEGATIVE_COMMAND_DISCARD));
    }
}

void completeRound(std::vector<Monkey*> monkeys, int round, long long divisors) {
    for (Monkey* curr_monkey: monkeys) {
        // std::cout << "Monkey " << curr_monkey->id << ":" << std::endl;
        const long long num_items = curr_monkey->items.size();

        for (long long i = 0; i < num_items; ++i) {
            // std::cout << "  Monkey inspects an item with a worry level of " << curr_monkey->items.front() << std::endl;
            curr_monkey->performOperation();
            curr_monkey->items[0] = curr_monkey->items[0] % divisors;
            // curr_monkey->gotBored();

            long long curr_item = curr_monkey->items.front();
            if (curr_monkey->test()) {
                monkeys[curr_monkey->pos_monkey_id]->items.emplace_back(curr_item);
                // std::cout << "    Current worry level is divisible by " << curr_monkey->divisible_arg << std::endl;
                // std::cout << "    Item with worry level " << curr_item << " is thrown to monkey " << curr_monkey->pos_monkey_id << std::endl;
            } else {
                // monkeys[curr_monkey->neg_monkey_id]->gotBored();
                monkeys[curr_monkey->neg_monkey_id]->items.emplace_back(curr_item);
                // std::cout << "    Current worry level is not divisible by " << curr_monkey->divisible_arg << std::endl;
                // std::cout << "    Item with worry level " << curr_item << " is thrown to monkey " << curr_monkey->neg_monkey_id << std::endl;
            }
            ++curr_monkey->inspected_items_counter;
            curr_monkey->items.pop_front();
        }
    }
}


void day11(char* test_file, int rounds) {
    std::ifstream infile(test_file);
    std::string line;
    std::vector<Monkey*> monkeys;
    while (std::getline(infile, line)) { // Monkey <id> line
        std::istringstream iss(line);
        iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        long long monkey_id;
        iss >> monkey_id;
        Monkey* monkey = new Monkey(monkey_id);
        std::getline(infile, line); // starting items line
        monkey->items = parseStartingItemsLine(line);

        Operator op;
        std::getline(infile, line); // operation
        monkey->op_arg = parseOperation(line, op);
        monkey->op = op;

        std::getline(infile, line); // test
        monkey->divisible_arg = parseDivisible(line);


        std::getline(infile, line); // condition1
        monkey->pos_monkey_id = parseBool(line, true);

        std::getline(infile, line); // condition2
        monkey->neg_monkey_id = parseBool(line, false);

        // monkey->prlong long();
        monkeys.emplace_back(monkey);

        std::getline(infile, line); // discard
    }

    long long divisors = 1;
    for (Monkey *curr_monkey: monkeys) {
        divisors *= curr_monkey->divisible_arg;
    }

    for (long long round = 1; round <= rounds; ++round) {
        completeRound(monkeys, round, divisors);
        if (round % 1000 == 0 || round == 20 || round == 1) {
            std::cout << "Round: " << round << std::endl;
            for (Monkey* monkey: monkeys) {
                std::cout << "Monkey " << monkey->id << " inspected " << monkey->inspected_items_counter << " times." << std::endl;
            }
            std::cout << std::endl;
        }
        /*std::cout << "Round: " << round << std::endl;
        for (Monkey *monkey: monkeys) {
            monkey->print();
        }
        std::cout << std::endl;*/
    }




    std::function<bool (Monkey *a, Monkey *b)> cmp = [](Monkey *a, Monkey *b){ return a->inspected_items_counter > b->inspected_items_counter; };
    std::sort(monkeys.begin(), monkeys.end(), cmp);
    long long res = monkeys[0]->inspected_items_counter * monkeys[1]->inspected_items_counter;
    std::cout << "Result: " << res << std::endl;
}



int main(int argc, char* argv[]) {
    day11(argv[1], 10000);
    return 0;
}