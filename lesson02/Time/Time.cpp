#include<iostream>
#include"Time.h"

using namespace std;

void Time::setTime(int hours,int mins,int secs)
{
	h = hours;
	m = mins;
	s = secs;
}
void Time::display()
{
	cout<<h<<":"<<m<<":"<<s<<endl;
}
