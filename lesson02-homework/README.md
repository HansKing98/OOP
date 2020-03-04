# 源码展示

> main.cpp

```c
#include <iostream>
using namespace std;

class Time
{
public:
    void set_time()
    {
        cout << "设置时钟：H:M:S" << endl;
        cin >> hour;
        cin >> minute;
        cin >> sec;
    }

    void show_time()
    {
        cout << hour << ":" << minute << ":" << sec << endl;
    }

private:
    int hour;
    int minute;
    int sec;
};

int main()
{
    Time t;
    t.set_time();
    t.show_time();

    return 0;
}
```

## 运行结果

>> 输入

```bash
设置时钟：H:M:S
10
12
13
```

>> 输出

```bash
10:12:13
```
