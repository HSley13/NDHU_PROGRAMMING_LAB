#include <cstdio>
#include <ctime>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_set>

template <class T>
class Node {
  public:
    Node() : data(std::make_shared<T>()) {}

    Node(T d) : data(std::make_shared<T>(d)) {}

    Node &operator=(T d) {
        *data = d;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Node &n) {
        out << *(n.data);
        return out;
    }

    void setData(T d) {
        *data = d;
    }

    T &getData() const {
        return *data;
    }

  protected:
    std::shared_ptr<T> data;
};

template <class T>
class ListNode : public Node<T> {
  public:
    ListNode() : Node<T>(), prev(nullptr), next(nullptr) {}

    ListNode(T d) : Node<T>(d), prev(nullptr), next(nullptr) {}

    std::shared_ptr<ListNode> getNext() const {
        return next;
    }

    std::shared_ptr<ListNode> getPrev() const {
        return prev;
    }

    void setNext(std::shared_ptr<ListNode> n) {
        next = n;
    }

    void setPrev(std::shared_ptr<ListNode> p) {
        prev = p;
    }

    ListNode &operator=(T d) {
        this->setData(d);
        return *this;
    }

  private:
    std::shared_ptr<ListNode> prev, next;
};

template <class T>
class LinkList {
  public:
    LinkList() : head(nullptr), tail(nullptr) {}

    void addFromHead(T d) {
        std::shared_ptr<ListNode<T>> node{std::make_shared<ListNode<T>>(d)};
        if (head != nullptr) {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
    }

    void addFromTail(T d) {
        std::shared_ptr<ListNode<T>> node{std::make_shared<ListNode<T>>(d)};
        if (tail != nullptr) {
            tail->setNext(node);
        }

        node->setPrev(tail);
        tail = node;
        if (head == nullptr) {
            head = node;
        }
    }

    ListNode<T> &operator[](int i) {
        std::shared_ptr<ListNode<T>> current{head};
        for (int k{0}; k < i && current != nullptr; k++) {
            current = current->getNext();
        }

        if (current == nullptr) {
            throw std::invalid_argument("Index does not exist.");
        }
        return *current;
    }

    void print() const {
        std::shared_ptr<ListNode<T>> current{head};
        while (current != nullptr) {
            std::cout << *current << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }

  private:
    std::shared_ptr<ListNode<T>> head, tail;
};

template <class V, class E>
class WeightedGraphEdge;

template <class V, class E>
class WeightedGraphVertex : public Node<V> {
  public:
    WeightedGraphVertex() : Node<V>(), list(std::make_shared<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>>()) {}

    WeightedGraphVertex(V d) : Node<V>(d), list(std::make_shared<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>>()) {}

    void addEdge(std::shared_ptr<WeightedGraphEdge<V, E>> edge) {
        list->addFromTail(edge);
    }

    ListNode<std::shared_ptr<WeightedGraphEdge<V, E>>> &operator[](int n) {
        return (*list)[n];
    }

  private:
    std::shared_ptr<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>> list;
};

template <class V, class E>
class WeightedGraphEdge : public Node<E> {
  public:
    WeightedGraphEdge() : Node<E>(), end{nullptr, nullptr} {}

    WeightedGraphEdge(E d) : Node<E>(d), end{nullptr, nullptr} {}

    WeightedGraphEdge(E d, std::shared_ptr<WeightedGraphVertex<V, E>> v1, std::shared_ptr<WeightedGraphVertex<V, E>> v2) : Node<E>(d), end{v1, v2} {}

    std::shared_ptr<WeightedGraphVertex<V, E>> &getAnotherEnd(std::shared_ptr<WeightedGraphVertex<V, E>> v) {
        return (v != end[0]) ? end[0] : end[1];
    }

  private:
    std::shared_ptr<WeightedGraphVertex<V, E>> end[2];
};

template <class V, class E>
class WeightedGraph {
  public:
    WeightedGraph()
        : vertex(std::make_shared<LinkList<std::shared_ptr<WeightedGraphVertex<V, E>>>>()),
          edge(std::make_shared<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>>()) {}

    std::shared_ptr<WeightedGraphVertex<V, E>> operator[](int n) {
        try {
            return (*vertex)[n].getData();
        } catch (const std::invalid_argument &) {
            return nullptr;
        }
    }

    void addLink(std::shared_ptr<WeightedGraphVertex<V, E>> v1, std::shared_ptr<WeightedGraphVertex<V, E>> v2, E w) {
        std::shared_ptr<WeightedGraphEdge<V, E>> newEdge = std::make_shared<WeightedGraphEdge<V, E>>(w, v1, v2);
        v1->addEdge(newEdge);
        if (v1 != v2) {
            v2->addEdge(newEdge);
        }
    }

    std::shared_ptr<WeightedGraphVertex<V, E>> addVertex(V d) {
        std::shared_ptr<WeightedGraphVertex<V, E>> v{std::make_shared<WeightedGraphVertex<V, E>>(d)};
        vertex->addFromTail(v);
        return v;
    }

    void BFS(std::shared_ptr<WeightedGraphVertex<V, E>> v) {
        std::unordered_set<std::shared_ptr<WeightedGraphVertex<V, E>>> visited;
        std::queue<std::shared_ptr<WeightedGraphVertex<V, E>>> q;
        q.push(v);
        visited.insert(v);

        while (!q.empty()) {
            std::shared_ptr<WeightedGraphVertex<V, E>> current = q.front();
            q.pop();
            std::cout << current->getData() << " ";

            for (int i = 0;; i++) {
                try {
                    std::shared_ptr<WeightedGraphEdge<V, E>> edge = current->operator[](i).getData();
                    std::shared_ptr<WeightedGraphVertex<V, E>> neighbor = edge->getAnotherEnd(current);
                    if (visited.find(neighbor) == visited.end()) {
                        q.push(neighbor);
                        visited.insert(neighbor);
                    }
                } catch (const std::invalid_argument &) {
                    break;
                }
            }
        }
    }

    void DFS(std::shared_ptr<WeightedGraphVertex<V, E>> v) {
        std::unordered_set<std::shared_ptr<WeightedGraphVertex<V, E>>> visited;
        std::stack<std::shared_ptr<WeightedGraphVertex<V, E>>> s;
        s.push(v);

        while (!s.empty()) {
            std::shared_ptr<WeightedGraphVertex<V, E>> current = s.top();
            s.pop();
            if (visited.find(current) == visited.end()) {
                std::cout << current->getData() << " ";
                visited.insert(current);
                for (int i = 0;; i++) {
                    try {
                        std::shared_ptr<WeightedGraphEdge<V, E>> edge = current->operator[](i).getData();
                        std::shared_ptr<WeightedGraphVertex<V, E>> neighbor = edge->getAnotherEnd(current);
                        s.push(neighbor);
                    } catch (const std::invalid_argument &) {
                        break;
                    }
                }
            }
        }
    }

  private:
    std::shared_ptr<LinkList<std::shared_ptr<WeightedGraphVertex<V, E>>>> vertex;
    std::shared_ptr<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>> edge;
};

int main(void) {
    std::shared_ptr<WeightedGraph<char, int>> g{std::make_shared<WeightedGraph<char, int>>()};
    std::shared_ptr<LinkList<std::shared_ptr<WeightedGraphVertex<char, int>>>> node{std::make_shared<LinkList<std::shared_ptr<WeightedGraphVertex<char, int>>>>()};

    int n;
    std::scanf("%d", &n);
    std::srand(n);
    for (int j{0}; j < 26; j++) {
        node->addFromTail(g->addVertex(static_cast<char>(j + 'A')));
    }

    int k{std::rand() % 100};
    for (int j{0}; j < k; j++) {
        int a{std::rand() % 26};
        int b{std::rand() % 26};
        int w{std::rand() % 100};
        g->addLink((*node)[a].getData(), (*node)[b].getData(), w);
    }

    g->BFS((*node)[rand() % 26].getData());
    std::cout << std::endl;
    g->DFS((*node)[rand() % 26].getData());
}
