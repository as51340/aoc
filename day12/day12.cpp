#include <bits/stdc++.h>
#include <fstream>
#include <limits>

// make cout and cin as fast as stdio
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();

struct GridElem {
    // has naming mark because it can also be starting or ending position not only elevation
    char mark, move = '.'; // . means that you didn't actually visit this position
    bool visited = false; // if this grid element was already visible
    int cache = std::numeric_limits<int>::max();
};

void printGrid(std::vector<std::vector<GridElem*>> &grid, std::function<char (const GridElem*)> grid_elem_acc) {
    for (const std::vector<GridElem*> &row : grid) {
        for (const GridElem *elem : row) {
            std::cout << grid_elem_acc(elem);
        }
        std::cout << std::endl;
    }
}

bool travelAroundGrid(int i, int j, std::vector<std::vector<GridElem*>> &grid) {
    // returns number of steps needed from the current position to the target element
    grid[i][j]->visited = true;
    if (grid[i][j]->mark == 'E') {
        grid[i][j]->cache = 0;
        return true; // no steps needed
    }
    int min_needed_steps = std::numeric_limits<int>::max();
    bool starting_point = grid[i][j]->mark == 'S';
    bool max_elevation = grid[i][j]->mark == 'z';


    bool top_condition = (i > 0) && (starting_point || max_elevation || (grid[i-1][j]->mark != 'E' && ((grid[i-1][j]->mark - grid[i][j]->mark) <= 1)));
    bool down_condition = (i < grid.size() - 1) && (starting_point || max_elevation || (grid[i+1][j]->mark != 'E' && ((grid[i+1][j]->mark - grid[i][j]->mark) <= 1)));
    bool left_condition = (j > 0) && (starting_point || max_elevation || (grid[i][j-1]->mark != 'E' && ((grid[i][j-1]->mark - grid[i][j]->mark) <= 1)));
    bool right_condition = (j < grid[0].size() - 1) && (starting_point || max_elevation || (grid[i][j+1]->mark != 'E' && ((grid[i][j+1]->mark - grid[i][j]->mark) <= 1)));

    // check top
    if (top_condition) {
        int cmp = -1;
        if (grid[i-1][j]->visited || travelAroundGrid(i-1, j, grid)) {
            cmp = 1 + grid[i-1][j]->cache;
        }
        if (cmp != -1 && cmp < min_needed_steps) {
            min_needed_steps = cmp;
            grid[i][j]->move = '^';
        }
    }
    // check down
    if (down_condition) {
        int cmp = -1;
        if (grid[i+1][j]->visited || travelAroundGrid(i+1, j, grid)) {
            cmp = 1 + grid[i+1][j]->cache;
        }
        if (cmp != -1 && cmp < min_needed_steps) {
            min_needed_steps = cmp;
            grid[i][j]->move = 'v';
        }
    }
    // check left
    if (left_condition) {
        int cmp = -1;
        if (grid[i][j-1]->visited || travelAroundGrid(i, j-1, grid)) {
            cmp = 1 + grid[i][j-1]->cache;
        }
        if (cmp != -1 && cmp < min_needed_steps) {
            min_needed_steps = cmp;
            grid[i][j]->move = '<';
        }
    }
    // right
    if (right_condition) {
        int cmp = -1;
        if (grid[i][j+1]->visited || travelAroundGrid(i, j+1, grid)) {
            cmp = 1 + grid[i][j+1]->cache;
        }
        if (cmp != -1 && cmp < min_needed_steps) {
            min_needed_steps = cmp;
            grid[i][j]->move = '>';
        }
    }

    if (grid[i][j]->move != '.') {
        grid[i][j]->cache=min_needed_steps;
        return true;
    } else {
        return false;
    }
}


// a is the lowest elevation and z is the higest elevation
// S is the current position and has the elevation a and you want to get to E with the elevation z
// you can jump to a square with only one elevation higher than the current elevation is
// or you can go down
void day12(char *test_file) {
    std::ifstream infile(test_file);
    std::vector<std::vector<GridElem*>> grid;
    // create accessor functions
    std::function<char (const GridElem*)> mark_acc = [](const GridElem *elem) { return elem->mark; };
    std::function<char (const GridElem*)> move_acc = [](const GridElem *elem) { return elem->mark == 'E' ? 'E' : elem->move ; };
    // read input
    std::string line;
    int si, sj, i = 0;
    while(std::getline(infile, line)) {
        std::vector<GridElem*> row;
        int j = 0;
        for (const char mark: line) {
            GridElem *grid_elem = new GridElem;
            grid_elem->mark = mark;
            if (mark == 'S') {
                sj = j;
                si = i;
            }
            row.emplace_back(grid_elem);
            ++j;
        }
        ++i;
        grid.emplace_back(row);
    }
    printGrid(grid, mark_acc);
    int res = travelAroundGrid(si, sj, grid);
    std::cout << "Part1: " << res << std::endl;
    printGrid(grid, move_acc);

}


int main(int argc, char* argv[]) {
    day12(argv[1]);
    return 0;
}