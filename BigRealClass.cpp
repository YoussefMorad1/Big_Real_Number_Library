#include "BigRealHeader.h"
#include <regex>

void BigReal::setdigits(string str) {
    regex check("[+-]?([0-9]+[.]?[0-9]*|.[0-9]+)");
    if (!regex_match(str, check)) {
        cout << "\nInvalid input to BigRealClass!\n";
        exit(1);
    }

    // deleting leading zeros
    int idx = -1;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '0') {
            idx = i;
        } else {
            break;
        }
    }
    str = str.substr(idx + 1, str.size() - idx);

    int pos = str.find('.');
    if (pos != -1) {
        // deleting tailing zeros in fraction
        idx = str.size();
        for (int i = str.size() - 1; i >= pos + 1; --i) {
            if (str[i] == '0')
                idx = i;
            else
                break;
        }
        str = str.substr(0, idx);

        // erasing the '.'
        str.erase(pos, 1);
    }
    dotpos = pos == -1 ? (int) str.size() : pos;
    if (str[0] == '+' || str[0] == '-')
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
    sign = bignum.sign();
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

void BigReal::print() {
    string s = digits.getNumber();
    s.insert(dotpos, 1, '.');
    if (s[0] == '.')
        s = '0' + s;
    if (s[s.size() - 1] == '.')
        s += '0';
    if (!sign)
        cout << '-';
    cout << s;
}

BigReal BigReal::operator+(BigReal num) {
    string s = digits.getNumber(), s1 = num.digits.getNumber();
    string lz;

    int cnt1 = digits.size(), cnt2 = num.digits.size();

    for (int i = 0; i < abs((cnt1 - dotpos) - (cnt2 - num.dotpos)); i++) {
        lz += "0";
    }
    if (cnt1 - dotpos > cnt2 - num.dotpos) {
        s1 = s1 + lz;
    } else {
        s = s + lz;
    }
    lz = "";
    for (int i = 0; i < abs(dotpos - num.dotpos); i++) {
        lz += "0";
    }
    if (dotpos > num.dotpos) {
        s1 = lz + s1;
    } else {
        s = lz + s;
    }
    if (sign == 0)
        s = '-' + s;
    if (num.sign == 0)
        s1 = '-' + s1;
    BigDecimalInt Big1(s), Big2(s1);
    BigReal BR(Big1 + Big2);
    BR.dotpos = max(dotpos, num.dotpos);
    return BR;
}
// return size.
int BigReal ::size() {
        return digits.getNumber().size();
    }



// function returns the sign
int BigReal::signReal() {
    if (sign == '+') {
        return 1;
    } else {
        return 0;
    }
}
