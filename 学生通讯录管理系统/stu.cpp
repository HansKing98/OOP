/*
 * @Description: 
 * @Author: hans
 * @Date: 2020-06-24 09:02:35
 * @LastEditTime: 2020-06-24 09:20:27
 * @LastEditors: hans
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int id;          //记录编号
    char name[20];   //姓名
    char cla[10];    //班级
    char number[20]; //学号
    char phone[15];  //电话号码
    char addr[30];   //家庭住址
} LinkList;
int creatIncreLink(LinkList L[]);
void Savelist(LinkList L[], int n);
int Loadlist(LinkList L[]);
int Dellist(LinkList L[], int n);
void S_asname(LinkList L[], int n);
void S_asphone(LinkList L[], int n);
void Scanlist(LinkList L[], int n);
void Update(LinkList L[], int n);
int Find(LinkList L[], int n, int id);
void getch();
void menu();

int main(void)
{
    int choice=0, count=0;
    LinkList L[10];

    do
    {
        if (choice >= 0 || choice <= 7)
            system("cls");
        printf("____使用本系统前请选择“7”读取数据，否则本程序无法正常运行!____\n");
        printf("----------------------欢迎使用学生通讯录管理系统-------------------");
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            count = creatIncreLink(L);
            break;
        case 2:
            Scanlist(L, count);
            break;
        case 3:
            S_asname(L, count);
            break;
        case 4:
            count = Dellist(L, count);
            break;
        case 5:
            Update(L, count);
            break;
        case 6:
            S_asphone(L, count);
            break;
        case 7:
            count = Loadlist(L);
            break;
        case 0:
            Savelist(L, count);
            return 0;
        default:
            system("cls");
            printf("输入错误!\n");
            break;
        }
    } while (choice != 0);
    printf("谢谢使用!\n");

    return 0;
}

void menu()
{
    printf("\n请选择下列功能:\n");
    printf("[1]－添加通讯记录。\n");
    printf("[2]－浏览全部通讯记录。\n");
    printf("[3]－按照姓名查找。\n");
    printf("[4]－删除通讯记录。\n");
    printf("[5]－修改通讯记录。\n");
    printf("[6]－按照电话号码查找。\n");
    printf("[7]－读取通讯记录。\n");
    printf("[0]－退出系统。\n");
    printf("请选择功能：");
}

int creatIncreLink(LinkList L[]) //通讯录的建立
{
    system("cls");
    int i, total;
    printf("------------------------------添加通讯记录------------------------\n");
    printf("您要输入记录的条数是：\n");
    scanf("%d", &total);
    for (i = 0; i < total; i++)
    {
        printf("您将要录入第条%d记录（共有%d条）\n", i + 1, total);
        printf("请输入姓名：\n");
        scanf("%s", L[i].name);
        printf("请输入班级：\n");
        scanf("%s", L[i].cla);
        printf("请输入学号：\n");
        scanf("%s", L[i].number);
        printf("请输入电话号码：\n");
        scanf("%s", L[i].phone);
        printf("请输入家庭住址：\n");
        scanf("%s", L[i].addr);

        printf("信息添加成功!\n");
        L[i].id = i;
        printf("您的记录编号为：%d\n", i);
        getch();
        system("cls");
    }
    return i;
}

void Scanlist(LinkList L[], int n)
{
    system("cls");
    if (n == 0)
    {
        printf("通讯录是空的!\n");
        getch();
        return;
    }
    printf("----------------------------全部记录信息浏览-------------------------");
    int i;
    printf("编号\t姓名\t班级\t学号\t电话号码\t家庭住址\n");
    for (i = 0; i < n; i++)
        printf("%d%10s%10s%5s%10s%25s\n", L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);

    getch();
}

void S_asphone(LinkList L[], int n)
{
    system("cls");
    int i, j = 0;
    char xphone[15], stop;
    if (n == 0)
    {
        printf("通讯录是空的!\n");
        getch();
        return;
    }
    printf("请输入要查找的电话号码：");
    scanf("%s", xphone);
    for (i = 0; i < n; i++)
    {
        if (strcmp(xphone, L[i].phone) == 0)
        {
            printf("编号\t姓名\t班级\t学号\t电话号码\t家庭住址\n");
            printf("%d%10s%10s%5s%10s%25s\n", L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);
            j++;
        }
    }

    if (j == 0)
        printf("未找到条目信息!\n");
    getch();
    scanf("%c", &stop);
}

int Dellist(LinkList L[], int n)
{
    system("cls");
    int i, p, q;
    char a;
    int xid;
    if (n == 0)
    {
        printf("通讯录是空的!\n");
        getch();
        return 0;
    }
    printf("请输入要删除条目的编号：");
    scanf("%d", &xid);
    i = Find(L, n, xid);
    if (i == -1)
        printf("未找到要删除通讯记录!!");
    else
    {
        printf("您要删除条目信息是：\n");
        printf("编号\t姓名\t班级\t学号\t电话号码\t家庭住址\n");
        printf("%d%10s%10s%5s%10s%25s\n", L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);
        printf("是否确认删除?y/n:");
        scanf("%c", &a);
        if (a == 'n')
        {
            printf("取消删除!\n");
            getch();
            return n;
        }
        else
        {
            for (p = i, q = p + 1; q <= n; p++, q++)
                L[p] = L[q];
            n--;
            printf("删除成功!!\n");
            getch();
        }
    }
    return n;
}

void Savelist(LinkList L[], int n)
{
    FILE *fp;
    int i;

    if ((fp = fopen("D:\\通讯录管理.txt", "w")) == NULL)
    {
        printf("文件打开失败!!");
        exit(0);
    }

    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t", L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);
    }

    if (fclose(fp))
    {
        printf("文件关闭失败!!");
        exit(0);
    }
    if ((fp = fopen("D:\\条目数.txt", "w")) == NULL)
    {
        printf("文件打开失败!!");
        exit(0);
    }
    fprintf(fp, "%d", n);
    if (fclose(fp))
    {
        printf("文件关闭失败!!");
        exit(0);
    }
    system("cls");
}

int Loadlist(LinkList L[])
{
    FILE *fp;
    int n;
    int i;
    if ((fp = fopen("D:\\条目数.txt", "r")) == NULL)
    {
        printf("文件打开失败!!");
        exit(0);
    }
    fscanf(fp, "%d", &n);
    if (fclose(fp))
    {
        printf("文件关闭失败!!");
        exit(0);
    }
    if ((fp = fopen("D:\\通讯录管理.txt", "r")) == NULL)
    {
        printf("文件打开失败!!");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d%s%s%s%s%s", &L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);
    }
    if (fclose(fp))
    {
        printf("文件关闭失败!!");
        exit(0);
    }
    system("cls");
    return n;
}

void Update(LinkList L[], int n)
{
    system("cls");
    int i, j, xid;
    if (n == 0)
    {
        printf("通讯录是空的!\n");
        getch();
        return;
    }
    printf("--------------------------数据修改-----------------------------");
    printf("编号\t姓名\t班级\t学号\t电话号码\t家庭住址\n");
    for (j = 1; j <= n; j++)
        printf("%d%10s%10s%5s%10s%25s\n", L[j].id, L[j].name, L[j].cla, L[j].number, L[j].phone, L[j].addr);
    printf("请输入要修改条目的编号：");
    scanf("%d", &xid);
    for (i = 0; i < n; i++)
    {
        printf("您要修改的原记录为：\n");
        printf("编号\t姓名\t班级\t学号\t电话号码\t家庭住址\n");
        printf("%d%10s%10s%5s%10s%25s\n", L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);
        printf("请输入姓名：\n");
        scanf("%s", L[i].name);
        printf("请输入学号：\n");
        scanf("%s", L[i].number);
        printf("请输入班级：\n");
        scanf("%s", L[i].cla);
        printf("请输入电话号码：\n");
        scanf("%s", L[i].phone);
        printf("请输入家庭住址：\n");
        scanf("%s", L[i].addr);

        printf("修改成功!!\n");
        getch();
        return;
    }
    printf("未找到记录!\n");
    return;
}

void S_asname(LinkList L[], int n)
{
    system("cls");
    int i, j = 0;
    char xname[20];
    if (n == 0)
    {
        printf("通讯录是空的!\n");
        getch();
        return;
    }
    printf("请输入要查找的姓名：");
    scanf("%s", xname);
    for (i = 1; i <= n; i++)
    {
        if (strcmp(xname, L[i].name) == 0)
        {
            printf("编号\t姓名\t班级\t学号\t电话号码\t家庭住址\n");
            printf("%d%10s%10s%5s%10s%25s\n", L[i].id, L[i].name, L[i].cla, L[i].number, L[i].phone, L[i].addr);
            j++;
        }
    }
    if (j == 0)
        printf("未找到要查找的信息!!");
    getch();
}

int Find(LinkList L[], int n, int id)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (id == L[i].id)
            return i;
    }
    return -1;
}
void getch()
{
    char stop;
    printf("确认？（按任意键并回车返回!）\n");
    getchar();
    scanf("%c", &stop);
    return;
}