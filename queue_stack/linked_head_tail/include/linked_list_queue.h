#include "../../../linked_list/include/linked_list.h"

class LinkedListQueue {
    private:
        LinkedList queue;
    public:
        int dequeue();
        void enqueue(int value);
        bool empty();
};
