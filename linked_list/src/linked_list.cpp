#include "../include/linked_list.h"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void LinkedList::addafter(struct Node** head, struct Node** tail, struct Node** beforeNode, int value) {
    if (*head == nullptr)
        throw "cannot insert in empty list";

    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = (*beforeNode)->next;

    (*beforeNode)->next = newNode;

    if (*beforeNode == *tail)
        *tail = newNode;

    ++size;
}

/**
 * DESC: Adds a new node after provided node pointer
 * TIME: Always O(1)
 */
void LinkedList::addafter(Node* beforeNode, int value) {
    addafter(&head, &tail, &beforeNode, value);
}


void LinkedList::addbefore(struct Node** head, struct Node** tail, struct Node** afterNode, int value) {
    if (*head == nullptr)
        throw "caonnot insert in empty list";

    Node* newNode = new Node;
    newNode->value = value;

    Node* walkNode = *head;
    Node* previous = nullptr;

    while (walkNode != nullptr) {
        if (*afterNode == walkNode) {
            newNode->next = *afterNode;

            if (previous != nullptr)
                previous->next = newNode;
            else
                *head = newNode;

            ++size;
            break;
        }

        previous = walkNode;
        walkNode = walkNode->next;
    }
}

/**
 * DESC: adds new node before provided node
 * TIME: O(N) in worst case, O(1) in best case
 */
void LinkedList::addbefore(Node* afterNode, int value) {
    addbefore(&head, &tail, &afterNode, value);
}

/**
 * DESC: returns value at index
 * TIME: O(N-1) in worst case, O(1) in best case.
 */
int LinkedList::valueAt(int index) {
    return getNodeAt(index)->value;
}
/**
 * DESC: returns true if the list is empty
 * TIME: O(1)
 */
bool LinkedList::empty() {
    return size == 0;
}

void LinkedList::insert(struct Node** head, struct Node** tail, int index, int value) {
    if (index >= size || index < 0)
        throw "Cannot insert a node outside the list bounds";

    Node* insertNode = new Node;
    insertNode->value = value;

    if (index == 0) { // same logic as popfront.
        insertNode->next = *head;
        *head = insertNode;
    } else { // links before node to insert then insert to nodeBefore's next
        Node* nodeBefore = getNodeAt(index - 1);
        insertNode->next = nodeBefore->next;
        nodeBefore->next = insertNode;
    }

    if (size == 0)
        *tail = insertNode;

    ++size;
}
/**
 * DESC: inserts a new node at provided index, and shifts what was at that index and all .
 * TIME: O(N-1) in worst case, O(1) in best case
 */
void LinkedList::insert(int index, int value) {
    insert(&head, &tail, index, value);
}

void LinkedList::erase(struct Node** head, struct Node** tail, int value) {
    if (*head == nullptr)
        throw "this list is empty!";

    Node* walkNode = *head;
    Node* previous = nullptr;

    while (walkNode != nullptr) {
        if (walkNode->value == value) {
            // if we are not erasing the head node, then link previous to next
            // in that case too, if n is the current tail, set the tail to the previous node
            // if we are erasing the head node, then set head to n->next
            if (previous != nullptr) {
                previous->next = walkNode->next;
                if (walkNode == *tail)
                    *tail = previous;
            } else {
                *head = walkNode->next;
            }

            delete walkNode;
            --size;
            break;
        }
        previous = walkNode;
        walkNode = walkNode->next;
    }
}

/**
 * DESC: removes first node with matching value.
 * TIME: O(N) in worst case, O(1) in best case.
 */
void LinkedList::erase(int value) {
    erase(&head, &tail, value);
}

/**
 * DESC: returns true if a node's value equals value in args
 * TIME: O(N) in worst case, O(1) in the best case.
 */
bool LinkedList::find(int value) {
    if (head == nullptr)
        throw "This list is empty";

    Node* n = head;
    while (n != nullptr) {
        if (n->value == value)
            return true;
        n = n->next;
    }
    return false;
}
/**
 * DESC: returns node at provided index
 * TIME: O(N-1) in best acse, O(1) in best case
 */
Node* LinkedList::getNodeAt(int index) {
    // do not allow index outside of list bounds.
    if (index >= size || index < 0)
        throw "Provided index outside of list bounds";

    if (index == 0)
        return head;
    else if (index == (size - 1))
        return tail;

    Node* n = head; int counter = 0;
    while (n != nullptr) {
        if (index == counter)
            break;
        n = n->next;
        counter++;
    }

    if (n == nullptr)
        throw "Corrupted List. Reached non-tail node with next pointer equal nullptr";

    return n;
}

/**
 * DESC: returns the current size of the list
 * TIME: O(1)
 */
int LinkedList::getsize() {
    return size;
}
/**
 * DESC: returns node at provided index.
 * TIME: O(N-1) in worst case, O(1) in best.
 */
Node* LinkedList::nodeAt(int index) {
    return getNodeAt(index);
}

/**
 * DESC: returns node n nodes away from tail (moving right->left)
 * TIME: O(N-1) in worst case, O(1) in best case
 */
Node* LinkedList::nthNodeFromEnd(int n) {
    if (head == nullptr)
        throw "cannot get value in an empty list";
    else if (n > size)
        throw "n is greater than the lenght of the list";

    // when n is the distance from the tail node, and that is zero, then it is the tail node.
    if (n == 0)
        return tail;

    // if n is the farthest node from the tail within the list bounds, then it is the head.
    int numNodes = size - 1;
    if (n == numNodes)
        return head;

    // if neither of these, find the node that has a distance away from the tail == n;
    // since we already have figured out it is not the head node, we can start looking
    // 1 node away from the head such that counter is 1.
    int counter = 1;
    Node* walkNode = head;
    while (walkNode != nullptr) {
        if ((numNodes - counter) == n)
            break;
        ++counter;
        walkNode = walkNode->next;
    }
    return walkNode;
}
/**
 * DESC: gets the value at node n from last (moving right->left)
 * TIME: O(N-1) in worst case, O(1) in best case
 */
int LinkedList::nthValueFromEnd(int n) {
    return nthNodeFromEnd(n)->value;
}

void LinkedList::pushback(struct Node** head, struct Node** tail, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (*head == nullptr)
        *head = newNode;
    else
        (*tail)->next = newNode;

    *tail = newNode;
    ++size;
}
/**
 * DESC: Adds a node to the end of the list
 * TIME: O(1)
 */
void LinkedList::pushback(int value) {
    pushback(&head, &tail, value);
}

void LinkedList::pushfront(struct Node** head, struct Node** tail, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (*head == nullptr)
        *tail = newNode;
    else
        newNode->next = *head;

    *head = newNode;
    ++size;
}
/**
 * DESC: creates a node at the beginning of the list
 * TIME: O(1)
 */
void LinkedList::pushfront(int value) {
    pushfront(&head, &tail, value);
};

/**
 * DESC: reverses order of the list such tail becomes head and head becomes tail and nodes are linked in reverse order
 * TIME: O(N)
 */
void LinkedList::reverse() {
    Node* current = head;
    Node* previous = nullptr;
    Node* next = nullptr;
    int step = 0;
    // walk the list, flippint the ->next pointers to the previous nodes.
    // when we are at our first walk, where current is the new head,
    // flip the is_tail boolean to indicate as much, and then after we've
    // pointed its next to NULL, set the tail equal to it.
    while (current != nullptr) {
        next = current->next;
        current->next = previous;
        if (step == 0)
            tail = current;
        previous = current;
        current = next;
        ++step;
    }
    head = previous;
}
/**
 * DESC: Returns the first (the head) node in the list
 * TIME: O(1)
 */
int LinkedList::topfront() {
    return head->value;
}
/**
 * DESC: returns the tail node's value
 * TIME: O(1)
 */
int LinkedList::topback() {
    return tail->value;
}

int LinkedList::popback(struct Node** head, struct Node** tail) {
    if (*head == nullptr)
        throw "Nothing to remove, this list is currently empty";

    int pop_value = (*tail)->value;

    // if i only have 1 in my list tail needs to end up being null.
    // so it needs to be a nullptr and when i delete the old tail
    // i think it will remove what ever was there right?
    Node* nextTail = size == 1 ? nullptr : getNodeAt(size - 2);
    Node* prevTail = *tail;

    delete prevTail;
    *tail = nextTail;

    if (size == 1)
        *head = *tail;

    --size;
    return pop_value;
}
/**
 * DESC: returns the value at the end of the list
 * TIME: O(N-1) in worst case O(1) in best
 */
int LinkedList::popback() {
    return popback(&head, &tail);
}

int LinkedList::popfront(struct Node** head, struct Node** tail) {
    if (*head == nullptr)
        throw "Nothing to remove, this list is currently empty";

    int pop_value = (*head)->value;

    Node* prevHead = *head;
    *head = size == 1 ? nullptr : (*head)->next;

    if (size <= 2)
        *tail = *head;

    delete prevHead;
    --size;


    return pop_value;
}

/**
 * DESC: removes the current head.
 * TIME: O(1)
 */
int LinkedList::popfront() {
    return popfront(&head, &tail);
}
