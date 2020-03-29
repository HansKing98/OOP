【OOP】基于对象的程序设计（1）

【OOP】第九章 怎样使用类的对象

# 类的对象

## 在声明类的同时对数据成员初始化

```c++
#include<iostream>
using namespace std;

class Time
{
	int h = 0;
	int m = 0;
	int s = 0;
};

int main()
{
	Time t;

	return 0;
}
```

## 数据成员均为公用，则可以在定义对象时对数据成员初始化

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	int h;
	int m;

private:
	int s;
};

int main()
{
	Time t = {10, 30};
  // 注：若数据成员不全为 public 则编译时会出错！
  // error: could not convert ‘{10, 30}’ from <brace-enclosed initializer list>’ to ‘Time’
	cout<<t.h<<":"<<t.m<<":"<<t.s<<endl;

	return 0;
}
```

# 构造函数(**constructor**)

实现数据成员初始化

构造函数特点：

- 与类同名

- 无任何返回类型，即不返回任何值

- 注：

  1. 建立对象时**自动调用**构造函数，无需也不能自主调用

  2. 一般声明为 public

  3. 无返回值

  4. 可用一个类对象**初始化**另一个该类对象（其实是使用了类的**默认拷贝构造函数**）

## 数据成员均为公用，则可以在定义对象时对数据成员初始化

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time()
	{
		h = 11;
		m = 31;
		s = 46;
	}
	void setTime(int hour, int minute, int second)
	{
		h = hour;
		m = minute;
		s = second;
	}
	void showTime() { cout << h << ":" << m << ":" << s << endl; }

private:
	int h;
	int m;
	int s;
};

int main()
{
	Time t1;
	t1.setTime(10, 30, 45);
	t1.showTime();

	Time t2;
	t2.showTime();

	return 0;
}
```

## 用一个类对象初始化另一个该类对象

```c++
int main()
{
	Time t1;
	t1.setTime(10, 30, 45);
	Time t2 = t1;  //也可以采用这种方式 Time t2(t1);
	t2.showTime();

	return 0;
}
```

## 构造函数的种类

- 默认构造函数（系统在用户**未定义**构造函数时自动生成，**无参无操作**）

- 无参构造函数

  **注**：用户自定义的，此时系统就不会生成默认构造函数了

- 含参构造函数（包括重载形式，即构造函数可以不止一个）

  **注**：一个类可以**没有**无参构造函数而只含有含参构造函数；同时，一个类**只要有**构造函数，系统就不会生成默认构造函数了(05.cpp). 因此，以防意外，**最好提供无参构造函数**

- 拷贝构造函数（也分**默认拷贝构造函数**和用户**自定义拷贝构造函数**）(06.cpp)

## 数据成员均为公用，则可以在定义对象时对数据成员初始化

05.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time() { h = 0; m = 0; s = 0; }
	Time(int hour, int minute, int second)
	{
		h = hour;
		m = minute;
		s = second;
	}
	void setTime(int hour, int minute, int second)
	{
		h = hour;
		m = minute;
		s = second;
	}
	void showTime() { cout << h << ":" << m << ":" << s << endl; }

private:
	int h;
	int m;
	int s;
};

int main()
{
	Time t1; // //此处定义方式就会出错，因为没有默认构造函数了 无参 => 0:0:0
	// t1.setTime(10, 30, 45); =>10:30:45
	t1.showTime();

	return 0;
}
```

06.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time(int hour, int minute, int second)
	{
		h = hour;
		m = minute;
		s = second;
	}
	void setTime(int hour, int minute, int second)
	{
		h = hour;
		m = minute;
		s = second;
	}
	void showTime() { cout << h << ":" << m << ":" << s << endl; }

private:
	int h;
	int m;
	int s;
};

int main()
{
	Time t1(10, 30, 45);
	Time t2 = t1;
	// Time t2(t1);
	t2.showTime();

	return 0;
}
```

## 构造函数中使用参数化列表初始化数据成员

- 带有**参数初始化表**的构造函数的一般形式：

  **类名::构造函数名([参数表])[:成员初始化表]**

  {

  ​ [构造函数体]

  }

- 使用初始化列表的情况（简单了解）：

  1. const 成员或者引用类型的成员

  2. 需要初始化的数据成员是对象的情况，并且这个对象只有含参数的构造函数，没有无参数的构造函数

  3. 派生类初始化基类的私有成员

- 使用初始化 列表会快一些的 原因（ 简单了解 1. 对 内置类型成员变量 （包括指针，引用 ），两者性能差别不大 2. 对非内置类型成员变量（类类型），构造函数体内 进行赋值操作会 使用两次构造函数，而成员初始化列表则只需要一次 (07.cpp,08.cpp)

**注**：默认情况 下，一个类可以通过默认类型转换构建一个对象，而不是直接调用该构造函数。若避免此种情形，需要 explicit 关键字(09..cpp)

07.cpp

```c++
#include <iostream>
using namespace std;
class A
{
public:
    A()
    {
        value = 0;
        cout << "A()" << endl;
    }
    A(int n)
    {
        value = n;
        cout << "A(int " << value << ")" << endl;
    }

    A(const A &a)
    {
        value = a.value;
        cout << "A(const A& a):  " << value << endl;
    }
    A &operator=(const A &a)
    {
        cout << "assignment for a" << endl;
        value = a.value;
        return *this;
    }

private:
    int value;
};

class B
{
public:
    B(const A &a)
    {
        b = a; //b 会自动调用A的默认构造函数，若A没有默认构造函数则出错
               //若没有对 = 进行重载，则调用默认拷贝构造函数进行赋值
    }

private:
    A b;
};

int main()
{
    A a(1);
    B b(a);
    return 0;
}
```

08.cpp

```c++
class B
{
public:
    B(const A &a) : b(a) {} //初始化列表，少调用一次默认构造函数

private:
    A b;
};

int main()
{
    A a(1);
    B b(a);
    return 0;
}
```

09.cpp

```c++
#include <iostream>
using namespace std;
class A
{
public:
    A()
    {
        value = 0;
        cout << "A()" << endl;
    }
    A(int n) //支持通过一个整数赋值构造A对象。加上explicit关键字将限制该种创建对象方式
    {
        value = n;
        cout << "A(int " << value << ")" << endl;
    }

private:
    int value;
};

class B
{
public:
    B(const A &a) //支持通过一个A对象赋值构造B对象。加上explicit关键字将限制该种创建对象方式
    {
        b = a;
    }

private:
    A b;
};

int main()
{
    A a = 1;
    B b = a;
    return 0;
}
```

## 使用默认参数的构造函数

- 使用默认参数的构造函数的好处

  **方便有效，提供了建立对象时的多种选择；即使未提供实参，构建对象时也不会出错**

- 使用默认参数的构造函数注意事项

1. 应在声明构造函数时指定默认值且形参名可以省略，若声明和定义均指定默认值，则以声明时参数为准（事实上，两者不一致时会报错）(10.cpp)

   error:default argument given for parameter 1 of 'Time:Time(int, int, int)'

2. 全部参数都指定了默认值的构造函数也属于默认构造函数

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time(int = 0, int = 0, int = 0);
	void setTime(int hour, int minute, int second)
	{
		h = hour;
		m = minute;
		s = second;
	}
	void showTime() { cout << h << ":" << m << ":" << s << endl; }

private:
	int h;
	int m;
	int s;
};
Time::Time(int hour, int minute, int second) : h(hour), m(minute), s(second) {}

int main()
{
	Time t1;
	t1.showTime();

	return 0;
}
```
