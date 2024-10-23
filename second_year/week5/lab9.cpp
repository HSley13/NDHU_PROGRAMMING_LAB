#include <cmath>
#include <iostream>
#include <memory>

template <class T>
class BinaryTreeInArray {
  public:
    BinaryTreeInArray() : height(0), numOfElement(0) {}

    void addElementAsCompleteTree(T data) {
        int cap = pow(2, height) - 1;

        if (numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1);

        array[numOfElement] = data;
        numOfElement++;
    }

    void displayInorder() {
    }

    void displayPreorder() {
    }

    void displayPostorder() {
    }

  private:
    std::vector<T> array;
    int height;
    int numOfElement;

    void resize(int size) {
        array.resize(size);
        height++;
    }
};

template <class T>
class BinaryTreeInLinkedList {
  public:
    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

    void addElementAsCompleteTree(T data) {
    }

    void displayInorder() {
    }

    void displayPreorder() {
    }

    void displayPostorder() {
    }

  private:
    class TreeNode {
      public:
        TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        T data;
    };

    std::shared_ptr<TreeNode> root;
    int numOfElement;
};

int main(void) {
    std::unique_ptr<BinaryTreeInArray<int>> b = std::make_unique<BinaryTreeInArray<int>>();
    std::unique_ptr<BinaryTreeInLinkedList<int>> tree = std::make_unique<BinaryTreeInLinkedList<int>>();

    int n;
    std::cin >> n;

    for (int j{0}; j < n; j++) {
        b->addElementAsCompleteTree(j);
        tree->addElementAsCompleteTree(j);
    }

    b->displayInorder();
    std::cout << std::endl;

    tree->displayInorder();
    std::cout << std::endl;

    b->displayPreorder();
    std::cout << std::endl;

    tree->displayPreorder();
    std::cout << std::endl;

    b->displayPostorder();
    std::cout << std::endl;

    tree->displayPostorder();
    std::cout << std::endl;
}
