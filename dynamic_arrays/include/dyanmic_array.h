#ifndef DynamicArrayJustInt_H
#define DynamicArrayJustInt_H

//    25 methods
//    26 - Get(i) -> return element at location i*; theta(1);
//    27 - Set(i, val) -> sets element i to val*; theta(1);
//    28 - PushBack(val) -> Adds val to the end of the array; omega(1); O(n)
//    29 - Remove(i) -> removes element at location i; O(n)
//    30 - Size() -> tells how many elements are in the array
//    31 properties
//    32 - capacity -- how large it can be
//    33 - size -- how much of that capacity we are using now
//    34
class DynamicArrayJustInt {
    private:
        int capacity;
        int size;
        int *mutable_array;
        void resize();
    public:
        DynamicArrayJustInt();
        void delete_at(int i);
        int find(int i);
        int get(int i);
        int get_size();
        void insert(int i, int value);
        int pop(int i = -1);
        void pushback(int value);
        void remove(int value);
        void set(int i, int value);
};

#endif
