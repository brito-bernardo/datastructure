#include <stdio.h>
#include "linkedlist2.h"

int main() {
    LinkedList list;
    list.insertElementAtEnd(8);
    list.showList();
    list.insertElementAtEnd(3);
    list.showList();
    list.insertElementAtEnd(2);
    list.showList();
    list.insertElementAtEnd(1);
    list.showList();
    list.insertElementAtEnd(0);
    list.showList();
    list.insertElementAtEnd(-5);
    list.showList();
    list.showList();
    list.removeElementAtPosition(2);
    list.showList();
    list.removeLastElement();
    list.showList();
    list.updateElementAtPosition(-14, 1);
    list.showList();

    return 0;
}