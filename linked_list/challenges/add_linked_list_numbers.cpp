#include "../include/linked_list.h"
#include <iostream>
#include <cassert>

/** SOLUTION FOR THIS LEETCODE https://leetcode.com/problems/add-two-numbers/ **/

void printAnswer(Node* printNode);
LinkedList addLinkedListNumbers(LinkedList numbers1, LinkedList numbers2);
int addLinkedListNumbersMain();

int addLinkedListNumbersMain() {
    std::cout << "ADD LINKED LIST NUMBERS STARTS, STUPID." << std::endl;
    LinkedList a; a.pushfront(1); LinkedList b; b.pushfront(1);
    printAnswer(addLinkedListNumbers(a,b).nodeAt(0));
    a.pushfront(3);
    printAnswer(addLinkedListNumbers(a,b).nodeAt(0));
    a.pushback(4);
    printAnswer(addLinkedListNumbers(a,b).nodeAt(0));
    std::cout << "ADD LINKED LIST NUMBERS ENDS, STUPID.\n" << std::endl;
    return 0;
}

void printAnswer(Node* printNode) {
    std::cout << "[";
    while (printNode != NULL) {
        std::cout << printNode->value;
        if (printNode->next != NULL) std::cout << ",";
        printNode = printNode->next;
    }
    std::cout << "]" << std::endl;
}
LinkedList addLinkedListNumbers(LinkedList numbers1, LinkedList numbers2) {
    // 1. figure out which is the larger of the lists;
    Node* loopNode; Node* otherNode; LinkedList sumList;
    if (numbers1.getsize() > numbers2.getsize()) {
        loopNode = numbers1.nodeAt(0); otherNode = numbers2.nodeAt(0);
    } else {
        loopNode = numbers2.nodeAt(0); otherNode = numbers1.nodeAt(0);
    }
    // 2. loop until end of loopNode's list, adding otherNode's value where otherNode exists
    while (loopNode != NULL) {
        if (otherNode != NULL) {
            sumList.pushfront(loopNode->value + otherNode->value);
            otherNode = otherNode->next;
        } else {
            sumList.pushfront(loopNode->value);
        }
        loopNode = loopNode->next;
    }
    return sumList;
}

/** SOLUTION FOR THIS LEETCODE https://leetcode.com/problems/rotate-list/ **/

Node* rotateRight(Node* listHead, int k);
int rotateListMain();

Node* rotateRight(Node* listHead, int k) {
    // get the tail of the list via walking to the end.
    Node* tailNode = NULL; Node* walkNode = listHead;
    while (walkNode != NULL) {
        tailNode = walkNode;
        walkNode = walkNode->next;
    }
    // rotate the list once until we reach k.
    for (int i = 0; i < k; ++i) {
        Node* nextTailNode = listHead; // walk the list again and set the nextTailNode to the one before tailNode
        while (nextTailNode->next != tailNode) {
            nextTailNode = nextTailNode->next;
        }

        tailNode->next = listHead; // link the tailNode to the head
        listHead = tailNode; // make the new head, which is linked to old head b/c of last step
        tailNode = nextTailNode; // move the tail back one (via nextTailNode) and repeat the above steps.
    }
    // delink the new tailNode to what at this point is the head node.
    tailNode->next = NULL;
    // return the listHead after we've done the above processing
    return listHead;
}
int rotateListMain() {
    std::cout << "ROTATE LINKED LIST NUMBERS STARTS, STUPID." << std::endl;
    LinkedList listToRotate;
    listToRotate.pushfront(5);
    listToRotate.pushfront(4);
    listToRotate.pushfront(3);
    listToRotate.pushfront(2);
    listToRotate.pushfront(1);
    Node* listHead = listToRotate.nodeAt(0);
    assert(listHead->value == 1);

    Node* printNode = listHead;
    std::cout << "INITIAL LIST ";
    printAnswer(printNode);

    listHead = rotateRight(listHead, 1);
    assert(listHead->value == 5);

    printNode = listHead;
    std::cout << "ROTATE LIST 1 ";
    printAnswer(printNode);

    listHead = rotateRight(listHead, 3);
    assert(listHead->value == 2);

    printNode = listHead;
    std::cout << "ROTATE LIST 3 ";
    printAnswer(printNode);

    std::cout << "ROTATE LINKED LIST NUMBERS ENDS, STUPID." << std::endl;
    return 0;
}
int main() {
    assert(addLinkedListNumbersMain() == 0);
    assert(rotateListMain() == 0);
    return 0;
}
