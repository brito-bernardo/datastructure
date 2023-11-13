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
        //3. Prepend Node - Attach a node at the start
        void prependNode(Node* n)
        {
            if (nodeExists(n->key) != NULL)
            {
                std::cout << "Node Already exists with key value: " << n->key <<". Append another niode with different Key value" << std::endl;
            }
            else
            {
                n->next = head;
                head = n;
                std::cout << "Node Prepended" << std::endl;
            }
        }
        //4. Insert a node after a paticular node in the list
        void insertNodeAfter(int k, Node *n)
        {
            Node* ptr = nodeExists(k);
            if(ptr == NULL)
            {
                std::cout << "Node Already exists with key value: " << k <<". Append another niode with different Key value" << std::endl;
            }
            else
            {
                if (nodeExists(n->key) != NULL)
                {
                    std::cout << "Node Already exists with key value: " << n->key <<". Append another niode with different Key value" << std::endl;
                }
                else
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    std::cout << "Node inserted" << std::endl;
                }
            }
        }
        //5. Deleting the node
        void deleteNodeByKey(int k)
        {
            if(head == NULL)
            {
                std::cout << "Singly linked list already empty. Cant delete" << std::endl;
            }
            else if (head != NULL)
            {
              if(head->key == k)
              {
                  head = head->next;
                  std::cout << "Node Unlied with key value: " << k << std::endl;
              }
              else
              {
                  Node* temp = NULL;
                  Node* prevptr = head;
                  Node* currentptr = head->next;
                  while (currentptr !=NULL)
                  {
                      if (currentptr->key == k)
                      {
                          temp = currentptr;
                          currentptr = NULL;
                      }
                      else
                      {
                          prevptr = prevptr->next;
                          currentptr = currentptr->next;
                      }
                  }
                  if (temp != NULL)
                  {
                      prevptr->next = temp->next;
                      std::cout << "Node unliked with keys value: " << k << std::endl;
                  }
                  else
                  {
                      std::cout << "Node doesn't exist with key value: " << k << std::endl;
                  }
              }
            }
        }
        //6. Update node
        void updateNodeByKey(int k, int d)
        {
            Node* ptr = nodeExists(k);
            if (ptr != NULL)
            {
                ptr->data = d;
                std::cout << "Node data updated sucessfully" << std::endl;
            }
            else
            {
                std::cout << "Node does not exist with key value: " << k << std::endl;
            }
        }

        //7. Print

        void printList()
        {
            if(head==NULL)
            {
                std::cout << "No nodes in singly linked list" << std::endl;
            }
            else
            {
                std::cout << "Singly linked list values: ";
                Node* temp = head;
                while (temp!=NULL)
                {
                    std::cout <<"(" << temp->key <<"," << temp->data << ") --> ";
                    temp = temp->next;
                }
            }
        }
};


int main()
{
    SinglyLinkedList s;
    int option;
    int key1,k1,data1;
    do {
        std::cout << "\nWhat operation do you want to perform? Select option number. Enter 0 to exit" << std::endl;
        std::cout << "1. appendNode()" << std::endl;
        std::cout << "2. prependNode()" << std::endl;
        std::cout << "3. insertNodeAfter()" << std::endl;
        std::cout << "4. deleteNodeByKey()" << std::endl;
        std::cout << "5. updateNodeByKey()" << std::endl;
        std::cout << "6. print()" << std::endl;
        std::cout << "7. Clear screen" << std::endl << std::endl;


        std::cin >> option;
        Node* n1 = new Node();

        switch (option) {

            case 0:
                break;
            case 1:
                std::cout << "Append node operation \nEnter key&data of the Node to be appended" << std::endl;
                std::cin>> key1;
                std::cin >>data1;
                n1->key=key1;
                n1->data=data1;
                s.appendNode(n1);
                break;
            case 2:
                std::cout << "Prepend node Operation \nEnter key & data of the node to be prepended" << std::endl;
                std::cin >>key1;
                std::cin >>data1;
                n1->key=key1;
                n1->data=data1;
                s.prependNode(n1);
                break;
            case 3:
                std::cout << "Insert Node After Operation \nEnter key of existing node after which you want to Insert this new node: " << std::endl;
                std::cin >> k1;
                std::cout << "Enter key & data of the New Node first: " << std::endl;
                std::cin >> key1;
                std::cin >> data1;
                n1->key = key1;
                n1->data = data1;

                s.insertNodeAfter(k1,n1);
                break;
            case 4:
                std::cout << "Delete Node By Key Operation \nEnter key of the node to be deleted: " << std::endl;
                std::cin >>k1;
                s.deleteNodeByKey(k1);
            case 5:
                std::cout << "Update Node By Key Operation \nEnter key & NEW data to be updated." << std::endl;
                std::cin >> key1;
                std::cin >> data1;
                s.updateNodeByKey(key1,data1);
                break;
            case 6:
                s.printList();
                break;
            case 7:
                system("cls");
                break;
            default:
                std::cout << "Enter proper option number " << std::endl;
        }
    } while (option !=0);

    return 0;
}
