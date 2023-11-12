#include <iostream>

class Node
{
    public:
        int key;
        int data;
        Node* next;

        Node()
        {
            key = 0;
            data = 0;
            next = NULL;
        }
        Node(int k, int d)
        {
            key = k;
            data = d;
        }
};

class SinglyLinkedList
{
    public:
        Node* head;

        SinglyLinkedList()
        {
            head=NULL;

        }
        SinglyLinkedList(Node *n)
        {
            head = n;
        }

        // 1. Checks if the node exists using key value
        Node* nodeExists(int k)
        {
            Node* temp = NULL;

            Node* ptr = head;
            while (ptr!=NULL)
            {
                if (ptr ->key==k)
                {
                    temp = ptr;
                }
                ptr = ptr->next;
            }
            return temp;
        }
        //2. Append a node to the list(add in the end of list)
        void appendNode(Node *n)
        {
            if (nodeExists(n->key) != NULL)
            {
                std::cout << "Node already exists with key value: " << n->key <<". Append another node with different key value" << std::endl;

            }
            else
            {
                if (head==NULL)
                {
                    head = n;
                    std::cout << "Node appended" << std::endl;
                }
                else
                {
                    Node* ptr = head;
                    while (ptr->next != NULL)
                    {
                        ptr = ptr->next;
                    }
                    ptr->next = n;
                    std::cout << "Node appended" << std::endl;
                }
            }
        }
};


int main()
{
    return 0;
}
