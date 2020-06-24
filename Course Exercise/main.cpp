/*
 * @Description: 学生成绩管理系统
 * @Author: hans
 * @Date: 2020-06-01 10:56:47
 * @LastEditTime: 2020-06-15 15:19:27
 * @LastEditors: hans
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>  // fin fout
#include <iomanip>  // setw()
using namespace std;

#define IOfile "Student.txt"

int Umonitor; // 监听用户输入

struct Student
{
    string Name;
    string Id;
    double Math;
    double English;
    double Oop;
    double Sum;
};

void ShowMenu() // 展示菜单
{
    // system("clear");
    ifstream fin(IOfile);
    puts("                 **************************************");
    puts("                          学生成绩管理系统v1.0         ");
    puts("                 --------------------------------------");
    puts("                        请输入您要操作的选项：          ");
    puts("                 --------------------------------------");
    if (!fin)
    {
        puts("                          1.首次使用请添加信息           \n");
    }
    else{
        puts("                              1.添加学生成绩           \n");
        puts("                              2.显示学生成绩           \n");
        puts("                              3.修改学生信息           \n");
        puts("                              4.删除学生信息           \n");
        puts("                              5.查询学生信息           \n");
        puts("                              0.退出系统               ");
        puts("                 **************************************");
    }
}

void ExitSystem() // 退出系统
{
    // system("clear");
    puts("\n\n\n                 **************************************");
    puts("                               感谢您的使用！          ");
    puts("                 **************************************\n\n\n");
    exit(0);
}

void InputError() // 输入错误
{
    puts("\n                 **************************************");
    puts("                      您的输入有误，请重新输入。   ");
    puts("                 **************************************\n");
}

void Add() // 添加
{
    // system("clear");
    puts("                 **************************************");
    puts("                                添加学生成绩           ");
    puts("                 --------------------------------------");
    puts("                               请输入学生信息          ");
    puts("                 **************************************\n");
    char x = 'Y';
    ofstream fout(IOfile, ios::app);
    if (!fout)
    {
        puts("文件读取失败！");
        exit(0);
    }
    Student *stud;
    stud = new Student;
    while (x == 'Y' || x == 'y')
    {
        printf("请输入姓名：");
        cin >> stud->Name;
        printf("请输入学号：");
        cin >> stud->Id;
        printf("请输入高数成绩：");
        cin >> stud->Math;
        while (stud->Math < 0 || stud->Math > 100)
        {
            puts("您输入的数据不合法，提示[0-100]，请重新输入");
            cin >> stud->Math;
        }
        printf("请输入英语成绩：");
        cin >> stud->English;
        while (stud->English < 0 || stud->English > 100)
        {
            puts("您输入的数据不合法，提示[0-100]，请重新输入");
            cin >> stud->English;
        }
        printf("请输入OOP成绩：");
        cin >> stud->Oop;
        while (stud->Oop < 0 || stud->Oop > 100)
        {
            puts("您输入的数据不合法，提示[0-100]，请重新输入");
            cin >> stud->Oop;
        }
        puts("");
        stud->Sum = stud->Math + stud->English + stud->Oop;
        fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
             << stud->Sum << endl;
        printf("学生信息添加成功！\n");

        puts("是否继续添加？(Y/N)");
        cin >> x;
        puts("");
    }
    fout.close();
}

void Display() // 显示学生成绩
{
    ifstream fin(IOfile);
    if (!fin)
    {
        puts("文件读取失败！");
        exit(0);
    }

    // system("clear");
    puts("*******************************************************");
    puts("                    显示学生成绩           ");
    puts("*******************************************************\n");
    cout << "序号\t姓名\t学号\t\t高数\t英语\tOOP成绩\t总分\n";
    Student *stud;
    stud = new Student;
    int count = 0;
    while (fin >> stud->Name >> stud->Id >> stud->Math >> stud->English >> stud->Oop >> stud->Sum)
    {
        count++;
        cout << left << setw(8) << count
             << left << setw(8) << stud->Name
             << left << setw(16) << stud->Id
             << left << setw(8) << stud->Math
             << left << setw(8) << stud->English
             << left << setw(8) << stud->Oop
             << stud->Sum
             << endl;
    }
    fin.close();
    puts("");
}

void Update() // 修改
{
    char x = 'Y';
    string tmp;
    // system("clear");
    puts("*******************************************************");
    puts("                    修改学生信息           ");
    puts("*******************************************************\n");

    while (x == 'Y' || x == 'y')
    {
        ifstream fin(IOfile);
        ofstream fout("tempS.txt");
        if (!fin)
        {
            puts("文件读取失败！");
            exit(0);
        }
        if (!fout)
        {
            puts("临时文件读取失败！");
            exit(0);
        }

        puts("         请先按照以下关键字之一查找学生：");
        puts("--------------------------------------");
        puts("            1.姓名\n");
        puts("            2.学号\n");
        puts("            0.返回上一级菜单");
        printf("请输入：");
        scanf("%d", &Umonitor);
        while ((Umonitor < 0) || (Umonitor > 2))
        {
            puts("");
            InputError();
            puts("         请先按照以下关键字之一查找学生：");
            puts("--------------------------------------");
            puts("            1.姓名\n");
            puts("            2.学号\n");
            puts("            0.返回上一级菜单");
            printf("请输入：");
            scanf("%d", &Umonitor);
        }

        if (Umonitor == 0)
            return;

        if (Umonitor == 1)
            printf("请输入姓名："), cin >> tmp;
        else if (Umonitor == 2)
            printf("请输入学号："), cin >> tmp;

        Student *stud;
        stud = new Student;
        bool isFind = false;
        while (fin >> stud->Name >> stud->Id >> stud->Math >> stud->English >> stud->Oop >> stud->Sum)
        {
            if ((tmp.compare(stud->Name)) && (tmp.compare(stud->Id)))
            {
                fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                     << stud->Sum << endl;
                continue;
            }
            isFind = true;

            cout << "\n姓名\t学号\t\t高数\t英语\tOOP成绩\t总分\n";
            cout << left << setw(8) << stud->Name
                 << left << setw(16) << stud->Id
                 << left << setw(8) << stud->Math
                 << left << setw(8) << stud->English
                 << left << setw(8) << stud->Oop
                 << stud->Sum
                 << endl;

            // system("clear");
            puts("\n         请选择要修改学生信息类型：");
            puts("--------------------------------------");
            puts("            1.姓名\n");
            puts("            2.学号\n");
            puts("            3.高数成绩\n");
            puts("            4.英语成绩\n");
            puts("            5.OOP成绩\n");
            puts("            0.返回上一级菜单");
            printf("请输入：");
            scanf("%d", &Umonitor);
            while ((Umonitor < 0) || (Umonitor > 5))
            {
                puts("");
                InputError();
                puts("\n         请选择要修改学生信息类型：");
                puts("--------------------------------------");
                puts("            1.姓名\n");
                puts("            2.学号\n");
                puts("            3.高数成绩\n");
                puts("            4.英语成绩\n");
                puts("            5.OOP成绩\n");
                puts("            0.返回上一级菜单");
                printf("请输入：");
                scanf("%d", &Umonitor);
            }

            if (Umonitor == 0)
                return;

            if (Umonitor == 1)
            {
                string NewName;
                printf("请输入新姓名：");
                cin >> NewName;

                // 确认机制
                printf("\n确认修改？(Y/N) ");
                cin >> x;
                if (x == 'N' || x == 'n')
                {
                    puts("\n取消修改成功!");
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                }
                else
                {
                    fout << NewName << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if (Umonitor == 2)
            {
                string NewId;
                printf("请输入新学号：");
                cin >> NewId;

                // 确认机制
                printf("\n确认修改？(Y/N) ");
                cin >> x;
                if (x == 'N' || x == 'n')
                {
                    puts("\n取消修改成功!");
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                }
                else
                {
                    fout << stud->Name << " " << NewId << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if (Umonitor == 3)
            {
                double NewMath;
                printf("请输入新高数成绩：");
                cin >> NewMath;
                while (NewMath < 0 || NewMath > 100)
                {
                    puts("您输入的数据不合法，提示[0-100]，请重新输入");
                    cin >> NewMath;
                }

                // 确认机制
                printf("\n确认修改？(Y/N) ");
                cin >> x;
                if (x == 'N' || x == 'n')
                {
                    puts("\n取消修改成功!");
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                }
                else
                {
                    stud->Sum = NewMath + stud->English + stud->Oop;
                    fout << stud->Name << " " << stud->Id << " " << NewMath << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if (Umonitor == 4)
            {
                double NewEng;
                printf("请输入新英语成绩：");
                cin >> NewEng;
                while (NewEng < 0 || NewEng > 100)
                {
                    puts("您输入的数据不合法，提示[0-100]，请重新输入");
                    cin >> NewEng;
                }

                // 确认机制
                printf("\n确认修改？(Y/N) ");
                cin >> x;
                if (x == 'N' || x == 'n')
                {
                    puts("\n取消修改成功!");
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                }
                else
                {
                    stud->Sum = stud->Math + NewEng + stud->Oop;
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << NewEng << " " << stud->Oop << " "
                         << stud->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if (Umonitor == 5)
            {
                double NewAlgor;
                printf("请输入新OOP成绩：");
                cin >> NewAlgor;
                while (NewAlgor < 0 || NewAlgor > 100)
                {
                    puts("您输入的数据不合法，提示[0-100]，请重新输入");
                    cin >> NewAlgor;
                }

                // 确认机制
                printf("\n确认修改？(Y/N) ");
                cin >> x;
                if (x == 'N' || x == 'n')
                {
                    puts("\n取消修改成功!");
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                         << stud->Sum << endl;
                }
                else
                {
                    stud->Sum = stud->Math + stud->English + NewAlgor;
                    fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << NewAlgor << " "
                         << stud->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
        }

        if (!isFind)
            puts("\n您要找的内容不存在！");

        fin.close();
        fout.close();

        remove(IOfile);
        rename("tempS.txt", IOfile);

        puts("\n是否继续修改？(Y/N)");
        cin >> x;
        puts("");
    }

    puts("");
}

void Delete() // 删除
{
    char x = 'Y';
    string tmp;
    // system("clear");
    puts("*******************************************************");
    puts("                    删除学生信息           ");
    puts("*******************************************************\n");

    while (x == 'Y' || x == 'y')
    {
        ifstream fin(IOfile);
        ofstream fout("tempS.txt");
        if (!fin)
        {
            puts("文件读取失败！");
            exit(0);
        }
        if (!fout)
        {
            puts("临时文件读取失败！");
            exit(0);
        }

        puts("         请选择要删除学生信息的关键字：");
        puts("--------------------------------------");
        puts("            1.姓名\n");
        puts("            2.学号\n");
        puts("            0.返回上一级菜单");
        printf("请输入：");
        scanf("%d", &Umonitor);
        while ((Umonitor < 0) || (Umonitor > 2))
        {
            puts("");
            InputError();
            puts("         请选择要删除学生信息的关键字：");
            puts("--------------------------------------");
            puts("            1.姓名\n");
            puts("            2.学号\n");
            puts("            0.返回上一级菜单");
            printf("请输入：");
            scanf("%d", &Umonitor);
        }

        if (Umonitor == 0)
            return;

        if (Umonitor == 1)
            printf("请输入姓名："), cin >> tmp;
        else if (Umonitor == 2)
            printf("请输入学号："), cin >> tmp;

        Student *stud;
        stud = new Student;
        bool isFind = false;
        while (fin >> stud->Name >> stud->Id >> stud->Math >> stud->English >> stud->Oop >> stud->Sum)
        {
            if ((tmp.compare(stud->Name)) && (tmp.compare(stud->Id)))
            {
                fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                     << stud->Sum << endl;
                continue;
            }
            isFind = true;

            cout << "\n姓名\t学号\t\t高数\t英语\tOOP成绩\t总分\n";
            cout << left << setw(8) << stud->Name
                 << left << setw(16) << stud->Id
                 << left << setw(8) << stud->Math
                 << left << setw(8) << stud->English
                 << left << setw(8) << stud->Oop
                 << stud->Sum
                 << endl;

            // 确认机制
            printf("\n确认删除？(Y/N) ");
            cin >> x;
            if (x == 'N' || x == 'n')
            {
                puts("\n取消删除成功!");
                fout << stud->Name << " " << stud->Id << " " << stud->Math << " " << stud->English << " " << stud->Oop << " "
                     << stud->Sum << endl;
                continue;
            }
            puts("\n数据删除成功!");
        }

        if (!isFind)
            puts("\n您要找的内容不存在！");

        fin.close();
        fout.close();

        remove(IOfile);
        rename("tempS.txt", IOfile);

        puts("\n是否继续删除？(Y/N)");
        cin >> x;
        puts("");
    }

    puts("");
}

void Query() // 查询
{
    char x = 'Y';
    string tmp;
    // system("clear");
    puts("*******************************************************");
    puts("                    查询学生信息           ");
    puts("*******************************************************\n");

    while (x == 'Y' || x == 'y')
    {
        ifstream fin(IOfile);
        if (!fin)
        {
            puts("文件读取失败！");
            exit(0);
        }

        puts("                  请选择查询方式：");
        puts("--------------------------------------");
        puts("                  1.姓名\n");
        puts("                  2.学号\n");
        puts("                  3.返回上一级菜单");
        printf("请输入：");
        scanf("%d", &Umonitor);
        while ((Umonitor < 1) || (Umonitor > 3))
        {
            puts("");
            InputError();
            puts("                  请选择查询方式：");
            puts("--------------------------------------");
            puts("                  1.姓名\n");
            puts("                  2.学号\n");
            puts("                  3.返回上一级菜单");
            printf("请输入：");
            scanf("%d", &Umonitor);
        }

        if (Umonitor == 3)
            return;

        if (Umonitor == 1)
            printf("请输入要查询的姓名："), cin >> tmp;
        else if (Umonitor == 2)
            printf("请输入要查询的学号："), cin >> tmp;
        Student *stud;
        stud = new Student;
        bool isFind = false;
        int count = 0;
        while (fin >> stud->Name >> stud->Id >> stud->Math >> stud->English >> stud->Oop >> stud->Sum)
        {
            if (Umonitor == 1)
            {
                if (!stud->Name.compare(tmp))
                {
                    if (!isFind)
                        cout << "\n序号\t姓名\t学号\t\t高数\t英语\tOOP成绩\t总分\n";
                    isFind = true;
                    count++;
                    cout << left << setw(8) << count
                         << left << setw(8) << stud->Name
                         << left << setw(16) << stud->Id
                         << left << setw(8) << stud->Math
                         << left << setw(8) << stud->English
                         << left << setw(8) << stud->Oop
                         << stud->Sum
                         << endl;
                }
            }
            else if (Umonitor == 2)
            {
                if (!stud->Id.compare(tmp))
                {
                    if (!isFind)
                        cout << "\n序号\t姓名\t学号\t\t高数\t英语\tOOP成绩\t总分\n";
                    isFind = true;
                    count++;
                    cout << left << setw(8) << count
                         << left << setw(8) << stud->Name
                         << left << setw(16) << stud->Id
                         << left << setw(8) << stud->Math
                         << left << setw(8) << stud->English
                         << left << setw(8) << stud->Oop
                         << stud->Sum
                         << endl;
                }
            }
        }
        if (!isFind)
            puts("\n您要找的内容不存在！");
        fin.close();
        puts("\n是否继续查询？(Y/N)");
        cin >> x;
        puts("");
    }

    puts("");
}

void MenuUmonitorAction() // 执行命令
{
    if (Umonitor == 1)
    {
        Add();
    }
    else if (Umonitor == 2)
    {
        Display();
    }
    else if (Umonitor == 3)
    {
        Update();
    }
    else if (Umonitor == 4)
    {
        Delete();
    }
    else if (Umonitor == 5)
    {
        Query();
    }
    else if (Umonitor == 0)
    {
        ExitSystem();
    }
}

int main()
{
    while (1)
    {
        ShowMenu();
        printf("请输入：");
        scanf("%d", &Umonitor);
        while ((Umonitor < 0) || (Umonitor > 6))
        {
            ShowMenu();
            InputError();
            printf("请输入：");
            scanf("%d", &Umonitor);
        }
        MenuUmonitorAction();
    }
    return 0;
}
