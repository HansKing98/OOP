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