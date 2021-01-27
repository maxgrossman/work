#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>

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

int starts_with(std::string pattern, std::string string_in_question)
{
    int pattern_size = pattern.size();
    int prime_number = getRandomPrime(pattern_size);

    int pattern_hash = 0;
    int pattern_last_char_value = 0;

    int string_in_question_substr_hash = 0;
    int string_in_question_last_char_value = 0;
    int to_the_pow_prime_mulitple = 0;
    for (int pattern_i = 0; pattern_i < pattern_size; pattern_i++)
    {
        int pattern_char_at_pattern_i_value = int(pattern[pattern_i]);
        int string_in_question_char_at_pattern_i_value = int(string_in_question[pattern_i]);
        if (pattern_i == 0)
        {
            pattern_hash += pattern_char_at_pattern_i_value;
            string_in_question_substr_hash += string_in_question_char_at_pattern_i_value;
            string_in_question_last_char_value = string_in_question_char_at_pattern_i_value;
        }
        else
        {
            int to_the_pow_prime = int(pow(prime_number, pattern_i));
            if (pattern_i == pattern_size - 1)
                to_the_pow_prime_mulitple = to_the_pow_prime;

            pattern_hash += pattern_char_at_pattern_i_value * to_the_pow_prime;
            string_in_question_substr_hash += string_in_question_char_at_pattern_i_value * to_the_pow_prime;
        }
    }
    int string_in_question_size = string_in_question.size();
    int starting_index = 1;
    int matching_index = -1;
    // CALCULATE HASH
    // 1) hash = old hash - val_at_old_char
    // 2) hash = hash/prime_number
    // 3) hash = hash + next_char_val x prime_number^(size_of_string-1)
    for (int string_in_question_i = pattern_size; string_in_question_i < string_in_question_size; string_in_question_i++)
    {
        if (string_in_question_substr_hash == pattern_hash)
        {
            int string_in_question_j = string_in_question_i;
            for (int pattern_i = 0; pattern_i < pattern_size; pattern_i++)
            {
                if (pattern[pattern_i] != string_in_question[string_in_question_j])
                {
                    matching_index = -1;
                    break;
                }
                ++string_in_question_j;
            }
            matching_index = string_in_question_i - pattern_size;
            return matching_index;
        }

        string_in_question_substr_hash -= string_in_question_last_char_value;
        string_in_question_substr_hash /= prime_number;
        string_in_question_substr_hash += int(string_in_question[string_in_question_i]) * to_the_pow_prime_mulitple;
        string_in_question_last_char_value = int(string_in_question[starting_index]);
        ++starting_index;

    }

    return -1;
};

int main()
{
    std::cout << starts_with(std::string("surf"), std::string("surfing")) << std::endl;
    std::cout << starts_with(std::string("urf"), std::string("surfing")) << std::endl;
    std::cout << starts_with(std::string(""), std::string("surfing")) << std::endl;
    return 0;
}
