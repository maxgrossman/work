#include <algorithm>
#include <cassert>
#include <iostream>

// keep array sorted each time a value is added
// sort my array when it is initialized
// implement the search functino which will apply the provided comparator lambda on the values to return index.


// how can I sort
/* sort(mMyClassVector.begin(), mMyClassVector.end(), */
/*     [](const MyClass & a, const MyClass & b) -> bool */
/* { */
/*     return a.mProperty > b.mProperty; */
/* }); */


int bin_search(int search_term, int *search_array, int min, int max) {
    if (max < min)
        return -1;

    int midpoint = max / 2;
    if (*(search_array + midpoint) < search_term)
        return bin_search(search_term, search_array, midpoint + 1, max);
    else if (search_term < *(search_array + midpoint))
        return bin_search(search_term, search_array, min, midpoint - 1);
    else
        return midpoint;
}
struct bin_searcher {
    int arr_to_sort_capacity = 10;
    int arr_to_sort_len = 0;
    int *arr_to_sort;
    void resize(int next_capacity) {
        arr_to_sort_capacity = next_capacity;
        int *next_arr_to_sort = new int[arr_to_sort_capacity];
        int *next_ptr = next_arr_to_sort;
        int *end = arr_to_sort + (arr_to_sort_len - 1);
        for (int *arr_to_sort_ptr = arr_to_sort; arr_to_sort_ptr < end; ++arr_to_sort_ptr) {
            *next_ptr = *arr_to_sort_ptr;
            ++next_ptr;
        }
        delete[] arr_to_sort;
        arr_to_sort = next_arr_to_sort;
    }
    void add (int next) {
        ++arr_to_sort_len;
        if (arr_to_sort_capacity / 2 == arr_to_sort_capacity) {
            resize(arr_to_sort_capacity * 2);
        }
        int *add_ptr = arr_to_sort + arr_to_sort_len - 1;
        *add_ptr = next;
        std::sort(arr_to_sort, ++add_ptr);
    };
    void print_arr() {
        std::cout << "[" << " ";
        int *end = arr_to_sort + arr_to_sort_len;
        for (int *arr_ptr = arr_to_sort; arr_ptr < end; arr_ptr++) {
            std::cout << *arr_ptr << " ";
        }
        std::cout << "]" << std::endl;
    }
    void init (int *next_arr_to_sort) {
        int next_arr_to_sort_len = sizeof(arr_to_sort)/sizeof(arr_to_sort[0]) + 1;
        // if someone isn't actually initializing, see if we ne need to resize.
        if (arr_to_sort_capacity / 2 == next_arr_to_sort_len) {
            resize(arr_to_sort_capacity * 2);
        } else if (arr_to_sort_capacity / 4 == next_arr_to_sort_len) {
            resize(arr_to_sort_capacity / 2);
        } else {
            arr_to_sort = new int[next_arr_to_sort_len];
        }
        // override the values in the current array with the new ones
        int *init_ptr = arr_to_sort;
        int *end = next_arr_to_sort + next_arr_to_sort_len;
        for (int *next_arr_to_sort_ptr = next_arr_to_sort; next_arr_to_sort_ptr < end; ++next_arr_to_sort_ptr) {
            *init_ptr = *next_arr_to_sort_ptr;
            ++init_ptr;
        }
        arr_to_sort_len = next_arr_to_sort_len;
        std::sort(arr_to_sort, arr_to_sort + arr_to_sort_len);
    }
    int search(int value) {
        return bin_search(value, arr_to_sort, 0, arr_to_sort_len);
    }
    void deconstruct() {
        delete[] arr_to_sort;
    }
};

int main() {
    int to_search[7] = {2,5,1,45,63,444,305};
    bin_searcher *b = new bin_searcher;
    b->init(to_search);
    b->print_arr();
    b->add(4);
    b->print_arr();
    assert(b->search(4) == 2);
    b->deconstruct();
    delete b;
    return 0;
}
