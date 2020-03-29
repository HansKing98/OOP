# 源码展示

![image-20200329162028849](https://image.hansking.cn/uPic/202003/77CKWV.png)

> main.cpp

```c
#include <iostream>
using namespace std;

class Student
{
public:
	Student(int num, int g);
	void display();

private:
	int number;
	float grade;
};

Student::Student(int num, int g)
{
	{
		number = num;
		grade = g;
	}
}

void Student::display()
{
	std::cout << "num:" << number << ","
			  << "grade:" << grade << std::endl;
}

int main()
{
	Student stud[5] = {
		Student(2201, 80),
		Student(2202, 85),
		Student(2203, 87),
		Student(2204, 90),
		Student(2205, 85)};
	Student *p = stud;
	p->display();
	(p += 2)->display();
	(p += 2)->display();

	return 0;
}
```
