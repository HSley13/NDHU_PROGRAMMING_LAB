#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 100

using namespace std;

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
        int j;
        list = NULL;
        for (j = 0; j < n; j++)
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
    }

    void selectionSort() {
    }

    void insertionSort() {
    }

    void print() {
        Node *cur = list;
        while (cur != NULL) {
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << endl;
    }

  private:
    Node *list;
};

int main() {
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
