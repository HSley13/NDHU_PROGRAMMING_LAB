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
      if(top == SIZE) return -1;
    
      this->data[top] = data;
      top++;

      return 1;
    }

    int *pop()
    {
      if(top == 0) return nullptr;

      top--;
      return &data[top];
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

            (stack->push(data) == 1) ? std::cout << "Successfully push data " << data << " into stack." << std::endl : std::cout << "Failed to push data into stack." << std::endl;
        }
        else if(strcmp(command, "pop") == 0) 
        {
            temp = stack->pop();
            (temp == NULL) ? std::cout << "Failed to pop a data from stack." << std::endl : std::cout << "Pop data " << *temp << " from stack.\n" << std::endl;
        }
    }
}
