/**
 * Sidney  Raabe
 * Bigint
 * CS-23001
 */

#ifndef BIGINT_HPP
#define BIGINT_HPP

const int CAPACITY = 300;

#include <ostream>

class bigint {
public:
    const char* getIntChars() const { return intChars; }
    bigint();
    bigint(const int);
    bigint(const char[]);
    bool operator==(const bigint&) const;
    void debugPrint(std::ostream&) const;
private:
    char intChars[CAPACITY];
};

std::ostream& operator<<(std::ostream&, const bigint&);

#endif
