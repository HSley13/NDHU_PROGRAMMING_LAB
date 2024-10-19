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

    void bubbleSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        bool swap{true};
        while (swap) {
            Node *current{list};
            swap = false;
            while (current->getNext() != nullptr) {
                if (current->getData() > current->getNext()->getData()) {
                    int temp = current->getData();
                    current->setData(current->getNext()->getData());
                    current->getNext()->setData(temp);
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
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        Node *sorted = new Node(0);
        Node *current = list;

        while (current != nullptr) {
            Node *next = current->getNext();

            Node *temp = sorted;
            while (temp->getNext() != nullptr && temp->getNext()->getData() < current->getData()) {
                temp = temp->getNext();
            }

            if (temp != current) {
                int temp2 = current->getData();
                current->setData(temp->getData());
                temp->setData(temp2);
            }

            if (current->getPre())
                current->getPre()->setNext(current->getNext());
            if (current->getNext())
                current->getNext()->setPre(current->getPre());

            current->setPre(temp);
            if (temp->getNext())
                temp->getNext()->setPre(current);
            temp->setNext(current);

            current = next;
        }

        list = sorted->getNext();
        list->setPre(nullptr);
        delete sorted;
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
    l->insertionSort();
    l->print();
    std::cout << std::endl;

    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
}
