#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid {
  public:
    Grid() {
        Grid(0);
    }

    Grid(int s) {
        state = s;
        for (int i{0}; i < 4; i++) {
            dir[i] = nullptr;
        }
        visited = false;
    }

    Grid(const Grid &) = delete;
    Grid &operator=(const Grid &) = delete;

    Grid *getDir(int d) {
        return dir[d];
    }

    int getState() {
        return state;
    }

    void setDir(int d, Grid *g) {
        dir[d] = g;
    }

    void setState(int s) {
        state = s;
    }

    bool isVisited() {
        return visited;
    }

    void setVisited(bool v) {
        visited = v;
    }

  private:
    Grid *dir[4];
    int state;
    bool visited;
};

class List {
  public:
    List() : top(0) {}

    void addElement(Grid *g) {
        if (top < SIZE * SIZE) {
            data[top++] = g;
        }
    }

    Grid *removeElement() {
        if (top == 0) {
            return nullptr;
        }
        return data[--top];
    }

    void printPath() {
        for (int j = 1; j < top; j++) {
            if (data[j] == data[j - 1]->getDir(UP)) {
                std::cout << "UP\n";
            } else if (data[j] == data[j - 1]->getDir(DOWN)) {
                std::cout << "DOWN\n";
            } else if (data[j] == data[j - 1]->getDir(LEFT)) {
                std::cout << "LEFT\n";
            } else if (data[j] == data[j - 1]->getDir(RIGHT)) {
                std::cout << "RIGHT\n";
            }
        }
    }

  private:
    Grid *data[SIZE * SIZE];
    int top;
};

class Maze {
  public:
    Maze() {
        initMaze(SIZE);
    }

    void initMaze(int s) {
        maze = std::make_unique<Grid>(0);
        Grid *currentRow = maze.get();

        for (int i{0}; i < s; i++) {
            Grid *current = currentRow;
            for (int j{0}; j < s; j++) {
                if (i == 0 && j == 0) continue;

                std::unique_ptr<Grid> newGrid = std::make_unique<Grid>(0);

                if (rand() % 100 < 20 && !(i == s - 1 && j == s - 1)) {
                    newGrid->setState(1);
                }

                if (j > 0) {
                    current->setDir(RIGHT, newGrid.get());
                    newGrid->setDir(LEFT, current);
                }

                current = newGrid.release();
            }

            if (i < s - 1) {
                std::unique_ptr<Grid> newRow = std::make_unique<Grid>(0);

                currentRow->setDir(DOWN, newRow.get());
                newRow->setDir(UP, currentRow);

                currentRow = newRow.release();
            }
        }
    }

    std::unique_ptr<List> getPath() {
        std::unique_ptr<List> path = std::make_unique<List>();
        if (findPath(maze.get(), path.get())) {
            return path;
        }
        return std::make_unique<List>();
    }

    void printMaze() {
        Grid *j = maze.get();
        Grid *k;

        while (j != nullptr) {
            k = j;
            while (k != nullptr) {
                std::cout << (k->getState() == 1 ? "#" : ".");
                k = k->getDir(RIGHT);
            }
            std::cout << std::endl;
            j = j->getDir(DOWN);
        }
    }

  private:
    std::unique_ptr<Grid> maze;

    bool findPath(Grid *current, List *path) {
        if (current == nullptr || current->getState() == 1 || current->isVisited())
            return false;

        current->setVisited(true);
        path->addElement(current);

        if (current->getDir(DOWN) == nullptr && current->getDir(RIGHT) == nullptr && current->getDir(LEFT) == nullptr && current->getDir(UP) == nullptr)
            return true;

        if (findPath(current->getDir(RIGHT), path) || findPath(current->getDir(DOWN), path) || findPath(current->getDir(LEFT), path) || findPath(current->getDir(UP), path)) {
            return true;
        }

        path->removeElement();
        return false;
    }
};

int main(void) {
    std::unique_ptr<Maze> maze = std::make_unique<Maze>();
    maze->printMaze();

    std::unique_ptr<List> path = maze->getPath();
    if (path->removeElement() != nullptr) {
        std::cout << "Path found:\n";
        path->printPath();
    } else {
        std::cout << "No path found.\n";
    }
}
