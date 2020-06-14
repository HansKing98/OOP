/************************************************************/
/*程序名：学生成绩管理系统   作者：SDUQER                                  */
/*主要功能：添加删除修改排序;                                */
/*编制时间：2018年12月13日                                  */
/************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

#define PUT puts("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")

int order; // 用户输入的指令

struct Student {
    string Name;
    string Id;
    long long Idnum;
    double Math;
    double English;
    double Algorithm;
    double Sum;
    Student *nxt;
};

void ShowMenu() // 展示菜单
{
    system("Cls");
    puts("                 **************************************");
    puts("                          学生成绩管理系统v1.0         ");
    puts("                 --------------------------------------");
    puts("                        请输入您要操作的指令<0-6>：    ");
    puts("                 --------------------------------------");
    puts("                              1.录入学生信息           \n");
    puts("                              2.所有学生信息           \n");
    puts("                              3.修改学生信息           \n");
    puts("                              4.删除学生信息           \n");
    puts("                              5.查询学生信息           \n");
    puts("                              6.成绩数据分析           \n");
    puts("                              0.退出系统               ");
    puts("                 **************************************");
}

void ExitSystem() // 退出系统
{
    system("Cls");
    puts("\n\n\n                 **************************************");
    puts("                               感谢您的使用！          ");
    puts("                 **************************************\n\n\n");
    system("pause");
    exit(0);
}

void InputError() // 输入错误
{
    puts("\n                 **************************************");
    puts("                      您输入的指令有误，请重新输入。   ");
    puts("                 **************************************\n");
}

//void update(Student *nw)
//{
//  cout << "EXM " <<endl;
//  nw->Sum = nw->Math + nw->English + nw->Algorithm;
//  return;
//}

void Add() // 录入
{
    system("Cls");
    puts("                 **************************************");
    puts("                                录入学生信息           ");
    puts("                 --------------------------------------");
    puts("                               请输入学生信息          ");
    puts("                 **************************************\n");
    char x = 'Y';
    ofstream fout("data.txt",ios::app);
    if(!fout)
    {
        puts("数据文件打开失败！");
        system("pause");
        exit(0);
    }
    Student *nw;
    nw = new Student; 
    while(x == 'Y' || x == 'y')
    {
        printf("请输入姓名："); cin >> nw->Name;
        printf("请输入学号："); cin >> nw->Id;
        printf("请输入数学成绩："); cin >> nw->Math;
        while(nw->Math < 0 || nw->Math > 100)
        {
            puts("您输入的数据不合法，提示[0-100]，请重新输入");
            cin >> nw->Math;
        }
        printf("请输入英语成绩："); cin >> nw->English;
        while(nw->English < 0 || nw->English > 100)
        {
            puts("您输入的数据不合法，提示[0-100]，请重新输入");
            cin >> nw->English;
        }
        printf("请输入计算导论成绩："); cin >> nw->Algorithm;
        while(nw->Algorithm < 0 || nw->Algorithm > 100)
        {
            puts("您输入的数据不合法，提示[0-100]，请重新输入");
            cin >> nw->Algorithm;
        }
        puts("");
        nw->Sum = nw->Math + nw->English + nw->Algorithm;///
        fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " " 
            << nw->Sum << endl;///
        printf("学生信息添加成功！\n"); 
        
        puts("是否继续添加？(Y/N)");
        cin >> x;
        puts("");
    }
    fout.close();
    system("pause");
}

void Display() // 显示所有学生信息 
{
    ifstream fin("data.txt");
    if(!fin)
    {
        puts("数据文件打开失败！");
        system("pause");
        exit(0);
    }
    
    system("Cls");
    puts("*******************************************************");
    puts("                    所有学生信息           ");
    puts("*******************************************************\n");
    cout << "序号\t姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
    Student *nw;
    nw = new Student;
    int cnt = 0;
    while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
    {
        cnt ++;
        cout << left << setw(8) << cnt 
            << left << setw(8) << nw->Name 
            << left << setw(8) << nw->Id 
            << left << setw(16) << nw->Math 
            << left << setw(16) << nw->English 
            << left << setw(16) << nw->Algorithm 
            << nw->Sum 
            << endl;
    }
    fin.close();
    puts("");
    system("pause");
}

void Mend() // 修改
{
    char x = 'Y';
    string tmp;
    system("Cls");
    puts("*******************************************************");
    puts("                    修改学生信息           ");
    puts("*******************************************************\n");
    
    while(x == 'Y' || x == 'y')
    {   
        ifstream fin("data.txt");
        ofstream fout("data2.txt");
        if(!fin)
        {
            puts("数据文件打开失败！");
            system("pause");
            exit(0);
        }
        if(!fout)
        {
            puts("临时数据文件打开失败！");
            system("pause");
            exit(0);
        }
        
        puts("         请先按照以下关键字之一查找学生：");
        puts("--------------------------------------");
        puts("            1.姓名\n");
        puts("            2.学号\n");
        puts("            0.返回上一级菜单");
        printf("指令："); scanf("%d", &order);
        while((order<0)||(order>2))
        {
            puts("");
            InputError();       
            puts("         请先按照以下关键字之一查找学生：");
            puts("--------------------------------------");
            puts("            1.姓名\n");
            puts("            2.学号\n");
            puts("            0.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
        }
        
        if(order == 0)
            return;
        
        if(order == 1) printf("请输入姓名："), cin >> tmp;
        else if(order == 2) printf("请输入学号："), cin >> tmp;
        
        Student *nw;
        nw = new Student;
        bool isFind = false;
        while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
        {
            if((tmp.compare(nw->Name)) && (tmp.compare(nw->Id)))
            {
                fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                    << nw->Sum << endl;
                continue;
            }
            isFind = true;
            
            cout << "\n姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
            cout << left << setw(8) << nw->Name 
                << left << setw(8) << nw->Id 
                << left << setw(16) << nw->Math 
                << left << setw(16) << nw->English  
                << left << setw(16) << nw->Algorithm 
                << nw->Sum 
                << endl;
            
            system("Cls");
            puts("\n         请选择要修改学生信息类型：");
            puts("--------------------------------------");
            puts("            1.姓名\n");
            puts("            2.学号\n");
            puts("            3.数学成绩\n");
            puts("            4.英语成绩\n");
            puts("            5.算法导论成绩\n");
            puts("            0.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
            while((order<0)||(order>5))
            {
                puts("");
                InputError();       
                puts("\n         请选择要修改学生信息类型：");
                puts("--------------------------------------");
                puts("            1.姓名\n");
                puts("            2.学号\n");
                puts("            3.数学成绩\n");
                puts("            4.英语成绩\n");
                puts("            5.算法导论成绩\n");
                puts("            0.返回上一级菜单");
                printf("指令："); scanf("%d", &order);
            }
        
            if(order == 0)
                return;
            
            if(order == 1)
            {
                string NewName;
                printf("请输入新姓名："); cin >> NewName;
            
                // 防止用户输入错误
                printf("\n确认修改？(Y/N) "); cin >> x;
                if(x == 'N' || x == 'n') 
                {
                    puts("\n取消修改成功!");
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                }
                else {
                    fout << NewName << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if(order == 2)
            {
                string NewId;
                printf("请输入新学号："); cin >> NewId;
            
                // 防止用户输入错误
                printf("\n确认修改？(Y/N) "); cin >> x;
                if(x == 'N' || x == 'n') 
                {
                    puts("\n取消修改成功!");
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                }
                else {
                    fout << nw->Name << " " << NewId << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if(order == 3)
            {
                double NewMath;
                printf("请输入新数学成绩："); cin >> NewMath;
                while(NewMath < 0 || NewMath > 100)
                {
                    puts("您输入的数据不合法，提示[0-100]，请重新输入");
                    cin >> NewMath;
                }
            
                // 防止用户输入错误
                printf("\n确认修改？(Y/N) "); cin >> x;
                if(x == 'N' || x == 'n') 
                {
                    puts("\n取消修改成功!");
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                }
                else {
                    nw->Sum = NewMath + nw->English + nw->Algorithm;
                    fout << nw->Name << " " << nw->Id << " " << NewMath << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if(order == 4)
            {
                double NewEng;
                printf("请输入新英语成绩："); cin >> NewEng;
                while(NewEng < 0 || NewEng > 100)
                {
                    puts("您输入的数据不合法，提示[0-100]，请重新输入");
                    cin >> NewEng;
                }
            
                // 防止用户输入错误
                printf("\n确认修改？(Y/N) "); cin >> x;
                if(x == 'N' || x == 'n') 
                {
                    puts("\n取消修改成功!");
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                }
                else {
                    nw->Sum = nw->Math + NewEng + nw->Algorithm;
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << NewEng << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
            else if(order == 5)
            {
                double NewAlgor;
                printf("请输入新算法导论成绩："); cin >> NewAlgor;
                while(NewAlgor < 0 || NewAlgor > 100)
                {
                    puts("您输入的数据不合法，提示[0-100]，请重新输入");
                    cin >> NewAlgor;
                }
            
                // 防止用户输入错误
                printf("\n确认修改？(Y/N) "); cin >> x;
                if(x == 'N' || x == 'n') 
                {
                    puts("\n取消修改成功!");
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                        << nw->Sum << endl;
                }
                else {
                    nw->Sum = nw->Math + nw->English + NewAlgor;
                    fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << NewAlgor << " "
                        << nw->Sum << endl;
                    puts("\n数据修改成功!");
                }
            }
        }
        
        if(!isFind)
            puts("\n未找到该信息！");
        
        
        fin.close();
        fout.close();
        
        remove("data.txt");
        rename("data2.txt","data.txt"); 
        
        puts("\n是否继续修改？(Y/N)");
        cin >> x;
        puts("");
    }
    
    puts("");
    system("pause");
}

void Delete() // 删除
{
    char x = 'Y';
    string tmp;
    system("Cls");
    puts("*******************************************************");
    puts("                    删除学生信息           ");
    puts("*******************************************************\n");
    
    while(x == 'Y' || x == 'y')
    {   
        ifstream fin("data.txt");
        ofstream fout("data2.txt");
        if(!fin)
        {
            puts("数据文件打开失败！");
            system("pause");
            exit(0);
        }
        if(!fout)
        {
            puts("临时数据文件打开失败！");
            system("pause");
            exit(0);
        }
        
        puts("         请选择要删除学生信息的关键字：");
        puts("--------------------------------------");
        puts("            1.姓名\n");
        puts("            2.学号\n");
        puts("            0.返回上一级菜单");
        printf("指令："); scanf("%d", &order);
        while((order<0)||(order>2))
        {
            puts("");
            InputError();
            puts("         请选择要删除学生信息的关键字：");
            puts("--------------------------------------");
            puts("            1.姓名\n");
            puts("            2.学号\n");
            puts("            0.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
        }
        
        if(order == 0)
            return;
        
        if(order == 1) printf("请输入姓名："), cin >> tmp;
        else if(order == 2) printf("请输入学号："), cin >> tmp;
        
        Student *nw;
        nw = new Student;
        bool isFind = false;
        while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
        {
            if((tmp.compare(nw->Name)) && (tmp.compare(nw->Id)))
            {
                fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                    << nw->Sum << endl;
                continue;
            }
            isFind = true;
            
            cout << "\n姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
            cout << left << setw(8) << nw->Name 
                << left << setw(8) << nw->Id 
                << left << setw(16) << nw->Math 
                << left << setw(16) << nw->English 
                << left << setw(16) << nw->Algorithm 
                << nw->Sum 
                << endl;
            
            // 防止用户输入错误
            printf("\n确认删除？(Y/N) "); cin >> x;
            if(x == 'N' || x == 'n') 
            {
                puts("\n取消删除成功!");
                fout << nw->Name << " " << nw->Id << " " << nw->Math << " " << nw->English << " " << nw->Algorithm << " "
                    << nw->Sum << endl;
                continue; 
            }
            puts("\n数据删除成功!");
        }
        
        if(!isFind)
            puts("\n未找到该信息！");
        
        
        fin.close();
        fout.close();
        
        remove("data.txt");
        rename("data2.txt","data.txt"); 
        
        puts("\n是否继续删除？(Y/N)");
        cin >> x;
        puts("");
    }
    
    puts("");
    system("pause");
}

void Query() // 查询
{
    char x = 'Y';
    string tmp;
    system("Cls");
    puts("*******************************************************");
    puts("                    查询学生信息           ");
    puts("*******************************************************\n");
    
    while(x == 'Y' || x == 'y')
    {   
        ifstream fin("data.txt");
        if(!fin)
        {
            puts("数据文件打开失败！");
            system("pause");
            exit(0);
        }
        
        puts("                  请选择查询方式：");
        puts("--------------------------------------");
        puts("                  1.姓名\n");
        puts("                  2.学号\n");
        puts("                  3.返回上一级菜单");
        printf("指令："); scanf("%d", &order);
        while((order<1)||(order>3))
        {
            puts("");
            InputError();
            puts("                  请选择查询方式：");
            puts("--------------------------------------");
            puts("                  1.姓名\n");
            puts("                  2.学号\n");
            puts("                  3.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
        }
        
        if(order == 3)
            return;
        
        if(order == 1) printf("请输入要查询的姓名："), cin >> tmp;
        else if(order == 2) printf("请输入要查询的学号："), cin >> tmp;
        Student *nw;
        nw = new Student;
        bool isFind = false;
        int cnt = 0;
        while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
        {
            if(order == 1)
            {
                if(!nw->Name.compare(tmp))
                {
                    if(!isFind)
                        cout << "\n序号\t姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
                    isFind = true;
                    cnt ++;
                    cout << left << setw(8) << cnt 
                        << left << setw(8) << nw->Name 
                        << left << setw(8) << nw->Id 
                        << left << setw(16) << nw->Math 
                        << left << setw(16) << nw->English 
                        << left << setw(16) << nw->Algorithm 
                        << nw->Sum 
                        << endl; 
                }
            }
            else if(order == 2)
            {
                if(!nw->Id.compare(tmp))
                {
                    if(!isFind)
                        cout << "\n序号\t姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
                    isFind = true;
                    cnt ++;
                    cout << left << setw(8) << cnt 
                        << left << setw(8) << nw->Name 
                        << left << setw(8) << nw->Id 
                        << left << setw(16) << nw->Math 
                        << left << setw(16) << nw->English 
                        << left << setw(16) << nw->Algorithm 
                        << nw->Sum 
                        << endl; 
                }
            }
        }
        if(!isFind)
            puts("\n未找到该信息！");
        fin.close();
        puts("\n是否继续查询？(Y/N)");
        cin >> x;
        puts("");
    }
    
    puts("");
    system("pause");
}

void Sort_Tongji() // 统计分数区间 
{
    
    char x = 'Y';
    string tmp;
    system("Cls");
    puts("*******************************************************");
    puts("                    统计学生信息           ");
    puts("*******************************************************\n");
    
    double l, r; 
    while(x == 'Y' || x == 'y')
    {   
        ifstream fin("data.txt");
        if(!fin)
        {
            puts("数据文件打开失败！");
            system("pause");
            exit(0);
        }
        
        system("Cls");
        puts("                  请选择需要统计的科目：");
        puts("--------------------------------------");
        puts("                  1.数学\n");
        puts("                  2.英语\n");
        puts("                  3.算法导论\n");
        puts("                  0.返回上一级菜单");
        printf("指令："); scanf("%d", &order);
        if(order == 0)
            return;
        puts("请输入两个数字代表要统计的区间,如60 100：");
        cin >> l >> r;
        while((order<0)||(order>3))
        {
            puts("");
            InputError();
            puts("                  请选择需要统计的科目：");
            puts("--------------------------------------");
            puts("                  1.数学\n");
            puts("                  2.英语\n");
            puts("                  3.算法导论\n");
            puts("                  0.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
            if(order == 0)
                return;
            puts("请输入两个数字代表要统计的区间,如60 100：");
            cin >> l >> r;
        }
        
        if(order == 0)
            return;
        
        Student *Head = NULL, *nw;
        nw = new Student;
        int cnt = 0;
        while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
        {
            if(order == 1 && nw->Math >= l && nw->Math <= r)
            {
                cnt ++;
                nw->nxt = NULL;
                    //空 
                if(Head == NULL)
                {
                    Head = nw;
                    nw = new Student;
                    continue;
                }
                    //第一个就更da
                if(Head->Math <= nw->Math)
                {
                    nw->nxt = Head;
                    Head = nw;
                    nw = new Student;
                    continue;
                }
                    // 开始找
                Student *lst = Head, *p = Head->nxt; // lst 是p 的上一个
                while(p != NULL)
                {
                    if(nw->Idnum < p->Idnum)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
                // 执行完之后 p->Id >= nw->id, lst->Id <= nw->Id 
                nw->nxt = p;
                lst->nxt = nw;
    
                nw = new Student;
            }
            else if(order == 2 && nw->English >= l && nw->English <= r)
            {
                cnt ++;
            //  Insert(Head, nw);
                nw->nxt = NULL;
                    //空 
                if(Head == NULL)
                {
                    Head = nw;
                    nw = new Student;
                    continue;
                }
                    //第一个就更da
                if(Head->English <= nw->English)
                {
                    nw->nxt = Head;
                    Head = nw;
                    nw = new Student;
                    continue;
                }
                    // 开始找
                Student *lst = Head, *p = Head->nxt; // lst 是p 的上一个
                while(p != NULL)
                {
                    if(nw->English < p->English)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
                nw->nxt = p;
                lst->nxt = nw;
    
                nw = new Student;
            }
            else if(order == 3 && nw->Algorithm >= l && nw->Algorithm <= r)
            {
                cnt ++;
                nw->nxt = NULL;
                    //空 
                if(Head == NULL)
                {
                    Head = nw;
                    nw = new Student;
                    continue;
                }
                    //第一个就更da
                if(Head->Algorithm <= nw->Algorithm)
                {
                    nw->nxt = Head;
                    Head = nw;
                    nw = new Student;
                    continue;
                }
                    // 开始找
                Student *lst = Head, *p = Head->nxt; // lst 是 p 的上一个
                while(p != NULL)
                {
                    if(nw->Algorithm < p->Algorithm)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间
                        break;
                }
                // 执行完之后 p->Id >= nw->id, lst->Id <= nw->Id 
                nw->nxt = p;
                lst->nxt = nw;
    
                nw = new Student;
            }
            
        }
        
        //print
        system("Cls");
        Student *rs = Head;
        puts("*******************************************************");
        if(order == 1)
        {
            puts("              统计学生信息-----数学        ");
            cout << "           分数段" << l << "~" << r << "的总人数为 " << cnt << endl;
        }
        else if(order == 2)
        {
            puts("              统计学生信息-----英语        ");
            cout << "           分数段" << l << "~" << r << "的总人数为 " << cnt << endl;
        }
        else if(order == 3)
        {
            puts("              统计学生信息-----算法导论        ");
            cout << "           分数段" << l << "~" << r << "的总人数为 " << cnt << endl;
        }
        puts("*******************************************************\n"); 
        cout << "\n序号\t姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
        cnt = 0;
        while(rs != NULL)
        {
            cnt ++;
            cout << left << setw(8) << cnt 
                << left << setw(8) << rs->Name 
                << left << setw(8) << rs->Id 
                << left << setw(16) << rs->Math 
                << left << setw(16) << rs->English 
                << left << setw(16) << rs->Algorithm 
                << rs->Sum 
                << endl;
            rs = rs->nxt;
        }
        //*******************************************************
        
        fin.close();
        puts("\n是否继续统计？(Y/N)");
        cin >> x;
        puts("");
    }
    
    puts("");
    system("pause");
}


void Sort_fenxi() // 统计分数
{
    
    char x = 'Y';
    string tmp;
    system("Cls");
    puts("*******************************************************");
    puts("                    分析成绩信息           ");
    puts("*******************************************************\n");
    
    while(x == 'Y' || x == 'y')
    {   
        ifstream fin("data.txt");
        if(!fin)
        {
            puts("数据文件打开失败！");
            system("pause");
            exit(0);
        }
        
        system("Cls");
        puts("                  请选择需要分析的科目：");
        puts("--------------------------------------");
        puts("                  1.数学\n");
        puts("                  2.英语\n");
        puts("                  3.算法导论\n");
        puts("                  4.自由选择分数区段\n");
        puts("                  0.返回上一级菜单");
        printf("指令："); scanf("%d", &order);
        while((order<0)||(order>4))
        {
            puts("");
            InputError();
            puts("                  请选择需要统计的科目：");
            puts("--------------------------------------");
            puts("                  1.数学\n");
            puts("                  2.英语\n");
            puts("                  3.算法导论\n");
            puts("                  4.自由选择分数区段\n");
            puts("                  0.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
        }
        
        if(order == 0)
            return;
        if(order == 4)
        {
            Sort_Tongji();
            return;
        }
        
        Student *Head = NULL, *nw;
        nw = new Student;
        int cnt = 0, Math_60 = 0, Math_90 = 0, English_60 = 0, English_90 = 0, Algorithm_60 = 0, Algorithm_90 = 0;
        double Math_Max = 0, English_Max = 0, Algorithm_Max = 0;
        double Math_Min = 100, English_Min = 100, Algorithm_Min = 100;
        double Math_average = 0, English_average = 0, Algorithm_average = 0;
        while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
        {
            cnt ++;
            Math_60 += (int)(nw->Math>=60); Math_90 += (int)(nw->Math>=90);
            English_60 += (int)(nw->English>=60); English_90 += (int)(nw->English>=90);
            Algorithm_60 += (int)(nw->Algorithm>=60); Algorithm_90 += (int)(nw->Algorithm>=90);
            
            Math_Min = min(Math_Min, nw->Math);
            English_Min = min(English_Min, nw->English);
            Algorithm_Min = min(Algorithm_Min, nw->Algorithm);
            
            Math_Max = max(Math_Max, nw->Math);
            English_Max = max(English_Max, nw->English);
            Algorithm_Max = max(Algorithm_Max, nw->Algorithm);
            
            Math_average += nw->Math;
            English_average += nw->English; 
            Algorithm_average += nw->Algorithm;
        }
        
        Math_average /= (double)cnt;
        English_average /= (double)cnt;
        Algorithm_average /= (double)cnt;
        
        //print
        system("Cls");
        Student *rs = Head;
        puts("*******************************************************");
        if(order == 1)
        {
            puts("              分析学科信息-----数学        ");
            puts("*******************************************************\n"); 
            cout << "       最高分 : " << Math_Max << endl << endl; 
            cout << "       最低分 : " << Math_Min << endl << endl;
            cout << "       平均分 : " << Math_average << endl << endl; 
            cout << "         极差 : " << Math_Max-Math_Min << endl << endl;
            cout << "及格人数(>60) : " << Math_60 << endl << endl;
            cout << "       及格率 : " << ((double)Math_60/(double)cnt)*100.0 << "%" << endl << endl;
            cout << "优秀人数(>90) : " << Math_90 << endl << endl;
            cout << "       优秀率 : " << ((double)Math_90/(double)cnt)*100.0 << "%" << endl << endl;
        }
        else if(order == 2)
        {
            puts("              分析学科信息-----英语        ");
            puts("*******************************************************\n"); 
            cout << "       最高分 : " << English_Max << endl << endl; 
            cout << "       最低分 : " << English_Min << endl << endl;
            cout << "       平均分 : " << English_average << endl << endl; 
            cout << "         极差 : " << English_Max-English_Min << endl << endl;
            cout << "及格人数(>60) : " << English_60 << endl << endl;
            cout << "       及格率 : " << ((double)English_60/(double)cnt)*100.0 << "%" << endl << endl;
            cout << "优秀人数(>90) : " << English_90 << endl << endl;
            cout << "       优秀率 : " << ((double)English_90/(double)cnt)*100.0 << "%" << endl << endl;
        }
        else if(order == 3)
        {
            puts("              分析学科信息-----算法导论        ");
            puts("*******************************************************\n"); 
        //  cout << Algorithm_Max << " " << Algorithm_Min << endl;
            cout << "       最高分 : " << Algorithm_Max << endl << endl; 
            cout << "       最低分 : " << Algorithm_Min << endl << endl;
            cout << "       平均分 : " << Algorithm_average << endl << endl; 
            cout << "         极差 : " << Algorithm_Max-Algorithm_Min << endl << endl;
            cout << "及格人数(>60) : " << Algorithm_60 << endl << endl;
            cout << "       及格率 : " << ((double)Algorithm_60/(double)cnt)*100.0 << "%" << endl << endl;
            cout << "优秀人数(>90) : " << Math_90 << endl << endl;
            cout << "       优秀率 : " << ((double)Algorithm_90/(double)cnt)*100.0 << "%" << endl << endl;
        }
        //*******************************************************
        
        fin.close();
        puts("\n是否继续分析？(Y/N)");
        cin >> x;
        puts("");
    }
    
    puts("");
    system("pause");
}

void Sort() // 数据分析 
{
    
    char x = 'Y';
    string tmp;
    system("Cls");
    puts("*******************************************************");
    puts("                    分析学生信息           ");
    puts("*******************************************************\n");
    
    while(x == 'Y' || x == 'y')
    {   
        ifstream fin("data.txt");
        if(!fin)
        {
            puts("数据文件打开失败！");
            system("pause");
            exit(0);
        }
        
        system("Cls");
        puts("                  请选择分析方式：");
        puts("--------------------------------------");
        puts("                  1.学号从小到大\n");
        puts("                  2.数学成绩从大到小\n");
        puts("                  3.英语成绩从大到小\n");
        puts("                  4.算法导论成绩从大到小\n");
        puts("                  5.总成绩从大到小\n");
        puts("                  6.查看各科合格率、优秀率等分析数据\n");
        puts("                  0.返回上一级菜单");
        printf("指令："); scanf("%d", &order);
        while((order<0)||(order>6))
        {
            puts("");
            InputError();
            puts("                  请选择分析方式：");
            puts("--------------------------------------");
            puts("                  1.学号从小到大\n");
            puts("                  2.数学成绩从大到小\n");
            puts("                  3.英语成绩从大到小\n");
            puts("                  4.算法导论成绩从大到小\n");
            puts("                  5.总成绩从大到小\n");
            puts("                  6.查看各科合格率、优秀率等分析数据\n");
            puts("                  0.返回上一级菜单");
            printf("指令："); scanf("%d", &order);
        }
        
//      cout << "!@#^*()" << order << endl;
        
        if(order == 0)
        {
//          cout << "EXM" <<endl; 
            return;
        } 
        if(order == 6)
        {
            Sort_fenxi();
            Sort();
            return;
        }
        
        Student *Head = NULL, *nw;
        nw = new Student;
        // Insert;
        while(fin >> nw->Name >> nw->Id >> nw->Math >> nw->English >> nw->Algorithm >> nw->Sum)
        {
            if(order == 1)
            {
                int len = nw->Id.length();
                nw->Idnum = 0;
                for(int i = 0; i < len; ++ i)
                {
                    nw->Idnum += (long long)(nw->Id[i]-'0');
                    nw->Idnum *= 10;
                }
                nw->Idnum /= 10;
            }
            nw->nxt = NULL;
                //空 
            if(Head == NULL)
            {
                Head = nw;
                nw = new Student;
                continue;
            }
                //第一个就更小 
            if(order == 1 && Head->Idnum >= nw->Idnum)
            {
            //  cout << Head->Idnum << " " << nw->Idnum << endl;
                nw->nxt = Head;
                Head = nw;
                nw = new Student;
                continue;
            }
                //第一个就更da
            if(order == 2 && Head->Math <= nw->Math)
            {
                nw->nxt = Head;
                Head = nw;
                nw = new Student;
                continue;
            }
                //第一个就更da
            if(order == 3 && Head->English <= nw->English)
            {
                nw->nxt = Head;
                Head = nw;
                nw = new Student;
                continue;
            }
                //第一个就更da
            if(order == 4 && Head->Algorithm <= nw->Algorithm)
            {
                nw->nxt = Head;
                Head = nw;
                nw = new Student;
                continue;
            }
                //第一个就更da
            if(order == 5 && Head->Sum <= nw->Sum)
            {
                nw->nxt = Head;
                Head = nw;
                nw = new Student;
                continue;
            }
                // 开始找
            Student *lst = Head, *p = Head->nxt; // lst 是p 的上一个
            while(p != NULL)
            {
                if(order == 1)
                {
                    if(nw->Idnum > p->Idnum)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
                else if(order == 2)
                {
                    if(nw->Math < p->Math)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
                else if(order == 3)
                {
                    if(nw->English < p->English)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
                else if(order == 4)
                {
                    if(nw->Algorithm < p->Algorithm)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
                else if(order == 5)
                {
                    if(nw->Sum < p->Sum)
                    {
                        lst = p;
                        p = p->nxt;
                    }
                    else // 找到了要插入的这个刚好不大于的点,这个点位于 r,q之间 
                        break;
                }
            }
            // 执行完之后 p->Id >= nw->id, lst->Id <= nw->Id 
            nw->nxt = p;
            lst->nxt = nw;

            nw = new Student;
        }
        
        //print
        system("Cls");
        Student *r = Head;
        puts("*******************************************************");
        if(order == 1)
            puts("              分析学生信息-----学号从小到大        ");
        else if(order == 2)
            puts("              分析学生信息-----数学成绩从大到小    ");
        else if(order == 3)
            puts("              分析学生信息-----英语成绩从大到小    ");
        else if(order == 4)
            puts("              分析学生信息-----算法导论成绩从大到小");
        else if(order == 5)
            puts("              分析学生信息-----总成绩从大到小");
        puts("*******************************************************\n"); 
        cout << "\n序号\t姓名\t学号\t数学成绩\t英语成绩\t算法导论成绩\t总分\n";
        int cnt = 0; 
        while(r != NULL)
        {
            cnt ++;
            cout << left << setw(8) << cnt 
                << left << setw(8) << r->Name 
                << left << setw(8) << r->Id 
                << left << setw(16) << r->Math 
                << left << setw(16) << r->English 
                << left << setw(16) << r->Algorithm 
                << r->Sum 
                << endl;
            r = r->nxt;
        }
        //*******************************************************
        
        fin.close();
        puts("\n是否继续查看？(Y/N)");
        cin >> x;
        puts("");
    }
    
    puts("");
    system("pause");
}

void MenuOrderAction() // 执行命令
{
    if(order == 1) {
        Add();
    }
    else if(order == 2){
        Display();
    }
    else if(order == 3){
        Mend();
    }
    else if(order == 4){
        Delete();
    }
    else if(order == 5){
        Query();
    }
    else if(order == 6){
        Sort();
    }
    else if(order == 0){
        ExitSystem();
    }
//  cout << "ahha" << endl;
}

int main()
{
    while(1)
    {
        ShowMenu();
        printf("指令："); scanf("%d", &order);
        while((order<0)||(order>6))
        {
            ShowMenu();
            InputError();
            printf("指令："); scanf("%d", &order);
        }
        MenuOrderAction();
    }
    return 0;
}
