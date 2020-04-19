# 转换构造函数

转换构造函数可以将一种类的对象程序转换为另一种类的对象。在以下程序中有转换构造函数 Teacher::Teacher(Student & stud);

作用就是将Student类的对象转换为Teacher类的对象。

 

## Description
定义一个Teacher(教师)类（教师号，姓名，性别，薪金）和一个Student(学生)类（学号，姓名，性别，成绩），二者有一部分数据成员是相同的，num(号码)，name(姓名),sex(性别)。编写程序，将一个Student对象(学生)转换为Teacher(教师)类，只将以上3个相同的数据成员移植过去。可以设想为： 一位学生大学毕业了，留校担任教师，他原有的部分数据对现在的教师身份来说仍然是有用的，应当保留并成为其教师数据的一部分。
## Input
一个教师的信息和一个学生的信息
## Output
学生的信息和学生转换为教师后的信息
Student s1为：
号码：1001
姓名：zhangsan
性别：female

转换后的Teacher t1为：
号码：1001
姓名：zhangsan
性别：female 
```c++
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
```