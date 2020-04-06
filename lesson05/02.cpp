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