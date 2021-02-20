#include <string>
#include <exception>
#include <type_traits>


template<typename keyType, typename valueType>
struct Node {
    Node<keyType, valueType>* next;
    keyType key;
    valueType value;
};

template<typename keyType, typename valueType>
class LinkedList {
    private:
        int size;
        struct Node<keyType, valueType>* head;
        struct Node<keyType, valueType>* tail;
    public:
        LinkedList() {
            size = 0;
            head = nullptr;
            tail = nullptr;
        };
        ~LinkedList() {
            while (size > 0) { // delete all of the nodes.
                Node<keyType, valueType>* temp = head->next;
                delete head;
                head = temp;
                --size;
            }
        }
        Node<keyType, valueType>* getHead() { return head; }
        void pushfront(keyType key, valueType value) {
            Node<keyType, valueType>* nextHead = new Node<keyType, valueType>;
            nextHead->value = value;
            nextHead->key = key;
            nextHead->next = head;

            if (head == nullptr)
                tail = nextHead;

            head = nextHead;
            size++;
        };
        Node<keyType, valueType>* search_return(keyType key) {
            Node<keyType, valueType>* walkNode = head;
            while (walkNode != nullptr) {
                if (walkNode->key == key)
                    break;
                walkNode = walkNode->next;
            }

            return walkNode;
        };
        bool search_remove(keyType key) {
            Node<keyType, valueType>* walkNode = head;
            Node<keyType, valueType>* previous = nullptr;
            while (walkNode != nullptr) {
                if (walkNode->key == key) {
                    if (previous != nullptr)
                        previous->next = walkNode->next;
                    else
                        head = walkNode->next;

                    delete walkNode;
                    --size;
                    return true;
                }
                previous = walkNode;
                walkNode = walkNode->next;
            }

            return false;
        };
        int getSize() { return size; }
};

template<typename keyType, typename valueType>
class Hashtable {
    private:
        int table_size;
        int num_linked_lists;
        LinkedList<keyType, valueType> **table;
        /**
         * DESC: simple, sad, niave, modulo hashing function that returns keyIndex for string
         * TIME: O(N) where N is length of key
         */
        int keyHash(keyType key) {
            int keyAsciiValue = 0;

            if (std::is_same<keyType, std::string>::value) {
                for (char& keyChar: key) {
                        keyAsciiValue += (int)keyChar;
                }
            }

            return keyAsciiValue % table_size;
        }

        /**
         * DESC: Rehashes/inserts each entry in the old table into the new one, deleting old table's lists, and then it, while doing so
         * TIME: Best is O(N), when we have empty all empty linked lists. Worst is O(N+M) where M is number of entries across linked lists.
         */
        void buildNextTable(int old_table_size) {
            LinkedList<keyType, valueType>* nextTable[table_size];

            for (int i = 0; i < old_table_size; ++i) {
                LinkedList<keyType, valueType>* tableList = table[i];

                if (tableList == nullptr)
                    continue;

                Node<keyType, valueType>* tableHead = tableList->getHead();
                while (tableHead != nullptr) {
                    int nextEntryIndex = keyHash(tableHead->key);
                    if (nextTable[nextEntryIndex] == nullptr)
                        nextTable[nextEntryIndex] = new LinkedList<keyType, valueType>;
                    
                    nextTable[nextEntryIndex]->pushfront(tableHead->key, tableHead->value);
                    tableHead = tableHead->next;
                }

                delete tableList;
            }

            delete[] table;
            table = nextTable;
        }

        /**
         * DESC: Doubles the size of our table. Done when number of linked lists we have is 1/2 table size.
         * TIME: Best is O(N), when we have empty all empty linked lists. Worst is O(N+M) where M is number of entries across linked lists.
         */
        void doubleTable() {
            int old_table_size = table_size;
            table_size *= 2;
            // for each node in our linked lists, rehash the keys and put them in our new list.
            buildNextTable(old_table_size);
        }
        /**
         * DESC: Halves the size of our table. We call this when the number of linked lists is 1/4th table size.
         * TIME: Best is O(N), when we have empty all empty linked lists. Worst is O(N+M) where M is number of entries across linked lists.
         */
        void halfTable() {
            int old_table_size = table_size;
            table_size /= 2;
            buildNextTable(old_table_size);
        };

        int randPrime(int min) {    
            bool isPrime = false; int i = 0; int rand_num = 0; int max = min * 2;
            while (isPrime == false) {
                rand_num = rand() % min + max;
                for (i = 2; i <= rand_num / 2; ++i) {
                    if (rand_num % i == 0) 
                        isPrime = false; i = 2; break;
                    i++;
                }
                isPrime = true;
            }
            return rand_num;
}

    public:
        Hashtable() {
            table_size = randPrime(30);
            table = new LinkedList<keyType, valueType>*[table_size];
            for (int i = 0; i < table_size; i++) table[i] = nullptr;
            num_linked_lists = 0;
        };
        ~Hashtable() {
            // delete each LinkedList
            for (int i = 0; i < table_size; ++i) {
                if (table[i] != nullptr)
                    delete table[i];
            }
            // delete table, array of pointers.
            delete[] table;
        }
        /**
         * DESC: adds Node to LinkedList at entryIndex containing provided key and value.
         * TIME: O(N) where n is length of key.
         */
        void put(keyType key, valueType value) {
            int entryIndex = keyHash(key);
            if (table[entryIndex] == nullptr) {
                // if number of keys gets to 1/2 size of our table, then we double our table size.
                if (num_linked_lists + 1 == (table_size / 2)) {
                    doubleTable();
                    entryIndex = keyHash(key);
                }

                table[entryIndex] = new LinkedList<keyType, valueType>;
                ++num_linked_lists;
            }

            (*table[entryIndex]).pushfront(key, value);
        }
        /**
         * DESC: replies Node.value for node in table[entryIndex]'s LinkedList
         * TIME: O(N) is best, O(N+M) in worst. Nis the length of the key and M is Node's index in the linked list.
         */
        int get(keyType key) {
            int entryIndex = keyHash(key);
            if (table[entryIndex] == nullptr)
                throw "key not in hashtable.";
            
            return (*table[entryIndex]).search_return(key)->value;
        };
        /**
         * DESC: Replies true if key maps to a Node in one of the table's LinkedLists, false if it does not.
         * TIME: O(N) is best, O(N+M) in worst. Nis the length of the key and M is Node's index in the linked list.
         */
        bool exists(keyType key) {
            int entryIndex = keyHash(key);

            // hashed key does not map to index in table or it does,
            // but the linked list at that index does not have a Node for the key.
            if (table[entryIndex] == nullptr || (*table[entryIndex]).search_return(key) == nullptr)
                return false;

            return true;
        };
        /**
         * DESC: Tries to remove Node in table's linked list for provided key, throwing errors if linked list with hashed key
         *       does not exist, or it does but the list's remove functino fails to find/delete node for key.
         * TIME: O(N) is best, O(N+M) in worst. Nis the length of the key and M is Node's index in the linked list.
         */
        void remove(keyType key) {
            int entryIndex = keyHash(key);
        
            if (table[entryIndex] == nullptr)
                throw "Key does not exist in this hashtable";

            if (table[entryIndex]->search_remove(key) == false)
                throw "Key does not exist in this hashtable";

            if (table[entryIndex]->getSize() == 0) {
                LinkedList<keyType, valueType>* listToDelete = table[entryIndex];
                table[entryIndex] = nullptr;
                delete listToDelete;
                --num_linked_lists;

                if (num_linked_lists == table_size / 4)
                    halfTable();
            };
        }
};
