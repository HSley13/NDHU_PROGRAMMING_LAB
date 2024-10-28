#include <iostream>
#include <vector>

class SudokuSolver {
  public:
    SudokuSolver(const std::vector<std::vector<int>> &initialBoard) {
        board = initialBoard;
    }

    void printBoard() const {
        for (int i{0}; i < N; i++) {
            for (int j{0}; j < N; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool isValid(int row, int col, int num) const {
        for (int x{0}; x < N; x++) {
            if (board[row][x] == num) {
                return false;
            }
        }

        for (int x{0}; x < N; x++) {
            if (board[x][col] == num) {
                return false;
            }
        }

        int startRow = row - row % 2;
        int startCol = col - col % 2;
        for (int i{0}; i < 2; i++) {
            for (int j{0}; j < 2; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    bool solve() {
        int row = -1, col = -1;
        bool isEmpty = false;

        for (int i{0}; i < N; i++) {
            for (int j{0}; j < N; j++) {
                if (board[i][j] == 0) {
                    row = i;
                    col = j;
                    isEmpty = true;
                    break;
                }
            }
            if (isEmpty) {
                break;
            }
        }

        if (!isEmpty) {
            return true;
        }

        for (int num{1}; num <= N; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;

                printBoard();

                if (solve()) {
                    return true;
                }

                board[row][col] = 0;
            }
        }
        return false;
    }

  private:
    static const int N = 4;
    std::vector<std::vector<int>> board;
};

int main(void) {
    std::vector<std::vector<int>> initialBoard = {{1, 2, 0, 0},
                                                  {3, 4, 0, 0},
                                                  {2, 1, 4, 3},
                                                  {4, 3, 2, 1}};

    SudokuSolver solver(initialBoard);

    std::cout << "Initial Board:" << std::endl;
    solver.printBoard();

    if (solver.solve()) {
        std::cout << "Solved Board:" << std::endl;
        solver.printBoard();
    } else {
        std::cout << "No solution exists." << std::endl;
    }
}
