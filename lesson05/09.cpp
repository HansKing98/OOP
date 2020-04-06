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