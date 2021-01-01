#include <iostream>
#include "vector.h"

int main()
{
    try {
        std::cout << "[INFO] TESTS START" << std::endl;
        DynamicArrayJustInt d;
        std::cout << "[TEST] get_size()==" << d.get_size() << "==0" << std::endl;
        d.set(0,1);
        d.set(1,2);
        std::cout << "[TEST] get(0)==" << d.get(0) << "==1" << std::endl;
        std::cout << "[TEST] get(1)==" << d.get(1) << "==2" << std::endl;
        // since capacity starts at 2, we see that when I added
        // at point which capacity == size, push back resizes the array
        // so we have capacity for size + i, then adds
        d.pushback(18);
        std::cout << "[TEST] get(2)==" << d.get(2) << "==18" << std::endl;
        // shows that when i remove at index i, index i+ 1 ends up being i
        d.delete_at(1);
        std::cout << "[TEST] get(1)==" << d.get(1) << "==18" << std::endl;

        d.insert(0, 42);
        std::cout << "[TEST] get(0)==" << d.get(0) << "==42" << std::endl;
        // if i remove 42, then afterward the 0th will be the first i inserted.
        d.remove(42);
        std::cout << "[TEST] get(0)==" << d.get(0) << "==1" << std::endl;
        // if I pop at index 1, it will remove 1, if I then get size, it will be one less,
        // in this case 1;
        // if I then pop again I should empty the list
        std::cout << "[TEST] pop(1)==" << d.pop(1) << "==18" << std::endl;
        std::cout << "[TEST] get_size()==" << d.get_size() << "==1" << std::endl;
        std::cout << "[TEST] pop(1)==" << d.pop() << "==1" << std::endl;
        std::cout << "[TEST] get_size()==" << d.get_size() << "==0" << std::endl;
        // shows that find gets the first index, regardless of duplicates
        d.pushback(36);
        d.pushback(36);
        std::cout << "[TEST] find(36)==" << d.find(36) << "==0" << std::endl;
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
