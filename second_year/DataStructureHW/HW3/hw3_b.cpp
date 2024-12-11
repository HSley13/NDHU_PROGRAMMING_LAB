#include <algorithm>
#include <iostream>
#include <memory>

template <class T>
class Element {
  public:
    T key;
};

template <class T>
class BSTNode {
  public:
    BSTNode() : LeftChild(nullptr), RightChild(nullptr) {}
    BSTNode(const Element<T> &x) : data(x.key), LeftChild(nullptr), RightChild(nullptr) {}

    int height();
    int weight();
    int heightBF();
    int weightBF();

    std::shared_ptr<BSTNode<T>> LeftChild;
    T data;
    std::shared_ptr<BSTNode<T>> RightChild;
};

template <class T>
class BST {
  public:
    std::shared_ptr<BSTNode<T>> Search(const Element<T> &x);
    std::shared_ptr<BSTNode<T>> Search(std::shared_ptr<BSTNode<T>> b, const Element<T> &x);
    std::shared_ptr<BSTNode<T>> IterSearch(const Element<T> &x);
    void Insert(const Element<T> &x);

    // Print elements in in-order traversal
    void PrintInOrder() const;

    int height();
    int weight();
    int heightBF();
    int weightBF();

  private:
    std::shared_ptr<BSTNode<T>> root;

    void PrintInOrderRecursive(std::shared_ptr<BSTNode<T>> node) const;
};

template <class T>
std::shared_ptr<BSTNode<T>> BST<T>::Search(const Element<T> &x) {
    return Search(root, x);
}

template <class T>
std::shared_ptr<BSTNode<T>> BST<T>::Search(std::shared_ptr<BSTNode<T>> b, const Element<T> &x) {
    if (!b) return nullptr;

    if (x.key == b->data) return b;

    if (x.key < b->data)
        return Search(b->LeftChild, x);

    return Search(b->RightChild, x);
}

template <class T>
std::shared_ptr<BSTNode<T>> BST<T>::IterSearch(const Element<T> &x) {
    std::shared_ptr<BSTNode<T>> t{root};
    while (t) {
        if (x.key == t->data) return t;
        if (x.key < t->data)
            t = t->LeftChild;
        else
            t = t->RightChild;
    }
    return nullptr;
}

template <class T>
void BST<T>::Insert(const Element<T> &x) {
    std::shared_ptr<BSTNode<T>> p{root}, pp{nullptr};
    while (p) {
        pp = p;
        if (x.key < p->data)
            p = p->LeftChild;
        else if (x.key > p->data)
            p = p->RightChild;
        else {
            return;
        }
    }

    p = std::make_shared<BSTNode<T>>(x);

    if (pp) {
        if (x.key < pp->data)
            pp->LeftChild = p;
        else
            pp->RightChild = p;
    } else {
        root = p;
    }
}

template <class T>
int BST<T>::height() {
    if (!root) return -1;
    return root->height();
}

template <class T>
int BST<T>::weight() {
    if (!root) return 0;
    return root->weight();
}

template <class T>
int BST<T>::heightBF() {
    if (!root) return 0;
    return root->heightBF();
}

template <class T>
int BST<T>::weightBF() {
    if (!root) return 0;
    return root->weightBF();
}

template <class T>
int BSTNode<T>::height() {
    int leftHeight{(LeftChild) ? LeftChild->height() : -1};
    int rightHeight{(RightChild) ? RightChild->height() : -1};
    return 1 + std::max(leftHeight, rightHeight);
}

template <class T>
int BSTNode<T>::weight() {
    int leftWeight{(LeftChild) ? LeftChild->weight() : 0};
    int rightWeight{(RightChild) ? RightChild->weight() : 0};
    return 1 + leftWeight + rightWeight;
}

template <class T>
int BSTNode<T>::heightBF() {
    int leftHeight{(LeftChild) ? LeftChild->height() : -1};
    int rightHeight{(RightChild) ? RightChild->height() : -1};

    return leftHeight - rightHeight;
}

template <class T>
int BSTNode<T>::weightBF() {
    int leftWeight{(LeftChild) ? LeftChild->weight() : 0};
    int rightWeight{(RightChild) ? RightChild->weight() : 0};

    return leftWeight - rightWeight;
}

template <class T>
void BST<T>::PrintInOrder() const {
    PrintInOrderRecursive(root);
    std::cout << std::endl;
}

template <class T>
void BST<T>::PrintInOrderRecursive(std::shared_ptr<BSTNode<T>> node) const {
    if (!node) return;

    PrintInOrderRecursive(node->LeftChild);
    std::cout << node->data << " ";
    PrintInOrderRecursive(node->RightChild);
}

int main(void) {
    BST<int> tree;

    Element<int> e1{50}, e2{30}, e3{20}, e4{40}, e5{70}, e6{60}, e7{80};
    tree.Insert(e1);
    tree.Insert(e2);
    tree.Insert(e3);
    tree.Insert(e4);
    tree.Insert(e5);
    tree.Insert(e6);
    tree.Insert(e7);

    std::cout << "Height of the tree: " << tree.height() << std::endl;
    std::cout << "Weight of the tree: " << tree.weight() << std::endl;
    std::cout << "Height balance factor of the tree: " << tree.heightBF() << std::endl;
    std::cout << "Weight balance factor of the tree: " << tree.weightBF() << std::endl;

    std::cout << "In-order traversal of the tree: ";
    tree.PrintInOrder();

    Element<int> e{100};
    std::shared_ptr<BSTNode<int>> node{std::make_shared<BSTNode<int>>(e)};
    std::cout << "Node height (no children): " << node->height() << std::endl;
    std::cout << "Node weight (no children): " << node->weight() << std::endl;

    node->LeftChild = std::make_shared<BSTNode<int>>(Element<int>{50});
    node->RightChild = std::make_shared<BSTNode<int>>(Element<int>{150});
    std::cout << "Node height (two children): " << node->height() << std::endl;
    std::cout << "Node weight (two children): " << node->weight() << std::endl;
}
