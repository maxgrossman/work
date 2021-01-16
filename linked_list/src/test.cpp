#include "../include/linked_list.h"
#include <iostream>
#include <cassert>


int main()
{
    std::cout << "[TEST] START TESTS STUPID." << std::endl;
    LinkedList l;
    // we can push stuff to the front and back of the list wiht .pushfront and .pushback
    l.pushfront(1);
    l.pushback(10);
    assert(l.topfront() == l.valueAt(0));
    assert(l.topback() == l.valueAt(1));
    assert(l.getsize() == 2);
    // we can remove stuff at the front and back of the list with .topfront and .topback
    l.popfront();
    assert(l.topfront() == l.topback());
    assert(l.getsize() == 1);
    l.popback();
    assert(l.getsize() == 0);
    // we can prove that stuff we add to the list is in the list with .find
    l.pushfront(3);l.pushback(18);l.pushfront(4);
    assert(l.find(3) == true);
    assert(l.find(18) == true);
    assert(l.find(4) == true);
    assert(l.find(36) == false);
    // we can remove first-found nodes based on values with .erase
    l.erase(18);
    assert(l.find(18) == false);
    l.pushfront(6);
    l.erase(4);
    assert(l.find(4) == false);
    // we can add a node before a node using .addbefore (and get pointers to nodes / node values with .nodeAt / .valueAt)
    l.addbefore(l.nodeAt(1), 34);
    assert(l.valueAt(1) == 34);
    l.addafter(l.nodeAt(1), 30);
    assert(l.valueAt(2) == 30);
    // we can insert at any index in the list with .insert
    l.insert(2, 11);
    assert(l.valueAt(2) == 11);
    // we can revers a list by doing .reverse
    LinkedList l2;
    l2.pushback(3); l2.pushback(2); l2.pushback(1);
    l2.reverse();
    assert(l2.valueAt(0) == 1);
    std::cout << "[TEST] THEY PASS STUPID." << std::endl;
    return 0;
}
