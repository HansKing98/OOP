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