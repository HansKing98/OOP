#include<iostream>
using namespace std;
class Time
{
public:
	int h;
	int m;
	int s;
};
int main()
{
	Time t;
	t.h = 10;
	t.m = 30;
	t.s = 45;
	cout<<t.h<<":"<<t.m<<":"<<t.s<<endl;

	return 0;
}