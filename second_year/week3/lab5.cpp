#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

class Node
{
public:
	Node()
	{
		next = NULL;
		pre = NULL;
	}

	Node(int n)
	{
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

class List
{
public:
	List() { list = NULL; }
	List(int n) { generate(n); }
	
	void generate(int n)
	{
		list = NULL;

		for(int j{0}; j < n; j++)
			generate();
	}
	
	void generate()
	{
		Node *buf = new Node(rand());

		buf->setNext(list);

		if(list != NULL)
			list->setPre(buf);
  
		list = buf;
	}
	
	void bubbleSort()
	{
	}
	
	void selectionSort()
	{
	}
	
	void insertionSort()
	{
	} 
	
	void print()
	{
		Node *cur = list;

		while(cur != NULL)
		{
			std::cout << cur->getData() << " ";

			cur = cur->getNext();
		}

    std::cout << std::endl;
	}

private:
	Node *list;
};

int main(void)
{
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

