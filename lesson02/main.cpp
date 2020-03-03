#include <iostream>
#include "Time/Time.h"
using namespace std;

int main()
{
	Time t;
	t.setTime(10, 30, 45);
	t.display();

	return 0;
}