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
    
    int size();
   
    int signReal():
    
    void print();
};

#endif //BIG_REAL_BIGREALHEADER_H
