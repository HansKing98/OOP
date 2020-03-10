#include <iostream>
using namespace std;

class Cuboid
{
public:
    void set_value();
    int Valume();

private:
    int length;
    int width;
    int height;
};

Cuboid a, b, c;

int main()
{
    a.set_value();
    b.set_value();
    c.set_value();

    cout << "体积分别为：" << endl
         << a.Valume() << endl
         << b.Valume() << endl
         << c.Valume() << endl;

    return 0;
}

void Cuboid::set_value()
{
    cout << "设置长宽高" << endl;
    cin >> length;
    cin >> width;
    cin >> height;
}

int Cuboid::Valume()
{
    return length * width * height;
}