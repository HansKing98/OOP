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