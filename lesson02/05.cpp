#include<iostream>
using namespace std;
class Time
{
public:
	void setTime(int hours,int mins,int secs){ h = hours; m = mins; s = secs; }
	void display(){ cout<<h<<":"<<m<<":"<<s<<endl; }
private:
	int h;
	int m;
	int s;
};
int main()
{
	Time t; 
	t.setTime(10,30,45);
	t.display();

	return 0;
}