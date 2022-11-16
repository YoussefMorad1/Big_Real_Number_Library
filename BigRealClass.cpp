#include "BigRealHeader.h"
#include <regex>

void BigReal::setdigits(string str) {
    regex check("[+-]?([0-9]+[.]?[0-9]*|[.][0-9]+)");
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
    if(str.empty()) str = "0";
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
    s.insert(min(dotpos, (int)s.size()), 1, '.');
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
    int curPos = max(dotpos, num.dotpos);
    if (sign == 0)
        s = '-' + s;
    if (num.sign == 0)
        s1 = '-' + s1;
    BigDecimalInt Big1(s), Big2(s1);
    BigReal BR(Big1 + Big2);
    if(BR.size() > Big1.size()){
        curPos++;
    }
    BR.dotpos = curPos;
    return BR;
}


BigReal BigReal::operator- (BigReal num){
    string str1 = digits.getNumber(), str2 = num.digits.getNumber();
    string lz;
    int cnt=digits.size(), cnt1=num.digits.size();
    for (int i = 0; i < abs((cnt-dotpos)-(cnt1 - num.dotpos)); ++i) {
        lz+="0";
    }
    if(cnt > cnt1){
        str2 = str2 + lz;
    }
    else{
        str1 = str1+ lz;
    }
    lz = "";

    for(int i=0;i< abs(dotpos- num.dotpos);i++){
        lz+="0";
    }
    if(dotpos>num.dotpos){
        str2 = lz + str2;
    }
    else{
        str1 = lz + str1;
    }
    if(sign == 0){
        str1 = "-" + str1;
    }
    if(num.sign==0){
        str2 = "-" + str2;
    }
    int curpos = max(dotpos, num.dotpos);
    BigDecimalInt BDI1(str1), BDI2(str2);
    BigDecimalInt subdig(BDI1 - BDI2);
    curpos -= BDI1.size() - subdig.size();
    string s = subdig.getNumber();
    s.insert(curpos, ".");
    BigReal BR(s);
    return BR;
}

bool BigReal::operator<(BigReal antherReal) {
    string s = digits.getNumber(), s1 = antherReal.digits.getNumber();
    string comp1 = "", comp2 = "";
    int cnt1 = digits.size(), cnt2 = antherReal.digits.size();

    string str1 = s.substr(0, dotpos);

    string str2 = s1.substr(0, antherReal.dotpos);

    string frac1 = s.substr(dotpos, digits.size() - dotpos); // after dot

    string frac2 = s1.substr(dotpos, antherReal.digits.size() - antherReal.dotpos);

    int len1 = (digits.size() - dotpos), len2 = (antherReal.digits.size() - antherReal.dotpos);

    int len3 = frac1.size(), len4 = frac2.size();

    while (dotpos < antherReal.dotpos) {
        comp1 += "0";
        antherReal.dotpos--;
    }
    while (dotpos > antherReal.dotpos) {
        comp2 += "0";
        dotpos--;
    }
    str1 = comp1 + str1;
    // 11 , 05
    str2 = comp2 + str2;
    comp1 = "";
    comp2 = "";

    while ((digits.size() - dotpos) > (antherReal.digits.size() - antherReal.dotpos)) {
        comp1 += '0';
        len1--;
    }
    while ((digits.size() - dotpos) < (antherReal.digits.size() - antherReal.dotpos)) {
        comp2 += '0';
        len2--;
    }
    frac1 = frac1 + comp1;
    frac2 = frac2 + comp2;
    string BD1 = str1 + frac1, BD2 = str2 + frac2;
    BigDecimalInt ob1(BD1), ob2(BD2);

    if (sign && antherReal.sign) {
        if (ob1 < ob2) {
            return true;
        }
        else {
            return false;
        }

    } else if (!sign && !(antherReal.sign)) {
        if (ob1 < ob2) {
            return false;
        }
        else{
            return true;
        }
    } else if (!sign && antherReal.sign) {
        return true;
    } else {

        return false;
    }

}
bool BigReal::operator>(BigReal antherBigReal) {
    if(antherBigReal < *this){
        return true;
    }
    else {
        return false;
    }

}
// operator == overloading function.
bool BigReal::operator==( BigReal anotherReal) {
    if (sign == anotherReal.sign && digits.getNumber() == anotherReal.digits.getNumber()) {
        return true;

    } else {
        return false;
    }

}







// return size
    int BigReal::size() {
        return digits.getNumber().size();
    }

// function returns the sign
    int BigReal::signReal() {
        if (sign) {
            return 1;
        } else {
            return 0;
        }
    }

// operator << overloading function.
ostream &operator<<(ostream &out, BigReal num) {
    if (num.sign == 1) {
        out << num.digits;
    } else {
        if (num.digits.getNumber() == "0") {
            out << num.digits;
        } else {
            out << num.sign << num.digits;
        }
    }
    return out;
}
istream& operator >> (istream& out, BigReal num){
    if (num.sign == 1) {
        out >> num.digits;
    } else {
        if (num.digits.getNumber() == "0") {
            out >> num.digits;
        } else {
            out >> num.sign >> num.digits;
        }
    }
    return out;
}
