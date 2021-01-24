#include "../include/fixed_size_array_queue.h"

/**
 * Makes an array of provided size,
 * then sets the read and write pointers
 * to the start of the new array.
 */
FixedSizeArrayQueue::FixedSizeArrayQueue(int size) {
    arr = new int[size];
    this->size = size;
    read_idx = 0; write_idx = 0;
}
/**
 * Sets moves write_idx over one and sets puts value in it.
 * If doing so would throw overwrite current read_idx, then throw an error.
 */
void FixedSizeArrayQueue::enqueue(int value) {
    int next_write_idx = (write_idx == (size - 1)) ? 0 : write_idx + 1;
    //we need to be able to distinguish read/write index so cannot allow a enqueue that would make them equal.
    if (next_write_idx == read_idx) {
        throw EnqueueException();
    } else {
        arr[write_idx] = value;
        write_idx = next_write_idx;
    }
}
/**
 * Returns and removes the value in read_idx, then increments it to the next arr pos.
 * If the array is empty, we throw an error.
 */
int FixedSizeArrayQueue::dequeue() {
    if (empty()) {
        throw DequeueException();
    }
    int to_return = arr[read_idx];
    read_idx = (read_idx == size - 1) ? 0 : read_idx + 1;
    return to_return;
}
/**
 * Empty happens if read and write index are the same.
 */
bool FixedSizeArrayQueue::empty() {
    return read_idx == write_idx;
}
