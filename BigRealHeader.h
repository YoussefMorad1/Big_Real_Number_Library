#ifndef BIG_REAL_BIGREALHEADER_H
#define BIG_REAL_BIGREALHEADER_H

#include "BigDecimalIntClass.h"

class BigReal {
private:
    BigDecimalInt digits;
    int dotpos;
    int sign;
public:
    void setdigits(string str);

    BigReal(string str);

    BigReal(double num);

    BigReal(BigDecimalInt bignum);

    BigReal &operator=(const BigReal &rhs);

    BigReal &operator=(BigReal &&rhs);

    BigReal(const BigReal &rhs);

    BigReal(BigReal &&rhs);

    BigReal operator+(BigReal num);

    BigReal operator-(BigReal num);

    bool operator< (BigReal antherBigReal);

    bool operator> (BigReal antherBigReal);

    int size();

    int signReal();

    friend ostream& operator << (ostream& out, BigReal num);

    friend istream& operator >> (istream& out, BigReal num);

    bool operator== (BigReal anotherReal);

    void print();
};

#endif //BIG_REAL_BIGREALHEADER_H
