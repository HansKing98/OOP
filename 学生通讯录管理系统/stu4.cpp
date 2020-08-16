/*
 * @Description: 
 * @Author: hans
 * @Date: 2020-06-24 15:00:05
 * @LastEditTime: 2020-06-24 16:01:08
 * @LastEditors: hans
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #include <conio.h>
#define Null 0

struct student
{
    int num;
    char name[20];
    float chinese, math, english, ave, sum;
    struct student *next;
};

void ShowMenu()
{
    printf("           |------------------------------------------------|\n");
    printf("           |            欢迎光临学生成绩管理系统            |\n");
    printf("           |------------------------------------------------|\n");
    printf("           |       1  ==> 创建学生数据                      |\n");
    printf("           |       2  ==> 载入学生数据                      |\n");
    printf("           |       3  ==> 添加学生数据                      |\n");
    printf("           |       4  ==> 查询学生数据                      |\n");
    printf("           |       5  ==> 删除学生数据                      |\n");
    printf("           |       6  ==> 统计班级人数                      |\n");
    printf("           |       7  ==> 排序                              |\n");
    printf("           |       0  ==> 退出学生管理系统                  |\n");
    printf("           |------------------------------------------------|\n");
}

struct student *init(int n)
{
    int i;
    struct student *head, *p, *s;
    for (i = 1; i <= n; i++)
    {

        if (i == 1)
        {
            printf("请输入第%d个学生信息:\n", i);
            p = (struct student *)malloc(sizeof(struct student));
            printf("学号\n");
            scanf("%d", &p->num);
            printf("姓名\n");
            scanf("%s", &p->name[20]);
            printf("语文\n");
            scanf("%f", &p->chinese);
            printf("数学\n");
            scanf("%f", &p->math);
            printf("英语\n");
            scanf("%f", &p->english);
            p->sum = p->chinese + p->math + p->english;
            p->ave = p->sum / 3;
            head = p;
            if (n == 1)
                p->next = Null;
        }
        else
        {
            printf("请输入第%d个学生信息:\n", i);
            s = (struct student *)malloc(sizeof(struct student));
            printf("学号\n");
            scanf("%d", &s->num);
            printf("姓名\n");
            scanf("%s", &s->name[20]);
            printf("语文\n");
            scanf("%f", &s->chinese);
            printf("数学\n");
            scanf("%f", &s->math);
            printf("英语\n");
            scanf("%f", &s->english);
            s->sum = s->chinese + s->math + s->english;
            s->ave = s->sum / 3;
            p->next = s;
            p = s;
            s->next = Null;
        }
    }

    return head;
}

void insert(struct student *head)
{
    struct student *p, *pi;
    int xuehao;
    printf("请问要在哪个学生后面插入数据（输入学号）:");
    scanf("%d", &xuehao);
    pi = (struct student *)malloc(sizeof(struct student));
    p = head;
    printf("学号\n");
    scanf("%d", &pi->num);
    printf("姓名\n");
    scanf("%s", &pi->name[20]);
    printf("语文\n");
    scanf("%f", &pi->chinese);
    printf("数学\n");
    scanf("%f", &pi->math);
    printf("英语\n");
    scanf("%f", &pi->english);
    pi->sum = pi->chinese + pi->math + pi->english;
    pi->ave = pi->sum / 3;
    if (head == Null)
    {
        head = pi;
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

void search(struct student *head)
{
    int no;
    struct student *p;
    p = head;
    int n = 0;
    printf("1 按学号查找\n");
    printf("2 按分数段查找\n");

    scanf("%d", &n);
    switch (n)
    {
    case 1:
        printf("请输入要查找同学的学号:");
        scanf("%d", &no);
        while (p != Null)
        {
            if (p->num == no)
            {
                printf("------------------学生成绩表-----------------------\n");
                printf("===================================================\n");
                printf("%-5s%-8s%-8s%-8s%-8s%-8s%-8s\n", "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
                printf("===================================================\n");
                printf("%-5d%-8s%-8.1f%-8.1f%-8.1f%-8.1f%-8.1f\n", p->num, p->name, p->chinese, p->math, p->english, p->sum, p->ave);
                printf("===================================================\n");
                break;
            }
            p = p->next;
        }
        break;

    case 2:
    {
        float a, b;
        int choose;
        // char c;
        for (;;)
        {

            printf("\t|---------------------------------------|\n");
            printf("\t|               分数段查询              |\n");
            printf("\t|---------------------------------------|\n");
            printf("\t|       1  ==> 按总分成绩查询           |\n");
            printf("\t|       2  ==> 按语文成绩查询           |\n");
            printf("\t|       3  ==> 按数学成绩查询           |\n");
            printf("\t|       4  ==> 按英语成绩查询           |\n");
            printf("\t|       0  ==> 返回上一级菜单           |\n");
            printf("\t|---------------------------------------|\n");
            printf("请输入你要执行的操作:");
            scanf("%d", &choose);
            while (getchar() != '\n')
                ;
            switch (choose)
            {
            case 1:
            {
                p = head;
                printf("请输入所要查找的分数段:\n");
                printf("请输入第一个分数:\n");
                scanf("%f", &a);
                printf("请输入第二个分数:\n");
                scanf("%f", &b);
                printf("%-5s%-8s%-8s%-8s%-8s%-8s%-8s\n", "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
                while (p != Null)
                {
                    if (p->sum >= a && p->sum <= b)
                    {
                        printf("%-5d%-8s%-8.1f%-8.1f%-8.1f%-8.1f%-8.1f\n", p->num, p->name, p->chinese, p->math, p->english, p->sum, p->ave);
                    }
                    p = p->next;
                }
            }
            break;
            case 2:
            {
                p = head;
                printf("请输入所要查找的分数段:\n");
                printf("请输入第一个分数:\n");
                scanf("%f", &a);
                printf("请输入第二个分数:\n");
                scanf("%f", &b);
                printf("%-5s%-8s%-8s%-8s%-8s%-8s%-8s\n", "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
                while (p != Null)
                {
                    if (p->chinese >= a && p->chinese <= b)
                    {
                        printf("%-5d%-8s%-8.1f%-8.1f%-8.1f%-8.1f%-8.1f\n", p->num, p->name, p->chinese, p->math, p->english, p->sum, p->ave);
                    }
                    p = p->next;
                }
            }
            break;
            case 3:
            {
                p = head;
                printf("请输入所要查找的分数段:\n");
                printf("请输入第一个分数:\n");
                scanf("%f", &a);
                printf("请输入第二个分数:\n");
                scanf("%f", &b);
                printf("%-5s%-8s%-8s%-8s%-8s%-8s%-8s\n", "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
                while (p != Null)
                {
                    if (p->math >= a && p->math <= b)
                    {
                        printf("%-5d%-8s%-8.1f%-8.1f%-8.1f%-8.1f%-8.1f\n", p->num, p->name, p->chinese, p->math, p->english, p->sum, p->ave);
                    }
                    p = p->next;
                }
            }
            break;
            case 4:
            {
                p = head;
                printf("请输入所要查找的分数段:\n");
                printf("请输入第一个分数:\n");
                scanf("%f", &a);
                printf("请输入第二个分数:\n");
                scanf("%f", &b);
                printf("%-5s%-8s%-8s%-8s%-8s%-8s%-8s\n", "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
                while (p != Null)
                {
                    if (p->english >= a && p->english <= b)
                    {
                        printf("%-5d%-8s%-8.1f%-8.1f%-8.1f%-8.1f%-8.1f\n", p->num, p->name, p->chinese, p->math, p->english, p->sum, p->ave);
                    }
                    p = p->next;
                }
            }
            break;
            case 0:
                return;
            default:
                printf("\n\n您的输入有误!请重新输入：\n\n");
                break;
            }
        }
    }
    }
}

struct student *del(struct student *head, int n)
{
    struct student *p, *q;
    p = head;
    if (head == Null)
    {
        printf("没有学生的资料要删除!\n");
        return head;
    }

    while (p->num != n && p->next != Null)
    {
        q = p;
        p = p->next;
    }

    if (p->num == n)
    {
        if (p == head)
            head = p->next;
        else
            q->next = p->next;
        free(p);
    }
    else
        printf("找不到相应的学生资料!\n");
    return head;
}

void list(struct student *head)
{
    // int i = 0;
    struct student *p;
    p = head;
    printf("------------------学生成绩表-----------------------\n");
    printf("===================================================\n");
    printf("%-5s%-8s%-8s%-8s%-8s%-8s%-8s\n", "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
    printf("===================================================\n");
    while (p != Null)
    {
        printf("%-5d%-8s%-8.1f%-8.1f%-8.1f%-8.1f%-8.1f\n", p->num, p->name, p->chinese, p->math, p->english, p->sum, p->ave);
        p = p->next;
    }
    printf("===================================================\n");
    printf("\n\n");
}

void tongji(struct student *head)
{
    int i = 0;
    struct student *p;
    float chinese1 = 0, math1 = 0, english1 = 0;
    p = head;
    while (p != Null)
    {
        i = i + 1;
        chinese1 = chinese1 + p->chinese;
        math1 = math1 + p->math;
        english1 = english1 + p->english;
        p = p->next;
    }

    printf("班级总人数为：%d\n", i);
    printf("班级语文平均分为：%4.1f\n", chinese1 / i);
    printf("班级数学平均分为：%4.1f\n", math1 / i);
    printf("班级英语平均分为：%4.1f\n", english1 / i);
    printf("\n");
}

student *sort(student *head, int choose)
{
    student *p1, *p2 = head, *pm, *px;
    student mid;
    if (!p2)
        return head;
    for (p1 = p2; p1->next != NULL; p1 = p1->next)
    {
        pm = p1;
        for (p2 = p1->next; p2 != NULL; p2 = p2->next)
            switch (choose)
            {
            case 1:
                if (pm->num > p2->num)
                    pm = p2;
                break;
            case 2:
                if (pm->sum < p2->sum)
                    pm = p2;
                break;
            case 3:
                if (pm->chinese < p2->chinese)
                    pm = p2;
                break;
            case 4:
                if (pm->math < p2->math)
                    pm = p2;
                break;
            case 5:
                if (pm->english < p2->english)
                    pm = p2;
                break;
            }
        if (pm != p1)
        {
            mid = *pm;
            *pm = *p1;
            *p1 = mid;
            px = pm->next;
            pm->next = p1->next;
            p1->next = px;
        }
    }
    printf("\n排序后的成绩表为:\n");
    list(head);
    return head;
}

student *sort_all(student *head)
{
    int choose;
    for (;;)
    {
        printf("\t|---------------------------------------|\n");
        printf("\t|            学生成绩统计排序           |\n");
        printf("\t|---------------------------------------|\n");
        printf("\t|       1  ==> 按学生学号排序           |\n");
        printf("\t|       2  ==> 按学生总分排序           |\n");
        printf("\t|       3  ==> 按学生语文成绩排序       |\n");
        printf("\t|       4  ==> 按学生数学成绩排序       |\n");
        printf("\t|       5  ==> 按学生英语成绩排序       |\n");
        printf("\t|       0  ==> 返回上一级菜单           |\n");
        printf("\t|---------------------------------------|\n");

        printf("请输入你要执行的操作:");
        scanf("%d", &choose);
        while (getchar() != '\n')
            ;
        switch (choose)
        {
        case 1:
            head = sort(head, choose);
            break;
        case 2:
            head = sort(head, choose);
            break;
        case 3:
            head = sort(head, choose);
            break;
        case 4:
            head = sort(head, choose);
            break;
        case 5:
            head = sort(head, choose);
            break;
        case 0:
            return head;
        default:
            printf("\n\n您的输入有误!请重新输入：\n\n");
            break;
        }
    }
}

void save(struct student *head)
{
    // int i, j;
    FILE *fp;
    student *p;
    p = head;
    // char c; //head 头指针
    if ((fp = fopen("c:\\stu_list", "wb")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        system("stty -icanon");
        getchar();
        exit(0);
    }
    while (p)
    {
        fwrite(p, sizeof(student), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

struct student *read()
{
    // int i = 0, j;
    FILE *fp;
    struct student *p;    //工作指针
    student *last, *head; //最后一项的指针
    head = (student *)malloc(sizeof(student));
    last = head;
    if ((fp = fopen("c:\\stu_list", "rb")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        system("stty -icanon");
        getchar();
        exit(0);
    }
    while (!feof(fp))
    {
        p = (student *)malloc(sizeof(student));
        if (fread(p, sizeof(student), 1, fp) == 1)
        {
            last->next = p;
            last = last->next;
        }
    }
    fclose(fp);
    return head = head->next;
}

int main()
{
    // FILE *fp;
    char ch, c;
    int n = 0;
    struct student *head;
    ShowMenu();
    while ((ch = tolower(getchar())) != '0')
    {
        switch (ch)
        {
        case '1':
        {
            printf("请问有多少个学生的资料要输入?\n");
            scanf("%d", &n);
            head = init(n);
            list(head);
            save(head);
            break;
        }

        case '2':
        {
            head = read();
            list(head);
            break;
        }

        case '3':
        {
            insert(head);
            list(head);
            save(head);
            break;
        }

        case '4':
        {
            search(head);
            break;
        }

        case '5':
        {
            int num;
            printf("请输入要删除学生的学号:\n");
            scanf("%d", &num);
            head = del(head, num);
            list(head);
            save(head);
            break;
        }
        case '6':
        {
            tongji(head);
            break;
        }

        case '7':
        {
            head = read();
            sort_all(head);
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