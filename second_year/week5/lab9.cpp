#include <cmath>
#include <iostream>

template <class T>
class BinaryTreeInArray {
  public:
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}

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
    T *array;
    int height;
    int numOfElement;

    void resize(int size) {
        T *temp = new T[numOfElement];

        for (int j{0}; j < numOfElement; j++)
            temp[j] = array[j];

        delete array;

        array = new T[static_cast<int>(pow(2, height + 1)) - 1];

        for (int j{0}; j < numOfElement; j++)
            array[j] = temp[j];

        height++;
        delete[] temp;
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
        TreeNode *left, *right;
        T data;
    };

    TreeNode *root;
    int numOfElement;
};

int main(void) {
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;

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
