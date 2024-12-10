#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

template <class T>
class BinaryThreadedTreeNode {
  public:
    T data;
    std::shared_ptr<BinaryThreadedTreeNode> left{nullptr}, right{nullptr};
    bool isThread;

    BinaryThreadedTreeNode(T d)
        : data(d), left(nullptr), right(nullptr), isThread(false) {}
};

template <class T>
class BinarySearchThreadedTree {
  public:
    BinarySearchThreadedTree() : root(nullptr) {}

    void insert(T d) {
        if (!root) {
            root = std::make_shared<BinaryThreadedTreeNode<T>>(d);
        } else {
            insertHelper(root, d);
        }
    }

    void createThreads() {
        createThreadsHelper(root, lastVisited);
    }

    void print() {
        std::shared_ptr<BinaryThreadedTreeNode<T>> node{leftmost(root)};
        while (node) {
            std::cout << node->data << " ";
            if (node->isThread) {
                node = node->right;
            } else {
                node = leftmost(node->right);
            }
        }
        std::cout << std::endl;
    }

  private:
    std::shared_ptr<BinaryThreadedTreeNode<T>> root{nullptr};
    std::shared_ptr<BinaryThreadedTreeNode<T>> lastVisited{nullptr};

    void insertHelper(std::shared_ptr<BinaryThreadedTreeNode<T>> node, T d) {
        if (d < node->data) {
            if (!node->left) {
                node->left = std::make_shared<BinaryThreadedTreeNode<T>>(d);
            } else {
                insertHelper(node->left, d);
            }
        } else {
            if (!node->right) {
                node->right = std::make_shared<BinaryThreadedTreeNode<T>>(d);
            } else {
                insertHelper(node->right, d);
            }
        }
    }

    void createThreadsHelper(std::shared_ptr<BinaryThreadedTreeNode<T>> node, std::shared_ptr<BinaryThreadedTreeNode<T>> &lastVisited) {
        if (!node) {
            return;
        }

        createThreadsHelper(node->left, lastVisited);

        if (lastVisited && !lastVisited->right) {
            lastVisited->right = node;
            lastVisited->isThread = true;
        }

        lastVisited = node;

        if (!node->isThread) {
            createThreadsHelper(node->right, lastVisited);
        }
    }

    std::shared_ptr<BinaryThreadedTreeNode<T>> leftmost(std::shared_ptr<BinaryThreadedTreeNode<T>> node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
};

int main(void) {
    BinarySearchThreadedTree<int> bstt;

    std::srand(std::time(nullptr));
    for (int j{0}; j < 10; j++) {
        bstt.insert(std::rand() % 10);
    }

    bstt.createThreads();

    bstt.print();
    std::cout << std::endl;
}
