#include <vector>

void swap(std::vector<int> &elements);
//https://www.baeldung.com/cs/binary-tree-max-heapify
void max_heapify(std::vector<int> &unsorted_elements, int root_index);
void max_heapify_array(std::vector<int> &unsorted_elements);

struct MaxHeap {
    std::vector<int> elements;
    explicit MaxHeap(std::vector<int> &unsorted_elements) {
        max_heapify_array(unsorted_elements);
        this->elements = unsorted_elements;
    }
    ~MaxHeap() { this->elements.clear(); }
};

int max_find_max(MaxHeap * h);
int max_find_min(MaxHeap * h);
int max_extract_max(MaxHeap * h);
void max_delete_max(MaxHeap * h);
void max_replace_max(MaxHeap * h, int value);

// melds two heaps into heap passed as first parameter
void max_meld(MaxHeap * h1, MaxHeap * h2);
