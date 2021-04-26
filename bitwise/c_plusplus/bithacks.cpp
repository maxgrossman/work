#include <iostream>
#include <bitset>

void check_if_odd_or_even(int test) {
    std::cout << test << " is ";
    if (test & 1)
        std::cout << "odd";
    else
        std::cout << "even";

    std::cout << "!" << std::endl;
}

void check_for_matching_signs(int a, int b) {
    std::cout << a << " and " << b;
    if (a >> 31 == b >> 31)
        std::cout << " have ";
    else
        std::cout << " do not have ";

    std::cout << "matching signs." << std::endl;
}

void add_one_to_an_integer(int x) {
    std::cout << x << " + 1 = " << -~x << std::endl;
}

void swap(int x, int y) {
    std::cout << "x is " << x << ", y is " << y << std::endl;
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    std::cout << "x is " << x << ", y is " << y << std::endl;
}

void turn_off_k_bit(int number, int position) {
    int turned_off = number & ~(1 << position);
    std::cout << number << " then I turn off bit at " << position << " and it is " << turned_off << std::endl;
}

void turn_on_k_bit(int number, int position) {
    int mask = 1 << position;
    int turned_on = number | mask;
    std::cout << number << " then I turn off bit at " << position << " and it is " << turned_on << std::endl;
}

void check_if_k_bit_set(int number, int position) {
    int mask = 1 << position;
    if ((number & mask) == mask)
        std::cout << number << " has the bit at pos " << position << " set" << std::endl;
    else
        std::cout << number << " does not have the bit at pos " << position << " set" << std::endl;
}

void toggle_the_k_bit(int number, int position) {
    int mask = 1 << position;
    int toggled_on = number ^ mask;
    std::cout << "flip the bit at pos " << position << " in " << number << " and you get " << toggled_on << std::endl;
    /**
     * number = 10
     * position =2
     *
     * 1010
     * 0100^
     * 1110
     *
     */
}

/**
 * 1010
 * 1001
 * 1000
 *
 * 00101010 42
 *   101001 &
 *
 *
 *   100111
 *   100110^
 *   000001
 */

void is_positive_pow_2(int number) {
    if (number & 1)
        std::cout << number << " is not a power of two" << std::endl;
    else
        std::cout << number << " is a power of two" << std::endl;

}

int main() {

    check_if_odd_or_even(1);
    check_if_odd_or_even(2);
    check_if_odd_or_even(100);
    check_if_odd_or_even(101);

    check_for_matching_signs(10, -20);
    check_for_matching_signs(10, 20);
    check_for_matching_signs(-10, -20);

    add_one_to_an_integer(10);

    swap(10,5);

    turn_off_k_bit(10, 3);
    turn_on_k_bit(5, 3);
    turn_on_k_bit(10, 3);

    check_if_k_bit_set(5, 2);
    check_if_k_bit_set(10, 3);
    check_if_k_bit_set(10, 2);

    toggle_the_k_bit(10,2);
    toggle_the_k_bit(5,2);

    is_positive_pow_2(20);
    is_positive_pow_2(7);

    return 0;
}
