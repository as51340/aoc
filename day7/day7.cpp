#include <bits/stdc++.h>
#include <cstddef>
#include <new>

#define LIMIT 100000
#define TOTAL_DISK_SPACE 70000000
#define UPDATE_SPACE 30000000

// make cout and cin as fast as stdio
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();


class FileHandler {
public:
    std::string name;
    long long size = 0;
    FileHandler* parent;

    ~FileHandler() {
        delete parent;
    }
    FileHandler(std::string &name, long long size) : name{name}, size(size) {}

    virtual void print(uint) = 0;
};

class File : public FileHandler {
public:

    using FileHandler::FileHandler;

    ~File() = default;

    void print(uint level = 0) override {
        for (int i = 0; i < level; ++i) std::cout << " ";
        std::cout << "- " << name << " " << "(file, size=" << size << ")" << std::endl;
    }
};

class Dir : public FileHandler {
public:
    std::vector<Dir*> dirs;
    std::vector<File*> files;

    ~Dir() {
        for (int i = 0; i < dirs.size(); ++i) {
            delete dirs[i];
        }
        for (int i = 0; i < files.size(); ++i) {
            delete files[i];
        }
    }

    Dir(std::string &name) : FileHandler(name, 0) {}
    Dir(std::string &&name) : FileHandler(name, 0) {}


    void print(uint level = 0) override {
        for (int i = 0; i < level; ++i) std::cout << " ";
        std::cout << "- " << name << " " << "(dir, size=" << size << ")" << std::endl;
    }

    void printRec(uint level = 0) {
        this->print(level);
        for (Dir* dir: this->dirs) {
           dir->printRec(level+1);
        }
        for (File* file: this->files) {
            file->print(level+1);
        }
    }

    void addDir(Dir* new_dir) {
        new_dir->parent = this;
        dirs.emplace_back(new_dir);
    }

    // add file to storage for files
    void addFile(File* new_file) {
        new_file->parent = this;
        files.emplace_back(new_file);
        this->addSize(new_file->size);
    }

    // add size to the current directory and continue
    void addSize(long long size) {
        this->size += size;
        if (this->parent != nullptr) {
           ((Dir*) (this->parent))->addSize(size);
        }
    }

    // change this to some c++ predicate
    void addSubtreeWithCondition(std::function<bool (Dir* dir)> &condition, std::vector<Dir*> &solutions) {
        if (condition(this)) {
            solutions.emplace_back(this);
        }
        for (Dir* dir: this->dirs) {
            dir->addSubtreeWithCondition(condition, solutions);
        }
    }

    // return directory from this current directory
    Dir* changeDir(std::string dir_name) {
        if (dir_name == "..") return (Dir*) this->parent;
        for (Dir* dir: this->dirs) {
            if (dir_name.compare(dir->name) == 0) {
                return dir;
            }
        }
        std::cerr << "Directory: " << this->name << " doesn't contain directory " << dir_name << std::endl;
        return nullptr;
    }
};

void printStatus(Dir* root, std::string &command) {
    std::cout << command << std::endl;
    root->printRec();
    std::cout << std::endl;
}

// probably won't work, so return curr dir
Dir* parseCommand(Dir* curr_dir, std::string command) {
    if (command.find('$') == 0) {
        std::istringstream iss(command);
        iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
        std::string sys_command;
        iss >> sys_command;
        if (sys_command.compare("cd") == 0) {
            std::string cd_arg;
            iss >> cd_arg;
            curr_dir = curr_dir->changeDir(cd_arg);
        }
    } else if(command.find("dir") == 0) { // dir command handling
        std::istringstream iss(command);
        iss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // delimiter is space
        std::string dir_name;
        iss >> dir_name;
        Dir* new_dir = new Dir(dir_name);
        curr_dir->addDir(new_dir);
    } else { // file command handling
        long long size;
        std::string name;
        std::istringstream iss(command); // TODO: possibly extract
        iss >> size >> name;
        File* new_file = new File(name, size);
        curr_dir->addFile(new_file);
    }
    return curr_dir;
}

long long sumDirectories(std::vector<Dir*> &directories) {
    long long res = 0;
    for (Dir* dir: directories) {
        res += dir->size;
    }
    return res;
}
Dir* findSmallestDirectory(std::vector<Dir*> &directories) {
    long long min = std::numeric_limits<long long>::max();
    Dir* smallest_dir = nullptr;
    for (Dir* dir: directories) {
        if (dir->size < min) {
            min = dir->size;
            smallest_dir = dir;
        }
    }
    return smallest_dir;
}



void day7(const char *input_file) {
    std::string command;
    std::ifstream infile(input_file);

    // first get the root
    Dir* root = new Dir("/");
    Dir* curr_dir = root;
    std:getline(infile, command); // just discard first value

    while(std::getline(infile, command)) {
        curr_dir = parseCommand(curr_dir, command);
    }

    // Solve 1st part
    std::vector<Dir*> solutions1;
    std::function<bool(Dir* dir)> cond_size = [](Dir* dir) { return dir->size <= LIMIT; };

    root->addSubtreeWithCondition(cond_size, solutions1);
    std::cout << "Part1: " << sumDirectories(solutions1) << std::endl;

    // Solve 2nd part
    std::vector<Dir*> solutions2;
    long long available_space = TOTAL_DISK_SPACE - root->size;
    long long needed_space = UPDATE_SPACE - available_space;
    std::function<bool(Dir* dir)> part2_cond = [needed_space](Dir* dir) { return dir->size >= needed_space; };
    root->addSubtreeWithCondition(part2_cond, solutions2);
    std::cout << "Part2: " << findSmallestDirectory(solutions2)->size << std::endl;
}


int main(int argc, char *argv[]) {
    day7(argv[1]);

    return 0;
}


