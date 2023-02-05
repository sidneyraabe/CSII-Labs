/**
 * Sidney  Raabe
 * Bigint
 * CS-23001
 */

#include "bigint.hpp"
#include <iostream>


const int LINE_LENGTH_LIMIT = 80;

bigint::bigint() {
    // insert one zero character
    intChars[0] = 0 + '0';

    // fill rest of array with null terminators
    for (int i = 1; i < CAPACITY; ++i) {
        intChars[i] = 0;
    }
}

bigint::bigint(const int input) {
    int modifiedInput = input;
    int iterator = 0;

    // case 0 handler
    if (input == 0) {
        // Insert one zero character
        intChars[0] = 0 + '0';
        // prevents 0 from being overwritten with null terminator, later
        iterator = 1;
    }

    // Insert provided int right-to-left to bigint char array
    while (modifiedInput > 0) { 
        // set char array current index to rightmost value
        intChars[iterator] = (modifiedInput % 10) + '0';
        // pop rightmost value
        modifiedInput /= 10;
        // set next bigint char array index location
        ++iterator;
    }

    // Fill remaining indices with trailing null terminators
    for (int i = iterator; i < CAPACITY; ++i){
        intChars[i] = 0;
    }
}

bigint::bigint(const char input[]) {
    
    int inputLength = 0;
    // determine length of input array
    // valid numbers must be >=0 and <=9, and if all are, end loop at max index
    while(input[inputLength] >= 0 + '0' && input[inputLength] <= 9 + '0' && inputLength < CAPACITY) {
        ++inputLength;
    }

    // determine index at which significant digits begin = trailingZeros
    int trailingZeros = 0;
    while (input[trailingZeros] == '0') {
        ++trailingZeros;
    }

    // keep track of index between bigint construction loops
    int currentIndex = 0;
    // assign numbers in reverse order, up to but not including trailing zeros
    while (currentIndex < inputLength - trailingZeros) {
        intChars[currentIndex] = input[inputLength - 1 - currentIndex];
        ++currentIndex;
    }

    // fill remaining indexes with null terminators
    while (currentIndex < CAPACITY) {
        intChars[currentIndex++] = 0;
    }

    // handle all 0 input
    if (intChars[0] == 0)
        intChars[0] = 0 + '0';
}

bool bigint::operator==(const bigint& rhs) const {
    for (int i = 0; i < CAPACITY; ++i) {
        // return false at first descrepancy found. if one is found, they must be unequal
        if (rhs.intChars[i] != this->intChars[i]) {
            return false;
        }
    }
    return true;
}

void bigint::debugPrint(std::ostream& stream) const {
    // iterate backwards through right to left array to print left to right
    for (int i = CAPACITY - 1; i >= 0; --i) {
        // only print non null terminators
        if (int(this->intChars[i] != 0)) {
            // print number then pipe ex:  3|
            stream << this->intChars[i] << '|';
            continue;
        }
    }

    // separate from next output
    stream << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const bigint& object) {
    const char* intChars = object.getIntChars();    
    
    int currentLineLength = 0;
    // iterate backwards through right to left array to print left to right
    for (int i = CAPACITY - 1; i >= 0; --i) {
        // only print not null terminators
        if (int(intChars[i] != 0)) {
            stream << intChars[i];
            ++currentLineLength;
        }
        // linebreak if hit max_columns
        if (currentLineLength == LINE_LENGTH_LIMIT) {
            stream << std::endl;
            currentLineLength = 0;
        }
    }

    // ensure endl at end, but prevent double endl if one was just made
    if (currentLineLength != 0)
        stream << std::endl;

    return stream;
}