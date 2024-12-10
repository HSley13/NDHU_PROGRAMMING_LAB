#include <iostream>
#include <memory>

template <class T>
class Element {
  public:
    T key;
};

template <class T>
class BST;

template <class T>
class BSTNode {
    friend class BST<T>;

  public:
    BSTNode();
    BSTNode(Element<T> &x) { data = x.key; };

    int height();
    int weight();
    int heightBF();
    int weightBF();

  private:
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

    int height();
    int weight();
    int heightBF();
    int weightBF();

  private:
    std::shared_ptr<BSTNode<T>> root;
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
    for (std::shared_ptr<BSTNode<T>> t{root}; t;) {
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
    if (root) {
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
    int leftHeight = (LeftChild) ? LeftChild->height() : -1;
    int rightHeight = (RightChild) ? RightChild->height() : -1;
    return 1 + std::max(leftHeight, rightHeight);
}

template <class T>
int BSTNode<T>::weight() {
    int leftWeight = (LeftChild) ? LeftChild->weight() : 0;
    int rightWeight = (RightChild) ? RightChild->weight() : 0;
    return 1 + leftWeight + rightWeight;
}

template <class T>
int BSTNode<T>::heightBF() {
    int leftHeight = (LeftChild) ? LeftChild->height() : -1;
    int rightHeight = (RightChild) ? RightChild->height() : -1;
    return leftHeight - rightHeight;
}

template <class T>
int BSTNode<T>::weightBF() {
    int leftWeight = (LeftChild) ? LeftChild->weight() : 0;
    int rightWeight = (RightChild) ? RightChild->weight() : 0;
    return leftWeight - rightWeight;
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
}
