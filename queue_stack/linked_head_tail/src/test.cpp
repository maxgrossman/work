#include "../include/linked_list_queue.h"
#include <iostream>
#include <cassert>

int main()
{
    std::cout << "[TEST] START TESTS STUPID." << std::endl;
    LinkedListQueue lQ;
    lQ.enqueue(20);
    lQ.enqueue(21);
    assert(lQ.empty() == false);
    assert(lQ.dequeue() == 20);
    assert(lQ.dequeue() == 21);
    assert(lQ.empty() == true);
    std::cout << "[TEST] When we enqueue then dequeue, dequeue-ing follows FIFO." << std::endl;
    std::cout << "[TEST] TESTS PASS STUPID." << std::endl;
    return 0;
}
