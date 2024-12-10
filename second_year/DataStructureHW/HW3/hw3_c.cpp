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

  private:
    std::unique_ptr<BSTNode<T>> LeftChild;
    T data;
    std::unique_ptr<BSTNode<T>> RightChild;
};

template <class T>
class BST {
  public:
    std::shared_ptr<BSTNode<T>> Search(const Element<T> &x);
    std::shared_ptr<BSTNode<T>> Search(std::shared_ptr<BSTNode<T>> b, const Element<T> &x);
    std::shared_ptr<BSTNode<T>> IterSearch(const Element<T> &x);
    void Insert(const Element<T> &x);

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
