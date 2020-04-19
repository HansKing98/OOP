#include <iostream>
using namespace std;

class Student; //提取引用申明
class Teacher
{
private:
    int num;
    char *name;
    char *sex;

public:
    Teacher()
    {
        num = 0;
        name = NULL;
        sex = NULL;
    }
    Teacher(int n, char *p, char *s)
    {
        num = n;
        name = p;
        sex = s;
    }
    Teacher(Student &s); //转换构造函数
    void display()
    {
        cout << "号码：" << num << endl;
        cout << "姓名：" << name << endl;
        cout << "性别：" << sex << endl;
        cout << endl;
    }
};

class Student
{
private:
    int num;
    char *name;
    char *sex;

public:
    Student(int n, char *p, char *s)
    {
        num = n;
        name = p;
        sex = s;
    }
    friend Teacher; //将Teacher声明为Student的友元类，那么Teacher就可以访问Student的私有数据
    void display()
    {
        cout << "号码：" << num << endl;
        cout << "姓名：" << name << endl;
        cout << "性别：" << sex << endl;
        cout << endl;
    }
};

Teacher::Teacher(Student &s) //转换构造函数
{
    num = s.num;
    name = s.name;
    sex = s.sex;
}

int main()
{
    Student s1(1001, "zhangsan", "female");
    cout << "Student s1为：" << endl;
    s1.display();

    Teacher t1;
    t1 = Teacher(s1);
    cout << "转换后的Teacher t1为：" << endl;
    t1.display();
    return 0;
}