#include "../include/hashtable.h"
#include <cassert>
#include <string>
#include <iostream>
#include <exception>

int main()
{
    std::cout << "[TEST] Test starting stupid." << std::endl;
    
    // Hashtable numbers_table;
    Hashtable<std::string, int> numbers_table;
    numbers_table.put("surfing", 100);
    assert(numbers_table.get("surfing") == 100);
    std::cout << "[TEST] if I put {surfing=100} key in my table, a ::get returns 100" << std::endl;
    
    bool error_thrown = false;
    try { numbers_table.get(std::string("sixers")); } catch (char const* e) { error_thrown = true; }
    assert(error_thrown == true);
    error_thrown = false;
    std::cout << "[TEST] if I ::get(\"sixers\") from my table with out putting it in there, I throw an error." << std::endl;
    
    assert(numbers_table.exists(std::string("surfing")) == true);
    assert(numbers_table.exists(std::string("sixers")) == false);
    std::cout << "[TEST] exists returns true if key maps to Node in table, false if it does not.." << std::endl;
    
    numbers_table.remove(std::string("surfing"));
    assert(numbers_table.exists(std::string("surfing")) == false);
    
    try { numbers_table.remove(std::string("sixers")); } catch (char const* e) { error_thrown = true; }
    assert(error_thrown == true);
    error_thrown = false;
    std::cout << "[TEST] Removes entries for keys that exist in table, throws errors when keys do not." << std::endl;
    std::cout << "[TEST] Test ending stupid." << std::endl;
    return 0;
}
