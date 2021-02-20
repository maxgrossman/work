#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
#include <cassert>

int getRandomPrime(int string_size)
{
    bool isPrime = false;
    int i = 0;
    int rand_num = 0;
    while (isPrime == false)
    {
        rand_num = rand() % string_size + (string_size * 2);
        for (i = 2; i <= string_size / 2; ++i)
        {
            if (string_size % i == 0)
            {
                isPrime = false;
                i = 2;
                break;
            }
            i++;
        }
        isPrime = true;
    }
    return rand_num;
}

/**
 * DESC: Returns index where pattern starts matching string_in_question using rabin-karp rolling hash algorithm.
 * TIME: O(N) in best case, O(XN+M) in worst case where N is length of pattern and M is index where two strings start matching, and X is number of matching hashes.
 */
int rabin_karp(std::string pattern, std::string string_in_question) {
    int pattern_size = pattern.size();
    int prime_number = getRandomPrime(pattern_size);

    int pattern_hash = 0;
    int pattern_last_char_value = 0;

    int siq_substr_hash = 0;
    int siq_last_char_value = 0;
    int to_the_pow_prime_mulitple = 0;
    int matching = 0;

    // build up the hashes of the pattern chars and 0...pattern_size chars.
    // also, check that we have matches for each iteration so we can just check
    // on the last loop to see if we have a match. makes the best case O(N)
    for (int i = 0; i < pattern_size; i++) {
        if (pattern[i] == string_in_question[i])
            ++matching;

        int pattern_value = int(pattern[i]);
        int siq_value = int(string_in_question[i]);

        if (i == 0) {
            pattern_hash += pattern_value;
            siq_substr_hash += siq_value;
            siq_last_char_value = siq_value;
        } else {
            int to_the_pow_prime = int(pow(prime_number, i));
            if (i == pattern_size - 1) {
                to_the_pow_prime_mulitple = to_the_pow_prime;
            
                if (siq_substr_hash == pattern_hash && matching == pattern_size)
                    return 0;
            }

            pattern_hash += pattern_value * to_the_pow_prime;
            siq_substr_hash += siq_value * to_the_pow_prime;
        }
    }

    int siq_size = string_in_question.size();
    int starting_index = 1;
    int matching_index = -1;
    
    // CALCULATE HASH
    // 1) hash = old hash - val_at_old_char
    // 2) hash = hash/prime_number
    // 3) hash = hash + next_char_val x prime_number^(size_of_string-1)
    for (int i = pattern_size; i < siq_size; ++i) {

        siq_substr_hash -= siq_last_char_value;
        siq_substr_hash /= prime_number;
        siq_substr_hash += int(string_in_question[i]) * to_the_pow_prime_mulitple;
        siq_last_char_value = int(string_in_question[starting_index]);

        if (siq_substr_hash == pattern_hash) {
            int siq_j = starting_index;
            matching_index = siq_j;
            for (int j = 0; j < pattern_size; j++) {
                if (pattern[j] != string_in_question[siq_j]) {
                    matching_index = -1;
                    break;
                }
                ++siq_j;
            }

            if (matching_index != -1)
                return matching_index;
        }

        starting_index++;
    }

    return -1;
};

int main()
{
    assert(rabin_karp("surf", "surfing") == 0);
    std::cout << "surf is at the 0th index of surfing" << std::endl;
    assert(rabin_karp("urf", "surfing") == 1);
    std::cout << "urf is at the 1st index of surfing" << std::endl;
    assert(rabin_karp("ing", "surfing") == 4);
    std::cout << "ing is at the 4th index of surfing" << std::endl;
    assert(rabin_karp("fli", "surfing") == -1);
    std::cout << "fli is not in surfing, so we return a -1" << std::endl;
    return 0;
}
