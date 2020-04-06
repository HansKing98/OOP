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