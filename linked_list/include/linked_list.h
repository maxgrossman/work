#ifndef LinkedList_H
#define LinkedList_H

struct Node {
    int value; // the value of the node
    Node* next;  // points to the next node in the list
};

class LinkedList {
    private:
        Node* head; // points to current head of the linked list.
        int size;
        Node* getNodeAt(int index);
    public:
        LinkedList();
        void addafter(Node* beforeNode, int value);
        void addbefore(Node* beforeNode, int value);
        bool empty();
        void erase(int value);
        void insert(int index, int value);
        bool find(int value);
        int getsize();
        Node* nodeAt(int index);
        void popback();
        void popfront();
        void pushfront(int value);
        void pushback(int value);
        void reverse();
        int topfront();
        int topback();
        int valueAt(int index);
        int nthValueFromEnd(int n);
        Node* nthNodeFromEnd(int n);
};

#endif
