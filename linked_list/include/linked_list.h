#ifndef LinkedList_H
#define LinkedList_H

struct Node {
    int value; // the value of the node
    struct Node* next;  // points to the next node in the list
};

class LinkedList {
    private:
        struct Node* head; // points to current head of the linked list.
        struct Node* tail;
        int size;
        void addafter(struct Node** head, struct Node** tail, struct Node** beforeNode, int value);
        void addbefore(struct Node** head, struct Node** tail, struct Node** afterNode, int value);
        void erase(struct Node** head, struct Node** tail, int value);
        Node* getNodeAt(int index);
        void insert(struct Node** head, struct Node** tail, int index,  int value);
        void pushfront(struct Node** head, struct Node** tail, int value);
        void pushback(struct Node** head, struct Node** tail, int value);
        int popback(struct Node** head, struct Node** tail);
        int popfront(struct Node** head, struct Node** tail);
        Node* nthNodeFromEnd(int n);
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
        int popback();
        int popfront();
        void pushfront(int value);
        void pushback(int value);
        void reverse();
        int topfront();
        int topback();
        int valueAt(int index);
        int nthValueFromEnd(int n);
};

#endif
