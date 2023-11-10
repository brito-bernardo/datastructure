#include <iostream>


class Queue{
    private:
        int front;
        int rear;
        int arr[5];
    public:
        Queue()
        {
            front = -1;
            rear = -1;
            for (int i = 0; i < 5; ++i)
            {
                arr[i] = 0;
            }
        }

        // Emptying the queue
        bool isEmpty()
        {
            if (front == -1 && rear == -1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool isFull()
        {
            if (rear == 4)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        void enqueue(int val)
        {
            if (isFull())
            {
                std::cout << "Queue is Full" << std::endl;
                return;
            }
            else if(isEmpty())
            {
                rear = 0;
                front = 0;
                arr[rear] = val;
            }
            else
            {
                rear++;
                arr[rear] = val;
            }
        }

        int dequeue()
        {
            int x;
            if(isEmpty())
            {
                std::cout << "Queue is empty" << std::endl;
                return 0;
            }
            else if(front == rear)
            {
                x = arr[front];
                arr[front] = 0;
                rear = -1;
                front = -1;
                return x;

            }
            else
            {
              x = arr[front];
              arr[front] = 0;
              front++;
              return x;
            }
        }

        int count()
        {
            return (rear-front + 1);
        }

        void display()
        {
            std::cout << "All values in the queue are: " << std::endl;
            for (int i = 0; i < 5; ++i) {
                std::cout<<arr[i] << "  ";
            }
        }


};

int main()
{
    Queue q1;
    int option, value;

    do{
        std::cout << "\n\nWhat operation do you want to perform? Select option number. Enter 0 to exit. " << std::endl;
        std::cout << "1. Enqueue()" << std::endl;
        std::cout << "2. Dequeue()" << std::endl;
        std::cout << "3. isEmpty()" << std::endl;
        std::cout << "4. isFull()" << std::endl;
        std::cout << "5. count()" << std::endl;
        std::cout << "6. display()" << std::endl;
        std::cout << "7. Clear Screen" << std::endl << std::endl;

        std::cin >> option;

        switch (option)
        {
            case 0:
                break;
            case 1:
                std::cout<<"Enqueue operation \nEnter an item to enqueue in the queue" << std::endl;
                std::cin >> value;
                q1.enqueue(value);
                break;
            case 2:
                std::cout << "Dequeue opeartion \nDequeued value: " << q1.dequeue() << std::endl;
                break;
            case 3:
                if (q1.isEmpty())
                {
                    std::cout << "Queue is empty" << std::endl;
                }
                else
                {
                    std::cout << "Queue is not empty" << std::endl;
                }
                break;
            case 4:
                if (q1.isFull())
                {
                    std::cout << "Queue is full" << std::endl;
                }
                else
                {
                    std::cout << "Queue is noit full" << std::endl;
                }
                break;
            case 5:
                std::cout << "Count operation \n Count of items in queue: " << q1.count() << std::endl;
                break;

            case 6:
                std::cout << "Display function called " << std::endl;
                q1.display();
                break;
            case 7:
                system("cls");
                break;
            default:
                std::cout << "Enter proper option number" << std::endl;
                break;
        }

    } while (option != 0);

    return 0;
}
