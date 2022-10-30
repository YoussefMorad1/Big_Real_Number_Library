#include "BigRealHeader.h"
#include <regex>

void BigReal::setdigits(string str) {
    regex check("[+-]?([0-9]+[.]?[0-9]*|.[0-9]+)");
    if (!regex_match(str, check)) {
        cout << "\nInvalid input to BigRealClass!\n";
        exit(1);
    }

    int pos = str.find('.');
    if(pos != -1)
        str.erase(pos, 1);

    dotpos = pos == -1 ? (int) str.size() : pos;
    if(str[0] == '+' || str[0] == '-')
        dotpos--;

    BigDecimalInt tmp(str);
    digits = tmp;
    sign = digits.sign();
}

BigReal::BigReal(string str) {
    setdigits(str);
}

BigReal::BigReal(double num) {
    setdigits(to_string(num));
}

BigReal::BigReal(BigDecimalInt bignum) {
    setdigits(bignum.getNumber());
}

BigReal &BigReal::operator=(const BigReal &rhs) {
    digits = rhs.digits;
    sign = rhs.sign;
    dotpos = rhs.dotpos;
    return (*this);
}

BigReal &BigReal::operator=(BigReal &&rhs) {
    digits = rhs.digits;
    sign = rhs.sign;
    dotpos = rhs.dotpos;
    return (*this);
}

BigReal::BigReal(const BigReal &rhs) {
    operator=(rhs);
}

BigReal::BigReal(BigReal &&rhs) {
    operator=(rhs);
}
