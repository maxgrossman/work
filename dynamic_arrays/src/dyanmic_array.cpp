#include "../include/dyanmic_array.h"

static const int START_CAPACITY = 2;
/**
 * Constructs DynamicArrayJustInt of capacity START_CAPACITY
 * and implicit size of 0;
 */
DynamicArrayJustInt::DynamicArrayJustInt() {
    capacity = START_CAPACITY;
    size = 0;
    mutable_array = new int[capacity]{ 0 };
}
/**
 * removes element at index i
 * @param {int} i index at which to remove an element
 */
void DynamicArrayJustInt::delete_at(int i) {
    int *next_array = new int[capacity];
    int *next_ptr = next_array;          // ptr at beginning of next_array
    int *end = mutable_array + size;     // ptr to end of mutable_array
    for (int *mutable_ptr = mutable_array; mutable_ptr < end; ++mutable_ptr) {
        if ((mutable_ptr - mutable_array) != i) { // really only remove at index i :).
            *next_ptr = *mutable_ptr; // this copies over the value
            next_ptr++; // this increments the next pointer;
        }
    }
    delete[] mutable_array;
    mutable_array = next_array;
    size--;
}
/**
 * Finds and returns first index with value, or -1 if nothing matched
 * @param {int} value, the value to match against
 * @return {int} the value that maches our index
 */
int DynamicArrayJustInt::find(int value) {
    int *end = mutable_array + size;
    int *mutable_ptr = mutable_array;
    while (mutable_ptr < end) {
        if (*mutable_ptr == value) {
            return mutable_ptr - mutable_array;
        }
        mutable_ptr++;
    }
    return -1;
}
/*
 * Returns element in array at index i
 * @param {int} i array index
 * @return {int} element at index i
 */
int DynamicArrayJustInt::get(int i) {
    if (i < 0 || i > size) {
        throw "provided i is out of range";
    }
    return mutable_array[i];
}
/**
 * @return current size of the array
 */
int DynamicArrayJustInt::get_size() { return size; }
/**
 * inserts value at index i
 * @param {int} i the index to insert at
 * @param {int} value the value to insert at i
 */
void DynamicArrayJustInt::insert(int i, int value) {
    if (i < 0 || i > size) {
        throw "provided i is out of range";
    }

    // if inserting makes size === capacity, insert into new array
    // otherwise, just the plain jane mutable_array
    bool need_new_array = capacity == (size + 1);
    if (need_new_array) {
        capacity *= 2;
    }
    int *next_array = new int[capacity];
    int *next_ptr = next_array;
    int *end = mutable_array + size;

    for (int *mutable_ptr = mutable_array; mutable_ptr < end; ++mutable_ptr) {
        if ((mutable_ptr - mutable_array) == i) { // if ptr arithmatic says I'm at i
            *next_ptr = value;                    // then insert value
            next_ptr++;
        }
        *next_ptr = *mutable_ptr;
        next_ptr++;
    }

    delete[] mutable_array;
    mutable_array = next_array;
    size++;
}
/**
 * Removes and returns the value at index i. if no values passed, last index
 * is assumed
 * @param {int} i the value to remove's index
 * @return {int} value at index i
 */
int DynamicArrayJustInt::pop(int i) {
    if (i == -1) { // if it's the default value, set to end of the list
        i = size - 1;
    }

    int *next_array = new int[capacity];
    int *next_ptr = next_array;
    int *end = mutable_array + size;
    int pop_value;

    for (int *mutable_ptr = mutable_array; mutable_ptr < end; mutable_ptr++) {
        if ((mutable_ptr - mutable_array) == i) { // if ptr math == index, set it to pop
            pop_value = *mutable_ptr;
        } else { // otherwise copy over.
            *next_ptr = *mutable_ptr;
        }
    }

    delete[] mutable_array;
    mutable_array = next_array;
    size--;

    return pop_value;
}
/**
 * inserts value at the end of the list
 * @param {int} value
 */
void DynamicArrayJustInt::pushback(int value) {
    if (size == capacity) resize();
    mutable_array[size] = value;
    size++;
}
/**
 * removes first instance of value from array
 */
void DynamicArrayJustInt::remove(int value) {
    int *next_array = new int[capacity];
    int *next_ptr = next_array;
    int *end = mutable_array + size;
    bool removed = false;

    for (int *mutable_ptr = mutable_array; mutable_ptr < end; ++mutable_ptr) {
        if (*mutable_ptr != value || removed) { // don't match or we already matched, copy over.
            *next_ptr = *mutable_ptr;
            next_ptr++;
        } else { // match first time, flip this to true
            removed = true;
        }
    }
    delete[] mutable_array;
    mutable_array = next_array;
    if (removed) { // be smart, only decrement 1 if we found the value in the array
        size--;
    }
}
/**
 * resizes array to have 2x capacity
 */
void DynamicArrayJustInt::resize() {
    // make new array
    capacity *= 2;
    int *next_array = new int[capacity];
    int *end = mutable_array + size; // ptr to the end of our array
    int *next_ptr = next_array;      // ptr to the start of the next array;

    // until we get to the end of the data in the mutable array,
    // copy the values over to the next_array
    for (int *mutable_ptr = mutable_array; mutable_ptr < end; ++mutable_ptr) {
        *next_ptr = *mutable_ptr;
        next_ptr++;
    }

    delete[] mutable_array;
    mutable_array = next_array;
}
/**
 * sets element i in array to value
 * @param {int} i index to set
 * @param {int} value to set at index i
 */
void DynamicArrayJustInt::set(int i, int value) {
    if (i < 0 || i > size) {
        throw "provided i is out of range";
    }
    mutable_array[i] = value;
    size++;
}
