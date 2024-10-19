#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 100

class Node {
  public:
    Node() {
        next = NULL;
        pre = NULL;
    }

    Node(int n) {
        data = n;
        next = NULL;
        pre = NULL;
    }

    int getData() { return data; }

    Node *getNext() { return next; }
    Node *getPre() { return pre; }

    void setData(int d) { data = d; }
    void setNext(Node *n) { next = n; }
    void setPre(Node *p) { pre = p; }

  private:
    int data;
    Node *next, *pre;
};

class List {
  public:
    List() { list = NULL; }
    List(int n) { generate(n); }

    void generate(int n) {
        list = NULL;

        for (int j{0}; j < n; j++)
            generate();
    }

    void generate() {
        Node *buf = new Node(rand() % 10);

        buf->setNext(list);

        if (list != NULL)
            list->setPre(buf);

        list = buf;
    }

    void swapNodes(Node *node1, Node *node2) {
        if (node1 == node2) {
            return;
        }

        Node *prev1 = node1->getPre();
        Node *next1 = node1->getNext();
        Node *prev2 = node2->getPre();
        Node *next2 = node2->getNext();

        if (node1->getNext() == node2) {
            node1->setNext(next2);
            node1->setPre(node2);
            node2->setNext(node1);
            node2->setPre(prev1);

            if (prev1 != nullptr) {
                prev1->setNext(node2);
            } else {
                list = node2;
            }

            if (next2 != nullptr) {
                next2->setPre(node1);
            }
        } else if (node2->getNext() == node1) {
            node2->setNext(next1);
            node2->setPre(node1);
            node1->setNext(node2);
            node1->setPre(prev2);

            if (prev2 != nullptr) {
                prev2->setNext(node1);
            } else {
                list = node1;
            }

            if (next1 != nullptr) {
                next1->setPre(node2);
            }
        } else {
            if (prev1 != nullptr) {
                prev1->setNext(node2);
            } else {
                list = node2;
            }

            if (prev2 != nullptr) {
                prev2->setNext(node1);
            } else {
                list = node1;
            }

            if (next1 != nullptr) {
                next1->setPre(node2);
            }

            if (next2 != nullptr) {
                next2->setPre(node1);
            }

            node1->setNext(next2);
            node1->setPre(prev2);
            node2->setNext(next1);
            node2->setPre(prev1);
        }
    }

    void bubbleSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        bool swap{true};
        while (swap) {
            Node *current{list};
            swap = false;
            while (current != nullptr && current->getNext() != nullptr) {
                if (current->getData() > current->getNext()->getData()) {
                    swapNodes(current, current->getNext());
                    swap = true;
                }
                current = current->getNext();
            }
        }
    }

    void selectionSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        Node *current = list;

        while (current != nullptr) {
            Node *min = current;
            Node *next = current->getNext();

            while (next != nullptr) {
                if (next->getData() < min->getData()) {
                    min = next;
                }

                next = next->getNext();
            }

            if (min != current) {
                swapNodes(min, current);

                Node *temp = current;
                current = min;
                min = temp;
            }
            current = current->getNext();
        }
    }

    void insertionSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        Node *current = list->getNext();

        while (current != nullptr) {
            Node *next = current->getNext();
            Node *search = list;

            // Find the correct position in the sorted part of the list
            while (search != current && search->getData() < current->getData()) {
                search = search->getNext();
            }

            // If search node is different from current, we need to move current to the correct position
            if (search != current) {
                // Detach current node
                Node *prev = current->getPre();
                Node *nextCurrent = current->getNext();

                if (prev != nullptr) {
                    prev->setNext(nextCurrent);
                }

                if (nextCurrent != nullptr) {
                    nextCurrent->setPre(prev);
                }

                // Insert current node before search node
                Node *searchPrev = search->getPre();

                current->setNext(search);
                current->setPre(searchPrev);

                if (searchPrev != nullptr) {
                    searchPrev->setNext(current);
                } else {
                    list = current;
                }
                search->setPre(current);
            }
            current = next;
        }
    }

    void print() {
        Node *cur = list;

        while (cur != NULL) {
            std::cout << cur->getData() << " ";

            cur = cur->getNext();
        }
        std::cout << std::endl;
    }

  private:
    Node *list;
};

int main(void) {
    srand(time(NULL));

    List *l = new List(10);

    l->print();
    l->bubbleSort();
    l->print();
    std::cout << std::endl;

    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
    std::cout << std::endl;

    l = new List(10);
    l->print();
    l->insertionSort();
    l->print();
}
