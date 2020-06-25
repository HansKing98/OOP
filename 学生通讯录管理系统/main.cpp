/*
 * @Description: 
 * @Author: hans
 * @Date: 2020-06-24 15:00:05
 * @LastEditTime: 2020-06-25 15:30:42
 * @LastEditors: hans
 */
#include <iostream>
#include <iomanip> // setw()
using namespace std;

int seat;

typedef struct LinkList
{
    int num;
    char name[20];
    char telephone[12];
    struct LinkList *next;
} LinkList;

void ShowMenu() // 菜单功能
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

LinkList *prior(LinkList *L, LinkList *p) // 查找位于当前地址元素的前一元素的地址
{
    LinkList *p_prior = L;
    if (L->next == NULL)
        return (L);
    while (p_prior->next != p)
    {
        p_prior = p_prior->next;
    }
    return (p_prior);
}

void insertYouXu(LinkList *L, LinkList *Elem) // 插入一条通讯录,按照学号顺序
{
    LinkList *p;
    p = L;
    // while (p != NULL)
    while (p != NULL && Elem->num >= p->num)
    {
        if (p->num == Elem->num)
        {
            printf("该学号的学生已存在!\n");
            return;
        }
        p = p->next;
    } //确定Elem插入的位置
    if (p == NULL)
    {
        p = prior(L, p);
        Elem->next = NULL;
        p->next = Elem;
    }
    else //若为空表，插到头结点之后
    {
        p = prior(L, p);
        Elem->next = p->next;
        p->next = Elem;
    }
}

LinkList *creatIncreLink() // 链表的创建
{
    int i = 1, count = 1;
    printf("请输入创建学生信息条数：");
    cin >> count;
    int num;
    char name[20];
    char telephone[12];
    LinkList *L, *p;
    L = (LinkList *)malloc(sizeof(LinkList)); // 头结点
    L->next = NULL;

    while (i <= count)
    {
        printf("请输入第%d个学生信息:\n", i);
        printf("学号：");
        cin >> num;
        printf("请输入姓名：");
        cin >> name;
        printf("Tel：");
        cin >> telephone;
        p = (LinkList *)malloc(sizeof(LinkList)); //新结点
        p->num = num;
        strcpy(p->name, name);
        strcpy(p->telephone, telephone);
        insertYouXu(L, p); //有序的插入新结点
        i++;
    }

    return L;
}

int searchNum(LinkList *L, int n) // 按学号查找通讯录成员记录
{
    LinkList *p;
    p = L;
    while (p != NULL)
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
    return 0;
}

void searchName(LinkList *L, char n[20]) // 按姓名查找通讯录成员记录
{
    LinkList *p;
    p = L;
    while (p != NULL)
    {
        if (!strcmp(p->name, n))
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

LinkList *deleleElem(LinkList *L, int i) //从通讯录中按序号删除学号为n的数据
{
    LinkList *p, *q;
    p = L;
    int seat = 1;
    if (L == NULL)
    {
        printf("没有学生的资料要删除!\n");
        return L;
    }

    while (i < seat && p->next != NULL)
    {
        q = p;
        p = p->next;
        seat++;
    }

    if (p == L)
        L = p->next;
    else
        q->next = p->next;
    free(p);
    return L;
}

LinkList *delName(LinkList *L, char n[]) //从通讯录中按序号删除学号为n的数据
{
    LinkList *p, *q;
    p = L;
    if (L == NULL)
    {
        printf("没有学生的资料要删除!\n");
        return L;
    }

    while (!strcmp(p->name, n) && p->next != NULL)
    {
        q = p;
        p = p->next;
    }

    if (!strcmp(p->name, n))
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

LinkList *delNum(LinkList *L, int n) //从通讯录中按序号删除学号为n的数据
{
    LinkList *p, *q;
    p = L;
    if (L == NULL)
    {
        printf("没有学生的资料要删除!\n");
        return L;
    }

    while (p->num != n && p->next != NULL)
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
    LinkList *p;
    p = L->next;
    printf("------------------学生通讯录-----------------------\n");
    printf("===================================================\n");
    cout << "学号\t\t姓名\t\t电话\n";
    printf("===================================================\n");
    if (L == NULL || L->next == NULL)
        printf("该通讯录中数据\n");
    else
        while (p != NULL)
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

void tongji(LinkList *L) // 链表计数
{
    int i = 0;
    LinkList *p;
    p = L;
    while (p != NULL)
    {
        i = i + 1;
        p = p->next;
    }

    printf("通讯录总人数为：%d\n", i);
}

void save(LinkList *L) // 通讯录保存函数
{
    FILE *fp;
    LinkList *p;
    p = L;
    if ((fp = fopen("stu_list", "wb")) == NULL)
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

LinkList *read() // 读取通讯录文件
{
    FILE *fp;
    LinkList *p;        //工作指针
    LinkList *last, *L; //最后一项的指针
    L = (LinkList *)malloc(sizeof(LinkList));
    last = L;
    if ((fp = fopen("stu_list", "rb")) == NULL)
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
    char ch, c;
    LinkList *L;
    ShowMenu();
    while ((ch = tolower(getchar())) != '0')
    {
        switch (ch)
        {
        case '1':
        {
            L = creatIncreLink();
            printList(L);
            save(L);
            break;
        }

        case '2':
        {
            LinkList *p;
            p = (LinkList *)malloc(sizeof(LinkList)); //新结点
            // char name[20];
            printf("请输入通讯者的学号和姓名：\n");
            printf("请输入学号: ");
            cin >> p->num;
            printf("请输入姓名: ");
            cin >> p->name;
            printf("请输入电话号码: ");
            cin >> p->telephone;
            insertYouXu(L, p); //有序的插入新结点
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
                cin >> n;
                searchName(L, n);
                break;
            }
            }
            break;
        }

        case '4':
        {

            printf("1 按序号删除\n");
            printf("2 按姓名删除\n");
            printf("3 按学号删除\n");
            cin >> ch;
            switch (ch)
            {
            case '1':
            {
                printf("请输入要查找同学的序号:");
                int n;
                cin >> n;
                searchNum(L, n);
                break;
            }
            case '2':
            {
                printf("请输入要删除学生的姓名:\n");
                char name[20];
                cin >> name;
                L = delName(L, name);
                break;
            }
            case '3':
            {
                int num;
                printf("请输入要删除学生的学号:\n");
                scanf("%d", &num);
                L = delNum(L, num);
                break;
            }
            }
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
        ShowMenu();
    }
}