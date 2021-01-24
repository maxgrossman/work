#include "../include/linked_list_queue.h"
#include "../../../linked_list/include/linked_list.h"

/**
 * DESC: removes the current tail's value, deletes it, and sets the node to its left to be the tail
 * TIME: Worst case is 0(N-1), best case is O(1)
 */
int LinkedListQueue::dequeue() {
    return queue.popfront();
};
/**
 * DESC: creates a new node with provided value and makes it the linked list tail
 * TIME: O(1)
 */
void LinkedListQueue::enqueue(int value) {
    queue.pushback(value);
};

/**
 * DESC: returns true if nothing is in the list.
 * TIME: O(1)
 */
bool LinkedListQueue::empty() {
    return queue.empty();
}
