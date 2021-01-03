//source -> https://www.hackerrank.com/challenges/dynamic-array/probleminclude

#include "../include/dyanmic_array.h"
#include <iostream>
#include <string>
#include <sstream>

/**
 * Yucky functions that resizes array.
 * TODO: shouldn't I just make a dyanmic array that can accept any primitive/object/class?
 */
void resize(DynamicArrayJustInt *seqList, int N, int currentSize, int nextCapacity);

/**
 * takes N and list of queries, returing a list of the operationB query results
 */
DynamicArrayJustInt dyanmicArray(int N, std::string queries);

int main() {
    // turns the input from standard in into a array of characters
    // that dynamicArray can use to execute operation1 and operation2;
    // the char array is a list of the following tokens...
    //     operator_character, x_value, xy_delimeter_comma, y_value, semicolon_delimeter
    //
    // operation_character tells me is this operation 1(a) or operation 2(b)
    // x_value and y_value are the parameters to the operations
    // xy_delimeter_comma delineates the 2 parameters
    // semicolon_delimeter delineates operations
    //
    // for example, "a2,10;b3,9;" will lead to operationA with x=2,y=10 being executed followed by operationB with x=3,b=9 being executed
    bool first = true; int N = 0, numQueries = 0; std::string queries;
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream lineStream; lineStream.str(line);
        std::string operationPart;
        int i = 0;
        if (first) {
            std::string NStr;
            std::string numQueriesStr;
            while(std::getline(lineStream, operationPart, ' ')) {
                if (i == 0) {
                    NStr += operationPart;
                } else {
                    numQueriesStr += operationPart;
                }
                ++i;
            }
            N = std::stoi(NStr);
            numQueries = std::stoi(numQueriesStr);
            first = false;
        } else {
            while(std::getline(lineStream, operationPart, ' ')){
               if (i == 0) {// the simplest way I could think to distinguish the op was to just use letters in place of 1 and 2..
                   queries += operationPart == "1" ? "a" : "b";
               } else {
                   queries += operationPart;
                   queries += i == 1 ? "," : ";";
               }
               ++i;
            }

        }
    }

    DynamicArrayJustInt operationB_results = dyanmicArray(N, queries);

    for (int i = 0; i < operationB_results.get_size(); ++i) {
        std::cout << operationB_results.get(i) << std::endl;
    }
    return 0;
}

void resize(DynamicArrayJustInt *seqList, int N, int currentSize, int nextCapacity) {
    DynamicArrayJustInt *nextSeqList = new DynamicArrayJustInt[nextCapacity];
    for (int i = 0; i < currentSize; ++i) {
        nextSeqList[i] = seqList[i];
    }
    delete[] seqList;
    seqList = nextSeqList;
}

DynamicArrayJustInt dyanmicArray(int N, std::string queries) {
    DynamicArrayJustInt operationB_results;
    int currentCapacity = N;
    int currentSize = 0;
    int lastAnswer = 0;

    DynamicArrayJustInt *seqList = new DynamicArrayJustInt[N];

    std::string x;
    std::string y;
    bool doA = false;
    bool seenComma = false;
    // loop over each character in the queries and execute the operations.
    for (std::string::iterator queriesIterator = queries.begin(); queriesIterator != queries.end(); ++queriesIterator) {
        char currentChar = *queriesIterator;
        if (currentChar == ';') { // when we've hit the semicolon_terminator, we know which operation to execute and the values of x and y
            int intX = std::stoi(x); int intY = std::stoi(y);

            int xor_index = (intX ^ lastAnswer) % N;
            if (currentCapacity < xor_index) { // for resizing, rather than guessing what the next size should be, just make it fill up to the xor_index
                currentCapacity = xor_index;
                resize(seqList, N, currentSize, currentCapacity);
                currentSize++;
            }
            if (doA) { // doA guides if we call operationA or operationB
                seqList[xor_index].pushback(intY);
            } else {
                int seqSize = seqList[xor_index].get_size();
                lastAnswer = seqList[xor_index].get(intY % seqSize);
                operationB_results.pushback(lastAnswer);
            }

            x.clear(); y.clear();
            doA = false; seenComma = false;
        } else {
            if (currentChar == 'a' || currentChar == 'b') {
                doA = currentChar == 'a';
            } else if (currentChar == ',') {
                seenComma = true;
            } else {
                if (seenComma) {
                    y += currentChar;
                } else {
                    x += currentChar;
                }
            }
        }
    }

    // cleanup
    delete[] seqList;
    return operationB_results;
}
