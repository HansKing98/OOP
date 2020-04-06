#include <iostream>
using namespace std;

class Time
{
public:
	//常对象的 数据成员 都是 常数据成员
	//当数据成员是实际的常成员时（即有 const 修饰），构造函数只能用参数初始化表
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