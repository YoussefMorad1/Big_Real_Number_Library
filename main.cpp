#include "BigDecimalIntClass.h"
#include "BigRealHeader.h"

int main() {
    string n1, n2;
    while (cin >> n1 >> n2) {
        BigReal x(n1);
        BigReal y(n2);
        BigReal z(x - y);
        z.print();

        cout << endl;
    }
}
