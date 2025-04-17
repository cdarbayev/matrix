#include <iostream>
#include "matrix.h"
#include "autoptr.h"

using namespace std;

int main()
{
    AutoPtr ap1(new Matrix(1));
    {
        AutoPtr ap2 = ap1;
    }
    /*Matrix* pa = new Matrix(1);
    Matrix* pb = new Matrix(2);

    pa = pb;
    {
        Matrix* pc = pa;
    }*/
    /*Matrix m(1), n(2), res;
    res = m + n;
    cout << res << endl;
    return 0;*/
    Matrix a(1);
    Matrix b(2);
    Matrix c = a + b; 
    Matrix d = a * b; 
    Matrix e = a * 5;
    Number trace = ~a;

    cout << "Matice A\n" << a << endl;
    cout << "(A + B):\n" << c << endl;
    cout << "(A * B):\n" << d << endl;
    cout << "(5 * A):\n" << e << endl;

    if (a == b) {
        cout << "A == B" << endl;
    }
    if (a != b) {
        cout << "A != B" << endl;
    }
  
    cout << "Trace: " << trace << endl;

    return 0;
}
