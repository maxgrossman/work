#include <iostream>
#include <cassert>
#include "../include/fixed_size_array_queue.h"
int main()
{
    std::cout << "[TEST] START TESTS STUPID." << std::endl;
    FixedSizeArrayQueue f(3);
    std::cout << "[TEST] I enqueue 2 and when I dequeue 2 I get 1st in then 2nd in." << std::endl;
    f.enqueue(1); f.enqueue(2);
    assert(f.dequeue() == 1);
    assert(f.dequeue() == 2);
    std::cout << "[TEST] After this my list is empty, and so trying to dequeue throws an error" << std::endl;
    assert(f.empty() == true);
    bool error_thrown = false;
    try { f.dequeue(); } catch (DequeueException &e) { error_thrown = true; }
    assert(error_thrown == true);
    error_thrown = false;
    std::cout << "[TEST] With an empty list I can just add 2 items, no problem" << std::endl;
    f.enqueue(10); f.enqueue(11);
    std::cout << "[TEST] But I cannot add a 3rd since you can only enqueue size - 1 items" << std::endl;
    try { f.enqueue(14); } catch (EnqueueException &e) { error_thrown = true; }
    assert(error_thrown == true);
    std::cout << "[TEST] TESTS PASS STUPID." << std::endl;
}
