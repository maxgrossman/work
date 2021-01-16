#include "../include/linked_list.h"
#include <iostream>

LinkedList::LinkedList() {
    head = NULL;
    size = 0;
}
/**
 * add new node after provided node pointer
 */
void LinkedList::addafter(Node* beforeNode, int value) {
    if (head != NULL) {
        // create a new node, set the beforeNode's next to the new node then make beforeNode's next = newNode
        Node* newNode = new Node; newNode->value = value;
        newNode->next = beforeNode->next;
        beforeNode->next = newNode;
    } else {
        throw "cannot insert in empty list";
    }
}
/**
 * adds new node before provided node
 */
void LinkedList::addbefore(Node* afterNode, int value) {
    if (head != NULL) {
        Node* newNode = new Node; newNode->value = value;
        Node* n = head; Node* previous = NULL;
        while (n != NULL) {
            if (afterNode == n) {
                if (previous != NULL) previous->next = newNode;
                newNode->next = n;
                ++size;
                break;
            }
            previous = n; n = n->next;
        }
    } else {
        throw "cannot insert in empty list";
    }
}

/**
 * returns value at index
 * @param {int} index
 * @return {int} the value at index
 */
int LinkedList::valueAt(int index) {
    return getNodeAt(index)->value;
}
/**
 * returns true if the list is empty
 */
bool LinkedList::empty() {
    return size == 0;
}
/**
 * inserts a new node at provided index.
 */
void LinkedList::insert(int index, int value) {
    // because we need to keep the link to the nodes previous,
    // get the node before the current index, set our insertNode's next to the nodeBefore's
    // then set nodeBefore's to the insertBefore
    Node* nodeBefore = getNodeAt(index - 1);
    Node* insertNode = new Node; insertNode->value = value;
    insertNode->next = nodeBefore->next;
    nodeBefore->next = insertNode;
}
/**
 * removes first node with matching value.
 */
void LinkedList::erase(int value) {
    if (head != NULL) {
        Node* n = head; Node* previous = NULL;
        while (n != NULL) {
            if (n->value == value) {            // erase when the input value matches
                if (previous != NULL) {           // if we are not erasing the head node, then linke previous to next
                    previous->next = n->next;
                }
                delete n;
                --size;
                break;
            }
            previous = n; n = n->next;
        }
    } else {
        throw "this list is empty!";
    }
}

/**
 * returns true if a node's value equals value in args
 */
bool LinkedList::find(int value) {
    if (head != NULL) {
        Node* n = head;
        while (n != NULL) {
            if (n->value == value) return true;
            n = n->next;
        }
        return false;
    } else {
        throw "This list is empty";
    }
}
/**
 * returns node at provided index
 * @param {int} index
 * @return {Node} node at index
 */
Node* LinkedList::getNodeAt(int index) {
    // do not allow index outside of list bounds.
    if (index > (size - 1) || index < 0) {
        throw "Provided index outside of list bounds";
    }
    Node* n = head; int counter = 0;
    while (n != NULL) {
        if (index == counter) break; // break index==counter means we walked to node at index matching index.
        n = n->next;               // otherwise we keep walking the list and incrementing until we find the match
        counter++;
    }

    if (n == NULL) {
        throw "Corrupted List. Reached non-tail node with next pointer equal to NULL";
    }

    return n;
}

/**
 * returns the current size of the list
 */
int LinkedList::getsize() {
    return size;
}
/**
 * get node at
 */
Node* LinkedList::nodeAt(int index) {
    return getNodeAt(index);
}

Node* LinkedList::nthNodeFromEnd(int n) {
    if (n > size) {
        throw "n is greater than the lenght of the list";
    } else if (head != NULL) {
        if (n == size) {
            return head;
        }
        int counter = 0;
        Node* walkNode = head;
        while (walkNode != NULL) {
            if ((size - counter) == n) {
                return walkNode;
            }
            ++counter;
            walkNode = walkNode->next;
        }
    } else {
        throw "cannot get value in an empty list";
    }
}
/**
 * gets node n from last
 */
int LinkedList::nthValueFromEnd(int n) {
    return nthNodeFromEnd(n)->value;
}
/**
 * Adds an element to the end of the list
 */
void LinkedList::pushback(int value) {
    Node* newNode = new Node; newNode->value = value;
    if (head != NULL) {
        Node* lastNode = getNodeAt(size - 1);
        lastNode->next = newNode;
    } else {
        head = newNode;
    }
    ++size;
}
/**
 * creates a node with new int value and places it at the front of the list
 * @param {int} value used in the new node placed at the front of the list.
 */
void LinkedList::pushfront(int value) {
    Node* newNode = new Node; newNode->value = value;
    if (head != NULL) {
        newNode->next = head;
    }
    head = newNode;
    ++size;
};
/**
 * reverses order of the list
 */
void LinkedList::reverse() {
    Node* current = head;
    Node* previous = NULL;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}
/**
 * returns the first (the head) element in the list
 */
int LinkedList::topfront() {
    return head->value;
}
/**
 * returns the tail element in the list
 * @returns {int} tail node's value
 */
int LinkedList::topback() {
    return size == 0 ? head->value : getNodeAt(size - 1)->value;
}

/**
 * returns the value at the end of the list
 */
void LinkedList::popback() {
    if (head != NULL) {
        delete getNodeAt(size - 1);
        size--;
    } else {
        throw "Nothing to remove, this list is currently empty";
    }
}
/**
 * removes the current head.
 */
void LinkedList::popfront() {
    if (head != NULL) {
        Node* nextHead = head->next;
        delete head;
        head = nextHead;
        --size;
    } else {
        throw "Nothing to remove, this list is currently empty";
    }
}
