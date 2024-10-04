#include <iostream>
#include <cstring>

#define SIZE 3

class Queue
{
public:
    Queue()
    {
        top = 0;
        bot = -1;
        count = 0;
    }

    int enqueue(int data)
    {
        if (count == SIZE)
            return -1; 
        
        this->data[top] = data;
        top = (top + 1) % SIZE;

        count++;

        return 1;
    }

    int *dequeue()
    {
        if (count == 0)
            return nullptr; 

        bot = (bot + 1) % SIZE; 
        count--;

        return &data[bot];  
    }

private:
    int data[SIZE];
    int top, bot;
};

int main(void)
{
    int data, *temp;
    char command[50];

    Queue *queue = new Queue();

    while(1)
    {
        std::cin >> command;

        if(strcmp(command, "exit") == 0)
          break;
        else if(strcmp(command, "enqueue") == 0)
        {
            std::cout << "Please input a integer data:";
            std::cin >> data;

            (queue->enqueue(data) == 1) ? std::cout << "Successfully enqueue data " << data << " into queue." << std::endl : std::cout << "Failed to enqueue data into queue." << std::endl;
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            (temp == NULL) ? std::cout << "Failed to dequeue a data from queue." << std::endl : std::cout << "Dequeue data " << *temp << " from queue." << std::endl;
        }
    }
}
