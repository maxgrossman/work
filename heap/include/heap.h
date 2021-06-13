#include <vector>

void swap(std::vector<int> &elements);
//https://www.baeldung.com/cs/binary-tree-max-heapify
void heapify(std::vector<int> &unsorted_elements, int root_index);
void heapify_array(std::vector<int> &unsorted_elements);
//https://www.geeksforgeeks.org/building-heap-from-array/
void heapify_array_optimized(std::vector<int> &unsorted_elements);

struct MaxHeap {
    std::vector<int> elements;
    explicit MaxHeap(std::vector<int> &unsorted_elements) {
        heapify_array(unsorted_elements);
        this->elements = unsorted_elements;
    }
    ~MaxHeap() { this->elements.clear(); }
};

int find_max(MaxHeap * h);
int find_min_of_max_heap(MaxHeap * h);
int extract_max(MaxHeap * h);
void delete_max(MaxHeap * h);
void replace_max(MaxHeap * h, int value);

// melds two heaps into heap passed as first parameter
void meld(MaxHeap * h1, MaxHeap * h2);