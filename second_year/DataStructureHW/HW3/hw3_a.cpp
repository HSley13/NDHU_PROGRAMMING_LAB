#include <memory>

template <class T>
class List;

template <class T>
class ListNode {
    friend class List<T>;

  private:
    T data;
    std::shared_ptr<ListNode<T>> link;
};

template <class T>
class List {
  public:
    List() : first(nullptr), last(nullptr) {}
    void Attach(T k);

  private:
    std::shared_ptr<ListNode<T>> first;
    std::shared_ptr<ListNode<T>> last;
};

template <class Type>
void List<Type>::Attach(Type k) {
    std::shared_ptr<ListNode<Type>> newnode = std::make_shared<ListNode<Type>>();
    newnode->data = k;
    if (first == nullptr) {
        first = last = newnode;
    } else {
        last->link = newnode;
        last = newnode;
    }
}
