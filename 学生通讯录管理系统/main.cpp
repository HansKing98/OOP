/*
 * @Description: 
 * @Author: hans
 * @Date: 2020-06-24 15:00:05
 * @LastEditTime: 2020-06-24 21:17:22
 * @LastEditors: hans
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream> // fin fout
#include <iomanip> // setw()
using namespace std;
// ********
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #include <conio.h>
#define Null 0

typedef struct LinkList
{
    int seat;
    int num;
    char name[20];
    char telephone[11];
    struct LinkList *next;
} LinkList;

void ShowMenu()
{
    puts("                 **************************************");
    puts("                          学生通讯录管理系统v1.0         ");
    puts("                 --------------------------------------");
    puts("                        请输入您要操作的选项：          ");
    puts("                 --------------------------------------");
    puts("                              1.通讯录的建立           ");
    puts("                              2.插入通讯记录           ");
    puts("                              3.查询通讯记录           ");
    puts("                              4.删除通讯记录           ");
    puts("                              5.显示通讯录信息         ");
    puts("                              6.显示通讯录条数         ");
    puts("                              7.载入通讯录         ");
    puts("                              0.退出管理系统               ");
    puts("                 **************************************");
}

LinkList *creatIncreLink(int n)
{
    int i;
    struct LinkList *L, *p, *s;
    for (i = 1; i <= n; i++)
    {

        if (i == 1)
        {
            printf("请输入第%d个学生信息:\n", i);
            p = (struct LinkList *)malloc(sizeof(struct LinkList));
            printf("学号：");
            cin >> p->num;
            printf("请输入姓名：");
            cin >> p->name;
            printf("Tel：");
            cin >> p->telephone;
            L = p;
            if (n == 1)
                p->next = Null;
        }
        else
        {
            printf("请输入第%d个学生信息:\n", i);
            s = (struct LinkList *)malloc(sizeof(struct LinkList));
            printf("学号：");
            cin >> s->num;
            printf("请输入姓名：");
            cin >> s->name;
            printf("Tel：");
            cin >> s->telephone;
            p->next = s;
            p = s;
            s->next = Null;
        }
    }

    return L;
}

void insertYouXu(LinkList *L) // 插入一条通讯录
{
    struct LinkList *p, *pi;
    int xuehao;
    printf("请问要在哪个学生后面插入数据（输入学号）:");
    scanf("%d", &xuehao);
    pi = (struct LinkList *)malloc(sizeof(struct LinkList));
    p = L;
    printf("学号：");
    cin >> pi->num;
    printf("请输入姓名：");
    cin >> pi->name;
    printf("Tel：");
    cin >> pi->telephone;
    if (L == Null)
    {
        L = pi;
        pi->next = Null;
    }
    else
    {
        while ((p->num != xuehao) && (p->next != Null))
        {
            p = p->next;
        }
        if (p->next != Null)
        {
            pi->next = p->next;
            p->next = pi;
        }
        else
        {
            p->next = pi;
            pi->next = Null;
        }
    }
}

void searchNum(LinkList *L, int n)
{
    struct LinkList *p;
    p = L;
    while (p != Null)
    {
        if (p->num == n)
        {
            printf("------------------学生通讯录-----------------------\n");
            printf("===================================================\n");
            cout << "学号\t\t姓名\t\t电话\n";
            printf("===================================================\n");
            cout << left << setw(16) << p->num
                 << left << setw(16) << p->name
                 << left << setw(8) << p->telephone
                 << endl;
            printf("===================================================\n");
            break;
        }
        p = p->next;
    }
}

void searchName(LinkList *L, char n[20])
{
    struct LinkList *p;
    p = L;
    while (p != Null)
    {
        if (p->name == n)
        {
            printf("------------------学生通讯录-----------------------\n");
            printf("===================================================\n");
            cout << "学号\t\t姓名\t\t电话\n";
            printf("===================================================\n");
            cout << left << setw(16) << p->num
                 << left << setw(16) << p->name
                 << left << setw(8) << p->telephone
                 << endl;
            printf("===================================================\n");
            break;
        }
        else
        {
            cout << "未找到" << n;
            cout << "未找到2" << p;
        }
        p = p->next;
    }
}
struct LinkList *del(struct LinkList *L, int n)
{
    struct LinkList *p, *q;
    p = L;
    if (L == Null)
    {
        printf("没有学生的资料要删除!\n");
        return L;
    }

    while (p->num != n && p->next != Null)
    {
        q = p;
        p = p->next;
    }

    if (p->num == n)
    {
        if (p == L)
            L = p->next;
        else
            q->next = p->next;
        free(p);
    }
    else
        printf("找不到相应的学生资料!\n");
    return L;
}

void printList(LinkList *L) // 打印指针地址为L的通讯录
{
    // int i = 0;
    struct LinkList *p;
    p = L;
    printf("------------------学生通讯录-----------------------\n");
    printf("===================================================\n");
    cout << "学号\t\t姓名\t\t电话\n";
    printf("===================================================\n");
    while (p != Null)
    {
        cout << left << setw(16) << p->num
             << left << setw(16) << p->name
             << left << setw(8) << p->telephone
             << endl;
        p = p->next;
    }
    printf("===================================================\n");
    printf("\n\n");
}

void tongji(struct LinkList *L)
{
    int i = 0;
    struct LinkList *p;
    p = L;
    while (p != Null)
    {
        i = i + 1;
        p = p->next;
    }

    printf("通讯录总人数为：%d\n", i);
}

void save(struct LinkList *L)
{
    // int i, j;
    FILE *fp;
    LinkList *p;
    p = L;
    // char c; //L 头指针
    if ((fp = fopen("c:\\stu_list", "wb")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        system("stty -icanon");
        getchar();
        exit(0);
    }
    while (p)
    {
        fwrite(p, sizeof(LinkList), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

struct LinkList *read()
{
    // int i = 0, j;
    FILE *fp;
    struct LinkList *p; //工作指针
    LinkList *last, *L; //最后一项的指针
    L = (LinkList *)malloc(sizeof(LinkList));
    last = L;
    if ((fp = fopen("c:\\stu_list", "rb")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        system("stty -icanon");
        getchar();
        exit(0);
    }
    while (!feof(fp))
    {
        p = (LinkList *)malloc(sizeof(LinkList));
        if (fread(p, sizeof(LinkList), 1, fp) == 1)
        {
            last->next = p;
            last = last->next;
        }
    }
    fclose(fp);
    return L = L->next;
}

int main()
{
    // FILE *fp;
    char ch, c;
    int n = 0;
    struct LinkList *L;
    ShowMenu();
    while ((ch = tolower(getchar())) != '0')
    {
        switch (ch)
        {
        case '1':
        {
            printf("请问有多少个学生的资料要输入?\n");
            scanf("%d", &n);
            L = creatIncreLink(n);
            printList(L);
            save(L);
            break;
        }

        case '2':
        {
            insertYouXu(L);
            printList(L);
            save(L);
            break;
        }

        case '3':
        {
            printf("1 按学号查询\n");
            printf("2 按姓名查询\n");
            cin >> ch;
            switch (ch)
            {
            case '1':
            {
                printf("请输入要查找同学的学号:");
                int n;
                cin >> n;
                searchNum(L, n);
                break;
            }
            case '2':
            {
                printf("请输入要查找同学的姓名:");
                char n[20];
                cin >> n[20];
                searchName(L, n);
                break;
            }
            }
            break;
        }

        case '4':
        {
            int num;
            printf("请输入要删除学生的学号:\n");
            scanf("%d", &num);
            L = del(L, num);
            printList(L);
            save(L);
            break;
        }

        case '5':
        {
            L = read();
            printList(L);
            break;
        }
        
        case '6':
        {
            tongji(L);
            break;
        }

        case '7':
        {
            L = read();
            printList(L);
            break;
        }

        default:
            break;
        }
        printf("\n\n\t======>按Enter键返回主菜单\n");
        fflush(stdin);
        c = getchar();
        system("cls");
        ShowMenu();
    }
}