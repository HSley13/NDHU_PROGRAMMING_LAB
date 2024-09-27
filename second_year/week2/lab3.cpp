#include <iostream>
#include <cstring>

#define SIZE 100

class Stack
{
public:
    Stack()
    {
        top = 0;
    }

    int push(int data)
    {
    }

    int *pop()
    {
    }

private:
    int data[SIZE];
    int top;
};

int main(void)
{
    int data, *temp;
    char command[50];

    Stack *stack = new Stack();

    while(1)
    {
        std::cin >> command;

        if(strcmp(command, "exit") == 0) 
          break;
        else if(strcmp(command, "push") == 0)
        {
            std::cout << "Please input a integer data:";
            std::cin >> data;

            (stack->push(data) == 1) ? std::cout << "Successfully push data " << data << " into stack.\n"; : std::cout << "Failed to push data into stack.\n";
        }
        else(strcmp(command, "pop") == 0) 
        {
            temp = stack->pop();
            (temp == NULL) ? std::cout << "Failed to pop a data from stack.\n"; : std::cout << "Pop data " << *temp << " from stack.\n" << endl;
        }
    }
}
