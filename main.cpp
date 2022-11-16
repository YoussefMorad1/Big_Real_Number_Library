#include "BigDecimalIntClass.h"
#include "BigRealHeader.h"

int main() {
    string n1, n2;
    while (cin >> n1 >> n2) {
        BigReal x(n1);
        BigReal y(n2);
        if (x.operator<(y)) {
            cout << "first is smaller\n";
        } else {
            cout << "second is smaller\n";
        }
        if (x.operator>(y)) {
            cout << "first is bigger\n";
        } else {
            cout << "second is bigger\n";
        }
        cout << endl;
        cout << "subtract: " << x - y << endl;
        cout << "addition: " << x + y << endl;
    }
}
