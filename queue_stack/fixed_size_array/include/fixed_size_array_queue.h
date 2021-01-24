#include <exception>
#include "../../../linked_list/include/linked_list.h"
struct DequeueException: public std::exception {
    const char * what() const throw() {
        return "The queue is empty, nothing to dequeue";
    }
};

struct EnqueueException: public std::exception {
    const char * what() const throw() {
        return "Cannot enqueue since it would overwrite the next value to enqueue.";
    }
};

class FixedSizeArrayQueue {
    private:
        int read_idx;
        int write_idx;
        int* arr;
        int size;
    public:
        FixedSizeArrayQueue(int size);
        void enqueue(int value);
        int dequeue();
        bool empty();
};

