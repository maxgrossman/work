#include <vector>

void swap(std::vector<int> &elements);
//https://www.baeldung.com/cs/binary-tree-max-heapify
void heapify(std::vector<int> &unsorted_elements, int root_index);
void heapify_array(std::vector<int> &unsorted_elements);
//https://www.geeksforgeeks.org/building-heap-from-array/
void heapify_array_optimized(std::vector<int> &unsorted_elements);

struct Heap {
    std::vector<int> elements;
    explicit Heap(std::vector<int> &unsorted_elements) {
        heapify_array(unsorted_elements);
        this->elements = unsorted_elements;
    }
    ~Heap() { this->elements.clear(); }
};

int find_max(Heap * h);
int find_min_of_max_heap(Heap * h);
int extract_max(Heap * h);
void delete_max(Heap * h);
void replace_max(Heap * h, int value);

// melds two heaps into heap passed as first parameter
void meld(Heap * h1, Heap * h2);
