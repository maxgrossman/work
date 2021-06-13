#include "../include/heap.h"

void heapify_array(std::vector<int> &unsorted_elements) {
    int root_index = unsorted_elements.size() / 2 - 2;
    for (; root_index >= 0; --root_index)
        heapify(unsorted_elements, root_index);
}
void heapify_array_optimized(std::vector<int> &unsorted_elements) {
    // start with the last node that has a child.
    int root_index = (unsorted_elements.size() - 2) / 2;
    for (; root_index >= 0; --root_index)
        heapify(unsorted_elements, root_index);
}

void swap(std::vector<int> &elements, int root_index, int largest) {
    int temp_largest = elements[largest];
    elements[largest] = elements[root_index];
    elements[root_index] = temp_largest;
}

void heapify(std::vector<int> &unsorted_elements, int root_index) {
    int left_index = 2 * root_index + 1;
    int right_index = 2 * root_index + 2;
    int largest = root_index;

    // find the index of the largest amongst the left, root, and right
    if (left_index < unsorted_elements.size() && unsorted_elements[left_index] > unsorted_elements[largest])
        largest = left_index;
    if (right_index < unsorted_elements.size() && unsorted_elements[right_index] > unsorted_elements[largest])
        largest = right_index;

    // if the index is not the root, then swap the root with the largest
    if (largest != root_index) {
        swap(unsorted_elements, root_index, largest);
        heapify(unsorted_elements, largest);
    }
}

void meld(Heap * h1, Heap * h2) {
    h1->elements.insert(h1->elements.end(), h2->elements.begin(), h2->elements.end());
    heapify_array(h1->elements);
}

int find_max(Heap * h) { return h->elements[0]; }
int find_min_of_max_heap(Heap * h) {
    int min = h->elements[0];
    for (const int element: h->elements) {
        if (element < min)
            min = element;
    }
    return min;
}
void delete_max(Heap * h) {
    // swap with smallest and delete
    swap(h->elements, 0, h->elements.size() - 1);
    h->elements.pop_back();
    // re-heapify the heap
    heapify(h->elements, 0);
}
int extract_max(Heap * h) {
    int max = h->elements[0];
    delete_max(h);
    return max;
}
void replace_max(Heap * h, int value) {
    h->elements[0] = value;
    heapify(h->elements, 0);
}
