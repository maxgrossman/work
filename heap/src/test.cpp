#include "../include/heap.h"
#include <cassert>

int main() {
    std::vector<int> unsorted_elements = {19,100,17,36,3,4,7,2,25};
    MaxHeap * h = new MaxHeap(unsorted_elements);
    assert(max_find_max(h) == 100);
    max_delete_max(h);
    assert(max_find_max(h) == 36);
    max_replace_max(h, 50);
    assert(max_find_max(h) == 50);

    std::vector<int> unsorted_elements_two = {39,8,15,11,1,23,55,200};
    MaxHeap * h0 = new MaxHeap(unsorted_elements_two);

    max_meld(h, h0);
    assert(max_find_max(h) == 200);
    assert(max_find_min(h) == 1);

    delete h;
    delete h0;
    unsorted_elements.clear();
    unsorted_elements_two.clear();
    return 0;
}
