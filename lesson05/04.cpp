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
	Time(int h, int m, int s) : h(h), m(m), s(s) {}

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