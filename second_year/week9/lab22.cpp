#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <vector>

template <class T>
class Node {
  public:
    Node() : data(std::make_unique<T>()) {}

    Node(T d) : data(std::make_unique<T>(d)) {}

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

  private:
    std::unique_ptr<T> data;
};

template <class T>
class ListNode : public Node<T> {
  public:
    ListNode() : Node<T>(), prev(nullptr), next(nullptr) {}

    ListNode(T d) : Node<T>(d), prev(nullptr), next(nullptr) {}

    ListNode(std::shared_ptr<ListNode<T>> p, std::shared_ptr<ListNode<T>> n)
        : Node<T>(), prev(p), next(n) {}

    ListNode(T d, std::shared_ptr<ListNode<T>> p, std::shared_ptr<ListNode<T>> n)
        : Node<T>(d), prev(p), next(n) {}

    std::shared_ptr<ListNode<T>> getNext() const {
        return next;
    }

    std::shared_ptr<ListNode<T>> getPrev() const {
        return prev;
    }

    void setNext(std::shared_ptr<ListNode<T>> n) {
        next = n;
    }

    void setPrev(std::shared_ptr<ListNode<T>> p) {
        prev = p;
    }

  private:
    std::shared_ptr<ListNode<T>> prev;
    std::shared_ptr<ListNode<T>> next;
};

template <class T>
class LinkList {
  public:
    LinkList() : head(nullptr), tail(nullptr) {}

    void addFromHead(T d) {
        auto node{std::make_shared<ListNode<T>>(d)};
        if (head != nullptr) {
            head->setPrev(node);
        }

        node->setNext(head);
        head = node;
        if (tail == nullptr) {
            tail = head;
        }
    }

    void addFromTail(T d) {
        auto node{std::make_shared<ListNode<T>>(d)};
        if (tail != nullptr) {
            tail->setNext(node);
        }

        node->setPrev(tail);
        tail = node;
        if (head == nullptr)
            head = tail;
    }

    std::shared_ptr<ListNode<T>> removeFromHead() {
        std::shared_ptr<ListNode<T>> n{head};
        if (head != nullptr) {
            head = head->getNext();
            if (head != nullptr)
                head->setPrev(nullptr);
            else
                tail = nullptr;
            n->setNext(nullptr);
        }
        return n;
    }

    std::shared_ptr<ListNode<T>> removeFromTail() {
        std::shared_ptr<ListNode<T>> n{tail};
        if (tail != nullptr) {
            tail = tail->getPrev();

            if (tail != nullptr)
                tail->setNext(nullptr);
            else
                head = nullptr;
            n->setPrev(nullptr);
        }
        return n;
    }

    void print() const {
        std::shared_ptr<ListNode<T>> j{head};
        while (j != nullptr) {
            std::cout << *j << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }

    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;
};

template <class V, class E>
class WeightedGraphEdge;

template <class V, class E>
class WeightedGraphVertex : public Node<V> {
  public:
    WeightedGraphVertex() : Node<V>(), list(std::make_shared<LinkList<WeightedGraphEdge<V, E> *>>()) {}

    WeightedGraphVertex(V d) : Node<V>(d), list(std::make_shared<LinkList<WeightedGraphEdge<V, E> *>>()) {}

    void addEdge(std::shared_ptr<WeightedGraphEdge<V, E>> edge) {
        list->addFromTail(edge.get());
    }

    std::shared_ptr<ListNode<WeightedGraphEdge<V, E> *>> operator[](int n) {
        std::shared_ptr<ListNode<WeightedGraphEdge<V, E> *>> cur{list->head};

        int i{0};
        while (cur != nullptr) {
            if (i == n) {
                return cur;
            }

            cur = cur->getNext();
            i++;
        }
        return nullptr;
    }

  private:
    std::shared_ptr<LinkList<WeightedGraphEdge<V, E> *>> list;
};

template <class V, class E>
class WeightedGraphEdge : public Node<E> {
  public:
    WeightedGraphEdge() : Node<E>(), end{nullptr, nullptr} {}

    WeightedGraphEdge(E d) : Node<E>(d), end{nullptr, nullptr} {}

    WeightedGraphEdge(E d, std::shared_ptr<WeightedGraphVertex<V, E>> v1, std::shared_ptr<WeightedGraphVertex<V, E>> v2)
        : Node<E>(d), end{v1, v2} {}

    std::shared_ptr<WeightedGraphVertex<V, E>> getAnotherEnd(std::shared_ptr<WeightedGraphVertex<V, E>> v) {
        return (v != end[0]) ? end[0] : end[1];
    }

  private:
    std::shared_ptr<WeightedGraphVertex<V, E>> end[2];
};

template <class V, class E>
class WeightedGraph {
  public:
    WeightedGraph() : vertexCount(0), edgeCount(0), vertex(std::make_shared<LinkList<std::shared_ptr<WeightedGraphVertex<V, E>>>>()),
                      edge(std::make_shared<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>>()) {}

    std::shared_ptr<WeightedGraphVertex<V, E>> operator[](int n) {
        std::shared_ptr<ListNode<std::shared_ptr<WeightedGraphVertex<V, E>>>> cur = vertex->head;

        int i{0};
        while (cur != nullptr) {
            if (i == n) {
                return cur->getData();
            }

            cur = cur->getNext();
            i++;
        }
        return nullptr;
    }

    void addLink(std::shared_ptr<WeightedGraphVertex<V, E>> v1, std::shared_ptr<WeightedGraphVertex<V, E>> v2, E w) {
        auto edge{std::make_shared<WeightedGraphEdge<V, E>>(w, v1, v2)};

        v1->addEdge(edge);
        if (v1 != v2) {
            v2->addEdge(edge);
        }

        this->edge->addFromTail(edge);
    }

    std::shared_ptr<WeightedGraphVertex<V, E>> addVertex(V d) {
        auto v{std::make_shared<WeightedGraphVertex<V, E>>(d)};

        vertex->addFromTail(v);
        vertexCount++;

        return v;
    }

    void adjList() {
        std::shared_ptr<ListNode<std::shared_ptr<WeightedGraphVertex<V, E>>>> cur{vertex->head};

        while (cur != nullptr) {
            auto temp = cur->getData();
            std::cout << *temp << ": ";
            std::shared_ptr<ListNode<WeightedGraphEdge<V, E> *>> e = (*temp)[0];

            while (e != nullptr) {
                std::cout << e->getData()->getAnotherEnd(temp) << "(" << e->getData()->getData() << ") ";
                e = e->getNext();
            }

            std::cout << std::endl;
            cur = cur->getNext();
        }
    }

    std::shared_ptr<WeightedGraph> minimumSpanningTree(std::shared_ptr<WeightedGraphVertex<V, E>> start) {
        auto mst{std::make_shared<WeightedGraph<V, E>>()};

        std::vector<bool> visited(vertexCount, false);
        std::vector<E> minEdge(vertexCount, std::numeric_limits<E>::max());
        minEdge[start->getData()] = 0;

        auto compare = [&](std::shared_ptr<WeightedGraphVertex<V, E>> a, std::shared_ptr<WeightedGraphVertex<V, E>> b) {
            return minEdge[a->getData()] > minEdge[b->getData()];
        };

        std::priority_queue<std::shared_ptr<WeightedGraphVertex<V, E>>, std::vector<std::shared_ptr<WeightedGraphVertex<V, E>>>, decltype(compare)> pq(compare);
        pq.push(start);

        while (!pq.empty()) {
            auto u{pq.top()};
            pq.pop();

            if (visited[u->getData()]) {
                continue;
            }

            visited[u->getData()] = true;

            for (std::shared_ptr<ListNode<WeightedGraphEdge<V, E> *>> e{(*u)[0]}; e != nullptr; e = e->getNext()) {
                auto edge{e->getData()};
                auto v{edge->getAnotherEnd(u)};

                if (!visited[v->getData()] && minEdge[v->getData()] > edge->getData()) {
                    minEdge[v->getData()] = edge->getData();
                    pq.push(v);
                    mst->addLink(u, v, edge->getData());
                }
            }
        }
        return mst;
    }

  private:
    int vertexCount;
    int edgeCount;
    std::shared_ptr<LinkList<std::shared_ptr<WeightedGraphVertex<V, E>>>> vertex;
    std::shared_ptr<LinkList<std::shared_ptr<WeightedGraphEdge<V, E>>>> edge;
};

int main(void) {
    std::shared_ptr<WeightedGraph<char, int>> g{std::make_shared<WeightedGraph<char, int>>()};
    std::shared_ptr<WeightedGraph<char, int>> tree;

    srand(time(NULL));

    for (int j{0}; j < 5; j++) {
        g->addVertex(j + 'a');
    }

    for (int j{0}; j < 5; j++) {
        int k{rand() % 5};
        int i{rand() % 5};

        while (k == i) {
            k = rand() % 5;
        }

        g->addLink((*g)[i], (*g)[k], rand() % 10 + 1);
    }

    g->adjList();

    std::cout << "MST:" << std::endl;

    tree = g->minimumSpanningTree((*g)[0]);
    tree->adjList();
}
