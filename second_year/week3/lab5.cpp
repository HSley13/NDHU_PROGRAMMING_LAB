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
        Node *buf = new Node(rand());

        buf->setNext(list);

        if (list != NULL)
            list->setPre(buf);

        list = buf;
    }

    void bubbleSort() {
        Node *current{list};
        bool swap{false};

        do {
            while (current != nullptr && current->getNext() != nullptr) {
                if (current->getData() > current->getNext()->getData()) {
                    int temp = current->getData();
                    current->setData(current->getNext()->getData());
                    current->getNext()->setData(temp);

                    swap = true;
                }
                current = current->getNext();
            }
        } while (swap);
    }

    void selectionSort() {
        Node *current{list};

        while (current != nullptr) {
            Node *min{current};
            Node *next{current->getNext()};

            while (next != nullptr) {
                if (min->getData() > next->getData())
                    min = next;

                next = next->getNext();
            }

            if (min != current) {
                int temp = current->getData();
                current->setData(min->getData());
                min->setData(temp);
            }
            current = current->getNext();
        }
    }

    void insertionSort() {
        Node *current{list};
        Node *sorted{nullptr};

        while (current != nullptr) {
            Node *next = current->getNext();

            if (sorted == nullptr || current->getData() < sorted->getData()) {
                current->setNext(sorted);
                sorted = current;
            } else {
                Node *sorted_current = sorted;

                while (sorted_current->getNext() != nullptr && sorted_current->getNext()->getData() < current->getData()) {
                    sorted_current = sorted_current->getNext();
                }

                current->setNext(sorted_current->getNext());
                sorted_current->setNext(current);
            }
            current = next;
        }
        list = sorted;
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

    l = new List(10);
    l->print();
    l->insertionSort();
    l->print();

    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
}
