# 源码展示

> main.cpp

```c
#include <iostream>
using namespace std;

class point
{
public:
    point(int rх, int rу)
    {
        x = rх;
        y = rу;
    }
    void show() { cout << "(" << x << "," << y << ")" << endl; }

private:
    int x;
    int y;
};

int main()
{
    point p(3, 4);
    p.show();
}
```
