#include "BigDecimalIntClass.h"
#include "BigRealHeader.h"

int main() {
    double n1, n2;
    while (cin >> n1 >> n2) {
        BigReal x(n1), y(n2);
        BigReal z(x + y);
        z.signReal();
        z.print();
        cout << x.size() << endl;
        cout << y.size() << endl;
        cout << z.size() << endl;
        cout << endl;
    }
}
