【OOP】基于对象的程序设计（2）

【OOP】第九章 怎样使用类的对象

# 类的对象

## 析构函数(**destructor**)

## 实现撤销对象前的清理工作

析构函数特点(01.cpp)：

- ~类名

- 无任何返回类型，即不返回任何值

- 无参数（因此没有重载形式）

注：当对象的生命期结束时**自动执行**析构函数（若没有定义析构函数，则系统自动生成一个默认析构函数），具体来说

1. 函数内的自动局部对象在函数调用结束时

2. **static 对象（全局或局部）**或者**全局变量**仅在 main 函数结束或调用了 exit 函数时自动执行析构函数

3. 使用 new 动态创建的对象，在用 delete 释放该对象时

注：关于对象的构造函数及析构函数调用次序(01.cpp)

构造函数：全局对象的构造函数早于 main 函数被调用，然后由 main 函数调用次序决定构造函数的调用次序（多次被使用的静态对象只调用一次构造函数）

析构函数：显式 delete 的对象会调用析构函数，自动局部变量随函数调用结束而调用析构函数，静态变量，全局变量最后调用析构函数

01.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time(int hour, int minute, int second) : h(hour), m(minute), s(second)
	{
		cout << "构造函数被调用了" << h << endl; //为了区别不同对象
	}
	~Time()
	{
		cout << "析构函数被调用了" << h << endl; //为了区别不同对象
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

Time t(0, 0, 0); //全局对象

void f()
{
	Time ft1(8, 20, 0);		   //局部自动对象
	static Time ft(9, 40, 30); //静态局部对象
}
int main()
{
	f();
	f();
	Time mt1(11, 30, 45); //局部自动对象
	mt1.showTime();

	Time mt2(12, 30, 45); //局部自动对象
	mt2.showTime();

	Time *p = new Time(7, 30, 45); //new创建的局部对象
	p->showTime();
	delete p;

	return 0;
}
```

## 对象数组

- 类对象数组定义

  `类名 数组名[常数];`

- 初始化

  1. 构造函数只有一个参数时，与普通数组初始化一样（初始化值不能多于对象个数）

  ```c++
  Student stud[3]={60,70,80};
  ```

  2. 构造函数有多个参数（至多有一个非默认值）时，每个对象只接受一个参数值，否则会报错(02.cpp).因此，最好采用列表方式构造

  ```c++
  Student stud[3] = {
    Student(1001,18,60),
    Student(1002,19,70),
    Student(1003,18,80)
  };
  ```

  02.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	//至多有一个非默认参数，即多于一个非默认参数时采用普通数组形式的初始化会出错
	Time(int hour, int minute, int second = 45) : h(hour), m(minute), s(second) {}

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
	Time t[3] = {1, 2, 3, 4, 5, 6};
	t[0].showTime();
	t[1].showTime();
	t[2].showTime();

	return 0;
}
```

## 对象指针

- 指向对象的指针(参见 01.cpp)

- 指向对象成员的指针

  1. 指向对象数据成员的指针

  2. 指向对象成员函数的指针(03.cpp)

     `数据类型名(类名::*指针变量名)(参数列表);`

- this 指针——指向“本对象”的指针

  this 指针是隐式使用的

  使用方法：`this->对象成员` 或者 `(*this).对象成员`

  需要显式使用 this(04.cpp)

  03.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time(int hour, int minute, int second) : h(hour), m(minute), s(second) {}

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
	Time t(10, 30, 45);
	void (Time::*p)(); //p 是指向对象成员函数的指针
	p = &Time::showTime;
	(t.*p)(); //必须指明所属对象，否则 p 的指向未知

	return 0;
}
```

04.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	//在内部通过赋值形式实现的构造函数虽没有错误，但是无法初始化
	//Time(int h, int m, int s)
	//{
	//	h = h;
	//	m = m;
	//	s = s;
	//}

	//为了实现初始化功能，加上this
	/* Time(int h, int m, int s)
	 {
	 	this->h = h;
	 	this->m = m;
	 	this->s = s;
	 }*/

	//采用带有初始化列表的构造函数可以正常执行初始化
	Time(int h, int m, int s) : h(h), m(m), s(s){}

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
	Time t(10, 30, 45);
	t.showTime();

	return 0;
}
```

## 共用数据的保护

- 常对象(05.cpp)

  `类名 const 对象名[(实参表)]`或者`const 类名对象名[(实参表)]`

  注：

  1. 当不希望改变对象数据成员时，可以声明为常对象

  2. 定义常对象时必须同时对之初始化

  3. 常对象**只能**调用它的<u>公有</u>**常成员函数**（除了由系统自动调用的隐式构造函数和析构函数），常成员函数<u>不允许</u>修改常对象中的数据成员值

  4. 常对象的常成员函数可修改被**mutable**修饰的数据成员

- 常·对象成员

  1. 常数据成员

  注：构造函数只能通过参数初始化表对常数据成员进行初始化，任何其他函数都不能对常数据成员赋值；常对象的数据成员都是常数据成员

  2. 常成员函数（声明和定义都要加 const）

     `类型名 函数名(参数表)const`

  注：常成员函数不能修改任何数据成员的值；常对象的成员函数不必都是常成员函数；常成员函数不能调用非常成员函数

![参数初始化表](https://image.hansking.cn/uPic/202003/61wLLe.png)

- 指向对象的常指针（指向不变）

  `类名*const指针变量名`

- 指向常对象的指针（视所指对象为常对象）

  `const类名* 指针变量名`

  注**1**：指向常对象的指针可以指向常对象和非常对象，但不能改变对象成员的值；指向非常对象的指针只能指向非常对象，但能改变对象成员的值。

  注**2**：函数的形参若是指向常对象的指针，则实参可以是常对象和非常对象；函数的形参若是指向非常对象的指针，则实参只能是非常对象。

- 对象的常引用（被引用对象的值不能被改变）
  `const 类名 &引用变量名`

  05.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	//常对象的 数据成员 都是 常数据成员，构造函数只能用参数初始化表
	Time(int h, int m, int s) : h(h), m(m), s(s) {}

	//常成员函数
	void showTime() const { cout << h << ":" << m << ":" << s << endl; }

private:
	int h;
	int m;
	int s;
};

int main()
{
	//定义 常对象
	const Time t(10, 30, 45);
	//常对象 只能访问 常成员函数
	t.showTime();

	return 0;
}
```

## 对象的动态创建和释放(01.cpp)

- 对象的动态创建

  `Time *pt= new Time(10,30,45);`

- 对象的释放

  `delete pt;`

## 对象的赋值和复制（参见 06.cpp）

- 对象的赋值（对于已存在对象的数据成员的赋值）

  `对象名1 = 对象名2;`

  注：“=“的重载

- 对象的复制（对于待建立对象的数据成员的赋值）

  `类名 对象2(对象1);` 或者`类名 对象2(对象1);`

注：“=“的重载。如果未提供拷贝构造函数，则系统会自动提供一个默认拷贝构造函数（也只是完成数据成员的赋值，但不应包括动态数据成员）。调用拷贝构造函数情形：① 以一个对象为模板创建一个新对象；② 函数参数为类对象；③ 函数的返回值是类对象

06.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	//构造函数不能用 参数初始化表 初始化 静态数据成员
	//Time(int hour, int minute, int second) : h(hour), m(minute), s(second) {}

	//静态数据成员 不能在 构造函数内部初始化
	//Time(int hour, int minute, int second) : m(minute), s(second) { h = hour; }

	Time(int minute, int second) : m(minute), s(second) {}

	void showTime() { cout << h << ":" << m << ":" << s << endl; }
	static int h;

private:
	int m;
	int s;
};

//静态数据成员只能在类体外执行初始化
int Time::h = 10;

int main()
{
	Time t(30, 45);
	cout << "sizeof(t) = " << sizeof(t) << endl;
	//公有静态数据成员可以使用对象来引用
	cout << "小时:" << t.h << endl;
	//公有静态数据成员也可以使用类名来引用
	cout << "小时:" << Time::h << endl;

	return 0;
}
```

## 静态成员

### static 可以实现同类多个对象之间的**数据共享**

- 静态数据成员(06.cpp)

  注：

  1. 静态数据成员不占用对象空间，或者说静态数据成员独立于对象而存在，为所有对象所共享

  2. 静态数据成员是在程序开始运行分配空间，直到结束释放

  3. 静态数据成员只能在类体外初始化（声明时加 static，初始化时无需加 static），且不能用参数初始化表（无论是类体内还是类体外）对静态成员变量进行初始化

  4. 公有静态数据成员既可以使用对象名引用，也可以使用类名引用

  5. 静态数据成员的使用要注意其作用域（只在其作用域内可见）

### static 修饰的成员函数（即静态成员函数）处理静态数据成员

- 静态成员函数(07.cpp)

  注：

  1. 静态成员函数是类的一部分而不是对象的一部分

  2. 静态成员函数没有 this 指针，因此无法对一个对象内部的非静态成员进行默认访问（即不加所属对象）

  3. 公有静态成员函数使用类名引用，也可以使用对象名引用

  07.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time(int minute, int second) : m(minute), s(second) {}

	// 此处的后两个参数没有意义，只是为了演示非静态变量不能在静态函数内赋值
	static void setTime(int hour, int minute = 0, int second = 0)
	{
		h = hour;
		// m = minute;
		// s = second;
	}
	void showTime() { cout << h << ":" << m << ":" << s << endl; }

private:
	static int h;
	int m;
	int s;
};

int Time::h = 10;

int main()
{
	Time t(30, 45);
	t.showTime();
	t.setTime(11);
	t.showTime();
	Time::setTime(12);
	t.showTime();

	return 0;
}
```

## 友元

friend 修饰的**函数**或**类**可以访问当前类中的私有成员

- 友元函数

  1. 将**普通函数**声明为友元函数(08.cpp)

  2. 友元**成员函数**(09.cpp)

  注：一个函数（普通函数或类成员函数）可以被**多个类**声明为友元

- 友元类

  `friend 类名;`

  注：

  1. 友元关系是单向的（不具备对称性）

  2. 友元关系不具有传递性

  3. 除非确有必要，一般不将整个类声明为友元类；友元事实上破坏了类的封装性，但是有助于数据共享，提高了程序的效率

     08.cpp

```c++
#include <iostream>
using namespace std;

class Time
{
public:
	Time(int hour, int minute, int second) : h(hour), m(minute), s(second) {}
	friend void showTime(Time &); //友元函数

private:
	int h;
	int m;
	int s;
};
void showTime(Time &t)
{
	//引用Time类的私有成员时必须要加上对象，因为该函数没有this指针
	cout << t.h << ":" << t.m << ":" << t.s << endl;
}

int main()
{
	Time t(10, 30, 45);
	showTime(t);

	return 0;
}
```

09.cpp

```c++
#include <iostream>
using namespace std;

class Date; //提前引用声明
class Time
{
public:
	Time(int hour, int minute, int second) : h(hour), m(minute), s(second) {}
	void showTime(Date &);

private:
	int h;
	int m;
	int s;
};

class Date
{
public:
	Date(int year, int month, int day) : y(year), m(month), d(day) {}
	friend void Time::showTime(Date &);

private:
	int y;
	int m;
	int d;
};

// 只有在正式声明Date类之后才可以实例化，因此该函数不能放到Date类声明之前定义
void Time::showTime(Date &d)
{
	//引用Date类的私有成员时必须要加上对象，因为该函数的this指针指向Time对象
	cout << d.y << "/" << d.m << "/" << d.d << endl;
	cout << h << ":" << m << ":" << s << endl;
}

int main()
{
	Date d(2020, 3, 24);
	Time t(10, 30, 45);
	t.showTime(d);

	return 0;
}
```

## 类模板(10.cpp)

**功能相同**但**数据类型不同**的类，可以采用类模板（参数化的类）

- 定义形式

  `template<class 类型参数名> class 类名{ … };`

- 使用方法

  `类模板名<实际类型名>对象名(参数表);`

  注：

  1. 类模板的类型参数可以有一个或多个，每个类型前都必须加 class,如

     `template<class T1,class T2>class 类名{…};`

  2. 类模板的声明和定义必须放在同一个文件内（不能做到声明与定义的分离）

  3. 模板可以有层次，基类模板可以派生出派生类模板

```c++
#include <iostream>
using namespace std;

template <class T>
class Compare
{
public:
	Compare(T a, T b) : x(a), y(b) {}
	T max() { return x > y ? x : y; }
	T min() { return x < y ? x : y; }

private:
	T x;
	T y;
};

int main()
{
	Compare<int> c1(10, 20);
	cout << "max = " << c1.max() << endl;
	cout << "min = " << c1.min() << endl;

	Compare<double> c2(12.5, 23.6);
	cout << "max = " << c2.max() << endl;
	cout << "min = " << c2.min() << endl;

	Compare<char> c3('A', 'a');
	cout << "max = " << c3.max() << endl;
	cout << "min = " << c3.min() << endl;

	return 0;
}
```
