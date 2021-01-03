#include <iostream>
#include <cassert>
#include "../include/dyanmic_array.h"


int main()
{
    std::cout << "[TEST] TESTS START" << std::endl;
    DynamicArrayJustInt d;

    assert(d.get_size() == 0);
    std::cout << "[TEST] get_size() is 0 when initialized" << std::endl;

    d.set(0,1); d.set(1,2);
    assert(d.get(0) == 1); assert(d.get(1) == 2);
    std::cout << "[TEST] set() method sets value ant index" << std::endl;

    d.pushback(18);
    assert(d.get(2) == 18);
    std::cout << "[TEST] pushback(value) puts value at end of list" << std::endl;

    d.delete_at(1);
    assert(d.get(1) == 18);
    std::cout << "[TEST] delete_at(i) deletes element at i and moves right of left 1" << std::endl;

    d.insert(0, 42);
    assert(d.get(0) == 42); assert(d.get(1) == 1);
    std::cout << "[TEST] insert(i, value) puts value at i and moves right of right 1" << std::endl;

    d.remove(42);
    assert(d.get(0) == 1);
    std::cout << "[TEST] remove(value) deletes first instance of value and move right of left 1" << std::endl;

    assert(d.pop(1) == 18); assert(d.get_size() == 1);
    assert(d.pop() == 1); assert(d.get_size() == 0);
    std::cout << "[TEST] pop(i) removes element at index, moves right of left 1, and returns element" << std::endl;

    d.pushback(36);
    d.pushback(36);
    assert(d.find(36) == 0); assert(d.find(200) == -1);
    std::cout << "[TEST] find(value) returns index of first match with value or -1 if none found" << std::endl;

    std::cout << "[TEST] TESTS PASS, NICE!!" << std::endl;
    return 0;
}
