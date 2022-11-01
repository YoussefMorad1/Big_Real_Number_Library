#include "BigDecimalIntClass.h"
#include "BigRealHeader.h"

int main() {
    double n1, n2;
    while (cin >> n1 >> n2) {
        BigReal x(n1), y(n2);
        BigReal z(x + y);
        z.print();
        cout << endl;
    }
}
