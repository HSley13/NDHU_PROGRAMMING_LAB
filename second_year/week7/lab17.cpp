#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>

template <class T>
class BinaryTreeNode {
  public:
    T data;
    std::unique_ptr<BinaryTreeNode<T>> left;
    std::unique_ptr<BinaryTreeNode<T>> right;
    int height;

    BinaryTreeNode(T d) : data(d), left(nullptr), right(nullptr), height(1) {}

    bool operator>(BinaryTreeNode<T> &n) {
        return data > n.data;
    }

    bool operator==(BinaryTreeNode<T> &n) {
        return data == n.data;
    }
};

template <class T>
class AVLTree {
  public:
    AVLTree() : root(nullptr) {}

    void insert(T data) {
        root = insert(std::move(root), data);
    }

    void inorder() {
        inorder(root.get(), 0);
    }

  private:
    std::unique_ptr<BinaryTreeNode<T>> root;

    int height(BinaryTreeNode<T> *node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }

    int getBalance(BinaryTreeNode<T> *node) {
        if (!node) {
            return 0;
        }
        return height(node->left.get()) - height(node->right.get());
    }

    // Right rotation
    std::unique_ptr<BinaryTreeNode<T>> rightRotate(std::unique_ptr<BinaryTreeNode<T>> &y) {
        std::unique_ptr<BinaryTreeNode<T>> x = std::move(y->left);
        std::unique_ptr<BinaryTreeNode<T>> T2 = std::move(x->right);

        // Perform rotation
        x->right = std::move(y);
        x->right->left = std::move(T2);

        // Update heights
        x->right->height = std::max(height(x->right->left.get()), height(x->right->right.get())) + 1;
        x->height = std::max(height(x->left.get()), height(x->right.get())) + 1;

        return x; // Return new root
    }

    // Left rotation
    std::unique_ptr<BinaryTreeNode<T>> leftRotate(std::unique_ptr<BinaryTreeNode<T>> &x) {
        std::unique_ptr<BinaryTreeNode<T>> y = std::move(x->right);
        std::unique_ptr<BinaryTreeNode<T>> T2 = std::move(y->left);

        // Perform rotation
        y->left = std::move(x);
        y->left->right = std::move(T2);

        // Update heights
        y->left->height = std::max(height(y->left->left.get()), height(y->left->right.get())) + 1;
        y->height = std::max(height(y->left.get()), height(y->right.get())) + 1;

        return y; // Return new root
    }

    // Function to insert a new node
    std::unique_ptr<BinaryTreeNode<T>> insert(std::unique_ptr<BinaryTreeNode<T>> node, T data) {
        // 1. Perform the normal BST insert
        if (!node) {
            return std::make_unique<BinaryTreeNode<T>>(data);
        }

        if (data < node->data) {
            node->left = insert(std::move(node->left), data);
        } else if (data > node->data) {
            node->right = insert(std::move(node->right), data);
        } else {
            return node; // Duplicates are not allowed
        }

        // 2. Update height of this ancestor node
        node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));

        // 3. Get the balance factor of this ancestor node to check whether it became unbalanced
        int balance = getBalance(node.get());

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the (unchanged) node pointer
    }

    // Function to print the inorder traversal of the tree
    void inorder(BinaryTreeNode<T> *node, int n) {
        if (!node) {
            return;
        }

        inorder(node->right.get(), n + 1);
        for (int j{0}; j < n; j++) {
            std::cout << "  ";
        }
        std::cout << node->data << std::endl;
        inorder(node->left.get(), n + 1);
    }
};

int main(void) {
    AVLTree<int> tree;

    std::cout << "Inserting elements: 10, 20, 30, 15, 25, 5, 6" << std::endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(6);

    std::cout << "\nInorder Traversal of the AVL Tree after insertions:" << std::endl;
    tree.inorder();

    std::cout << "\nInserting elements: 35, 50, 40, 45" << std::endl;
    tree.insert(35);
    tree.insert(50);
    tree.insert(40);
    tree.insert(45);

    std::cout << "\nInorder Traversal of the AVL Tree after more insertions:" << std::endl;
    tree.inorder();
}
