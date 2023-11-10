#include <iostream>
#include <string>

class Stack{
    private:
        int top;
        int arr[5];
    public:
        Stack ()
        {
            top = -1;
            // Emptying the stack
            for (int i = 0; i < 5; ++i) {
                arr[i] = 0;
            }
        }

        //Checking if the stack is empty
        bool isEmpty()
        {
            if(top == -1){
                return true;
            }
            else{
                return false;
            }
        }

        // Checking if the stack is full
        bool isFull()
        {
            if(top ==4){
                return true;
            }
            else
            {
                return false;
            }
        }

        void push(int val)
        {
            if(isFull())
            {
               std::cout << "Stack overflow" << std::endl;
            }
            else
            {
                top++;
                arr[top] = val;
            }
        }
        // Removing the last number of the stack
        int pop()
        {
            if(isEmpty())
            {
                std::cout << "Stack underflow" << std::endl;
                return 0;
            }
            else
            {
                int popValue = arr[top];
                // It has to be zero after taking the number
                arr[top] = 0;
                top--;
                return popValue;
            }
        }

        int count()
        {
            return(top+1);
        }


        int peek(int pos)
        {
            if (isEmpty())
            {
                std::cout << "Stack underflow" << std::endl;
                return 0;
            }
            else
            {
                return arr[pos];
            }
        }


        void change(int pos, int val)
        {
            arr[pos] = val;
            std::cout << "Value changed at location" << pos << std::endl;
        }

        void display()
        {
            std::cout << "All values in the stack are " << std::endl;
            for (int i = 4; i >= 0 ; i--)
            {
                std::cout << arr[i] << std::endl;
            }
        }
        void reverse()
        {
            Stack tempStack;
            while (!isEmpty())
            {
               tempStack.push(pop());
            }
            while (!tempStack.isEmpty())
            {
                push(tempStack.pop());
            }
        }




};

int main()
{

    Stack s1;
    int option, position, value;

    do
    {
        std::cout << "What operation do you want to perform? Select option number. Enter 0 to exit" << std::endl;
        std::cout << "1. Push()" << std::endl;
        std::cout << "2. Pop()" << std::endl;
        std::cout << "3. isEmpty()" << std::endl;
        std::cout << "4. isFull()" << std::endl;
        std::cout << "5. peek()" << std::endl;
        std::cout << "6. count()" << std::endl;
        std::cout << "7. change()" << std::endl;
        std::cout << "8. display()" << std::endl;
        std::cout << "9. reverse()" << std::endl;
        std::cout << "10. Clear Screen" << std::endl << std::endl;

        std::cin >> option;
        switch (option)
        {
            case 0:
                break;
            case 1:
                std::cout << "Enter an item to push in the stack" << std::endl;
                std::cin >> value;
                s1.push(value);
                break;
            case 2:
               std::cout << "Pop function called - Poped value " << s1.pop() << std::endl;
               break;
            case 3:
                if (s1.isEmpty())
                {
                    std::cout << "Stack is empty" << std::endl;
                }
                else
                {
                    std::cout << "Stack is not empty" << std::endl;
                }
                break;
            case 4:
                if (s1.isFull())
                {
                    std::cout << "Stack is full" << std::endl;
                }
                else
                {
                    std::cout << "Stack is not full" << std::endl;
                }
                break;
            case 5:
                std::cout << "Enter the position" << std::endl;
                std::cin >> position;
                std::cout << "Peek function called - Value at position "<< position << " is " << std::endl << s1.peek(position) << std::endl;
                break;
            case 6:
                std::cout << "The number of items in the stack are " << s1.count() << std::endl;
                break;
            case 7:
                std::cout << "Enter the value you want to change. " << std::endl;
                std::cin >> value;
                std::cout << "Enter the position you want to put in." << std::endl;
                std::cin >> position;
                s1.change(position,value);
                break;
            case 8:
                std::cout << "Display function called. " << std::endl;
                s1.display();
                break;
            case 9:
                if (s1.isEmpty())
                {
                    std::cout << "Stack is empty, it can not be reversed. " << std::endl;
                }
                else
                {
                    s1.reverse();
                    std::cout << "Stack has been reversed." << std::endl;
                }

                break;
            case 10:
                system("cls");
                break;
            default:
                std::cout<<"Enter proper option number" << std::endl;
        }


    } while (option != 0);

    return 0;
}
