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