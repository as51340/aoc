#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <sys/types.h>

// make cout and cin as fast as stdio
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();


class MatrixElem {
public:
    int max_left = 0, max_top = 0, max_right = 0, max_down = 0; // max seen from each side
    int left_visible = 0, top_visible = 0, right_visible = 0, down_visible = 0;
    bool visible = false; // if already classified as visible
    int elem = -1; // not initialized
    MatrixElem(int elem) : elem(elem) {}

    long long scenicScore() {
        return left_visible*top_visible*right_visible*down_visible;
    }
};

// change so it accepts function for printing specific element
void printMatrix(std::vector<std::vector<MatrixElem*>> *matrix, std::function<int (const MatrixElem*)> &accessor) {
    for (const auto &row: *matrix) {
        for (const auto *elem: row) {
            std::cout << accessor(elem) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int processMatrix1(std::vector<std::vector<MatrixElem*>> *matrix) {
    int res = 0;
    for (const auto &row: *matrix) {
        for (const auto *elem: row) {
            if (elem->visible) ++res;
        }
    }
    return res;
}


long long processMatrix2(std::vector<std::vector<MatrixElem*>> *matrix) {
    long long max = -1;
    for (const auto &row: *matrix) {
        for (auto *elem: row) {
            max = std::max(max, elem->scenicScore());
        }
    }
    return max;
}

void processTopLeft(std::vector<std::vector<MatrixElem*>> *matrix) {
    int num_rows = matrix->size();
    for (int i = 0; i < num_rows; i++) {
        const auto &row = (*matrix)[i];
        int num_cols = row.size();
        for (int j = 0; j < num_cols; j++) {
            MatrixElem* curr_elem = row[j];
            bool first_row = i == 0;
            bool first_col = j == 0;
            if (first_row) {
                curr_elem->visible = true;
                curr_elem->max_top = curr_elem->elem;
            } else {
                MatrixElem* top_elem = (*matrix)[i-1][j];
                if (curr_elem->elem > top_elem->max_top) {
                    curr_elem->visible = true;
                }
                for (int k = i - 1; k >= 0; --k) {
                    curr_elem->top_visible++;
                    if (curr_elem->elem <= (*matrix)[k][j]->elem) {
                        break;
                    }
                }
                curr_elem->max_top = std::max(top_elem->max_top, curr_elem->elem);
            }
            if (first_col) {
                curr_elem->visible = true;
            } else {
                MatrixElem* left_elem = row[j-1];
                if (curr_elem->elem > left_elem->max_left) {
                    curr_elem->visible = true;
                }
                for (int k = j - 1; k >= 0; --k) {
                    curr_elem->left_visible++;
                    if (curr_elem->elem <= (*matrix)[i][k]->elem) {
                        break;
                    }
                }
                curr_elem->max_left = std::max(left_elem->max_left, curr_elem->elem);
            }
        }
    }
}


void processDownRight(std::vector<std::vector<MatrixElem*>> *matrix) {
    int num_rows = matrix->size();
    for (int i = num_rows - 1; i >= 0; --i) {
        const auto &row = (*matrix)[i];
        int num_cols = row.size();
        for (int j = num_cols - 1; j >= 0; --j) {
            MatrixElem* curr_elem = row[j];
            bool last_row = i == num_rows - 1;
            bool last_col = j == num_cols - 1;
            if (last_row) {
                curr_elem->visible = true;
                curr_elem->max_down = curr_elem->elem;
            } else {
                MatrixElem* down_elem = (*matrix)[i+1][j];
                if (curr_elem->elem > down_elem->max_down) {
                    curr_elem->visible = true;
                }
                for (int k = i + 1; k < num_rows; ++k) {
                    curr_elem->down_visible++;
                    if (curr_elem->elem <= (*matrix)[k][j]->elem) {
                        break;
                    }
                }
                curr_elem->max_down = std::max(down_elem->max_down, curr_elem->elem);
            }
            if (last_col) {
                curr_elem->visible = true;
                curr_elem->max_right = curr_elem->elem;
            } else {
                MatrixElem* right_elem = row[j+1];
                if (curr_elem->elem > right_elem->max_right) {
                    curr_elem->visible = true;
                }
                for (int k = j + 1; k < num_cols; ++k) {
                    curr_elem->right_visible++;
                    if (curr_elem->elem <= (*matrix)[i][k]->elem) {
                        break;
                    }
                }

                curr_elem->max_right = std::max(right_elem->max_right, curr_elem->elem);
            }
        }
    }
}

void day8(const char* test_file) {
    // I don't think the complexity can go belowe O(n*m)
    std::ifstream infile(test_file);
    std::vector<std::vector<MatrixElem*>> matrix;

    std::string line;
    while (std::getline(infile, line)) {
        const int line_length = line.length();
        std::vector<MatrixElem*> row;
        for (uint8_t i = 0; i < line_length; ++i) {
            MatrixElem* matrix_elem = new MatrixElem(line[i] - '0');
            row.emplace_back(matrix_elem);
        }
        matrix.emplace_back(row);
    }
    // first part accessors
    std::function<int (const MatrixElem*)> elem_acc = [](const MatrixElem *elem) { return elem->elem; };
    std::function<int (const MatrixElem*)> max_left_acc = [](const MatrixElem *elem) { return elem->max_left; };
    std::function<int (const MatrixElem*)> max_top_acc = [](const MatrixElem *elem) { return elem->max_top; };
    std::function<int (const MatrixElem*)> max_right_acc = [](const MatrixElem *elem) { return elem->max_right; };
    std::function<int (const MatrixElem*)> max_down_acc = [](const MatrixElem *elem) { return elem->max_down; };
    std::function<int (const MatrixElem*)> status_acc = [](const MatrixElem *elem) { return elem->visible; };
    // second part accessors
    std::function<int (const MatrixElem*)> left_acc = [](const MatrixElem *elem) { return elem->left_visible; };
    std::function<int (const MatrixElem*)> top_acc = [](const MatrixElem *elem) { return elem->top_visible; };
    std::function<int (const MatrixElem*)> right_acc = [](const MatrixElem *elem) { return elem->right_visible; };
    std::function<int (const MatrixElem*)> down_acc = [](const MatrixElem *elem) { return elem->down_visible; };

    std::cout << "Elem" << std::endl;
    printMatrix(&matrix, elem_acc);
    processTopLeft(&matrix);
    std::cout << "left visible" << std::endl;
    printMatrix(&matrix, left_acc);
    std::cout << "top visible" << std::endl;
    printMatrix(&matrix, top_acc);

    processDownRight(&matrix);

    int part1 = processMatrix1(&matrix);
    long long part2 = processMatrix2(&matrix);

    std::cout << "Part1: " << part1 << std::endl;
    std::cout << "Part2: " << part2 << std::endl;

    // clear memory
    for (const auto &v1: matrix) {
        for (const auto* elem: v1) {
            delete elem;
        }
    }
}



int main(int argc, char* argv[]) {
    day8(argv[1]);

    return 0;
}