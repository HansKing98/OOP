#include <iostream>
#include "compute/compute.h"

using namespace std;

int main()
{
    int a, b;
    cout << "请输入a,b" << endl;
    cin >> a >> b;
    cout << a << " + " << b << " = " << add(a, b) << endl;
    cout << a << " - " << b << " = " << sub(a, b) << endl;
    cout << a << " * " << b << " = " << mul(a, b) << endl;
    return 0;
}