#include "../include/linked_list.h"
#include <iostream>
#include <cassert>


int main()
{
    std::cout << "[TEST] START TESTS STUPID." << std::endl;
    LinkedList l;
    l.pushfront(1);
    l.pushback(10);
    // showing that no matter how you look, what's in the front is 1, at the back is 10
    assert(l.valueAt(0) == 1);
    assert(l.valueAt(1) == 10);
    assert(l.topfront() == l.valueAt(0));
    assert(l.topback() == l.valueAt(1));
    assert(l.nthValueFromEnd(0) == 10);
    assert(l.nthValueFromEnd(1) == 1);
    assert(l.getsize() == 2);
    std::cout << "[TEST] we can push stuff to the front and back of the list with .pushfront and .pushback" << std::endl;
    l.popfront();
    assert(l.topfront() == l.topback());
    assert(l.getsize() == 1);
    l.popback();
    // AT THIS POINT WE HAVE AN EMPTY LINKED LIST.
    assert(l.getsize() == 0);
    std::cout << "[TEST] we can remove stuff at the front and back of the list with .topfront and .topback" << std::endl;
    l.pushfront(3);
    l.pushback(18);
    l.pushfront(4);
    assert(l.find(3) == true);
    assert(l.find(18) == true);
    assert(l.find(4) == true);
    assert(l.find(36) == false);
    std::cout << "[TEST] we can prove that stuff we add to the list is in the list with .find" << std::endl;
    l.erase(18);
    assert(l.find(18) == false);
    l.erase(4);
    assert(l.find(4) == false);
    std::cout << "[TEST] we can remove first-found nodes based on values with .erase" << std::endl;
    assert(l.valueAt(0) == 3);
    l.addafter(l.nodeAt(0), 30);
    assert(l.valueAt(1) == 30);
    l.addbefore(l.nodeAt(1), 25);
    assert(l.valueAt(1) == 25);
    std::cout << "[TEST] we can add a node before a node using .before (and get pointers to nodes / node values with .nodeAt / .valueAt)" << std::endl;
    l.insert(1, 11);
    assert(l.valueAt(1) == 11);
    l.insert(0,15); // show that when we insert at head index it replaces the head);
    assert(l.popfront() == 15);
    // clean up whatever is left
    while (l.getsize() > 0)
        l.popfront();
    std::cout << "[TEST] we can insert at any index in the list with .insert" << std::endl;

    LinkedList l2;
    l2.pushback(3); l2.pushback(2); l2.pushback(1);
    l2.reverse();
    assert(l2.valueAt(0) == 1);

    // clean up
    while (l2.getsize() > 0)
        l2.popfront();

    std::cout << "[TEST] we can reverse a list by calling .reverse" << std::endl;
    std::cout << "[TEST] THEY PASS STUPID." << std::endl;
    return 0;
}
