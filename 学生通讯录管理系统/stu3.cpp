/*
 * @Description: 
 * @Author: hans
 * @Date: 2020-06-24 09:41:48
 * @LastEditTime: 2020-06-24 09:56:12
 * @LastEditors: hans
 */

#include <stdio.h>
#include <stdlib.h> //除了一些常用函数需要以外，如在网上查到的system清屏函数，exit退出函数也需要这个H文件
#include <string.h> //程序中的字符比较strump函数需要这个H文件
// #include <conio.h>  //在网上查的getch函数需要这一个H文件

#define ID struct tel //宏定义，方便以后的使用
 
struct tel

{
    char name[10];  //姓名
    char tele[15];  //电话
    char style[15]; //类型
    char mail[20];  //邮箱
    ID *next;
};

int total = 0; //通讯录人数的统计

void Save(ID *head); //保存函数的声明，因为你在调用Create函数时用到了

/***********************************************

*函数名：Create（创建）
*功能：创建一个单链表，把数据放在链表里面，一旦需要保存，就调用save函数保存在文件中
*返回值：ID *（结构体指针）

***********************************************/
ID *Create()
{
    total = 0;
    int k = 0;
    int i = 0;
    ID *head, *p1, *p2, *p3; //创建一个头指针和两个可用于移动的指针
    char saveflag;           //这个字符用来接收是否保存的Y or y的
    head = p1 = p2 = NULL;   //首先把上述的指针赋值为空
    while (1)                //这个循环可以实现多次添加通讯人
    {
        p1 = (ID *)malloc(sizeof(ID)); //给p1分配一个动态存储空间
        printf("请输入姓名，当你不想录入时，在姓名处输入*，结束录入\n");
        scanf("%s", p1->name);          //输入姓名
        if (strcmp(p1->name, "*") == 0) //这里是结束函数的一个通道（没有输入联系人），就是判断输入的是否为*号
        {
            if (total == 0) //当记录人数为0时做以下事情
            {
                printf("你输入了0条记录，单链表没有创建...\n");
                free(p1);      //释放p1空间
                return (head); //把head返回
            }
            else
            {
                break; //跳出while循环
            }
        }
        printf("请输入电话号码： \n");
        scanf("%s", p1->tele);
        printf("请输入类别：办公类、个人类、商务类\n");
        scanf("%s", p1->style);
        printf("请输入邮箱:\n");
        scanf("%s", p1->mail);
        if (k > 0)
        {
            p3 = head;         //让p3从头开始遍历
            while (p3 != NULL) //当p3不为空时
            {
                if ((strcmp(p1->name, p3->name) == 0) && (strcmp(p1->tele, p3->tele) == 0))
                {
                    free(p1);
                    printf("你重复输入了，这一条不保存。请按任意键返回主菜单\n");
                    i = 1;
                    printf("请按任意键返回主菜单\n");
                    getchar(); //按下任意键就进入下一条语句的函数
                    break;
                }
                if ((strcmp(p1->name, p3->name)) && (strcmp(p1->tele, p3->tele)) && (p3 == p2)) //一旦到了最后一个结点，并且还没有和他相同的信息的时候
                {
                    i = 0;
                    break; //跳出第一个循环
                }
                p3 = p3->next;
            }
            if (i == 1)
            {
                break; //跳出第二个循环
            }
        }
        if (head == NULL) //这是第一次进来的时候，head为空
        {
            head = p1; //head和p2都为p1
            p2 = p1;
        }
        else
        {
            p2->next = p1; //这是第二次以后的执行命令，目的就是p2向后移，而head的位置不变
            p2 = p1;
        }
        total++; //这是录入一个人后，总数就加1
        k++;
    }
    p2->next = NULL; //把最后一个的指针域赋值为NULL，在以后的函数中，很多判断都是靠这一点来实现的，所以很重要
    if (i == 0)
    {
        free(p1);
        printf("\n新建通讯录成功，共有%d个联系人，是否保存？(Y/N)\n ", total);
        getchar();                              //这个getchar是吸收回车键的，十分重要
        scanf("%c", &saveflag);                 //写入一个字符
        if (saveflag == 'y' || saveflag == 'Y') //判断它是不是为Y or y
            Save(head);                         //进入到保存函数里面，保存到文件里面
        else
            printf("\n没有保存到成功保存到文件，请在返回主菜单后输入3保存通讯录。\n");
    }
    return head; //返回一个头指针，这个是最重要的，因为在后面的函数中，大部分都是要头指针作为参数的
}

/************************************************

*函数名：Save（保存）
*功能：将链表（数据）保存在文件
*返回值：NULL

*************************************************/
void Save(ID *head)
{
    FILE *fp;                                       //定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    ID *t;                                          //定义一个指针，从头到尾遍历一遍单链表，向文件中写入
    if ((fp = fopen("telephone.txt", "w")) == NULL) //打开文件来写入
    {
        printf("打开文件失败！\n");
        getchar(); //输入任意键进入下一步
        exit(0); //退出
    }
    t = head;         //把头指针赋给t，让它从头开始
    while (t != NULL) //只要t指针不为空，即等于链表没有结束
    {
        fwrite(t, sizeof(ID), 1, fp); //把链表的东西写入文件中
        t = t->next;                  //把指针往后移
    }
    fclose(fp); //把文件关闭
    printf("文件保存成功\n");
    printf("请按任意键返回主菜单\n");
    getchar(); //按下任意键就进入下一条语句的函数
}

/************************************************

*函数名：Read（读取文件）
*功能：读取文件中的信息并将其放入单链表中，并且最后返回一个头指针
*返回值：ID *（结构体指针）

*************************************************/
ID *Read()
{
    FILE *fp;                                       //定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
    ID *t1, *t2, *head = NULL;                      //定义3个结构体指针，一个头指针用于返回，2个可移动的临时指针
    char ch;                                        //定义一个变量来存放文件的第一个字符，但在这个函数里面主要是用来判断文件是不是为空
    if ((fp = fopen("telephone.txt", "r")) == NULL) //这可以判断有没有文件给你去读取
    {
        printf("打开文件失败！没有该文件\n\n");
        printf("请按任意键退出程序\n");
        getchar(); //一个在网上查到的函数，用于你可以按任意键进入下一步
        exit(0); //退出程序
    }

    /****** 这是在网上查到的一段有关于文件的程序 ******/
    ch = fgetc(fp); //这是在网上查到的一个有关文件的函数，返回值是文件的第一个字符，当文件为空的时候，他返回的是一个特殊值：EOF
    if (ch == EOF)  //当文件为空的时候
    {
        printf("文件为空，请重新建立一个通讯录\n");
        printf("请按任意键返回主菜单\n");
        getchar();       //按下任意键就进入下一条语句的函数
        return (head); //返回一个指针，因为这个函数要有一个返回值，所以把头指针返回出去
    }
    else
    {
        rewind(fp); //这个函数是把一个文件的位置指针从新移至开头，不然的话会出现一个组数据丢失
    }
    /*************************************************/

    t1 = (ID *)malloc(sizeof(ID)); //开始申请动态空间，用t1接着
    head = t1;                     //把t1赋给头结点
    while (!feof(fp))              //feof函数的功能是判断这个文件是不是结束了，如果结束了，返回一个非零值，否则返回一个0，来自百度
    {
        if (fread(t1, sizeof(ID), 1, fp) != 1) //根据书上的定义，fread函数的类型为int型，返回一个输入数据项的个数
            break;                             //如果没有读取的内容，则结束
        total++;                               //人数加1
        t1->next = (ID *)malloc(sizeof(ID));   //把在申请动态空间的同时，把t1的next指向下一个结点
        t2 = t1;                               //让t2和t1指向同一个地方
        t1 = t1->next;                         //t1向后移一个结点
    }
    t2->next = NULL; //把t2的指针域赋值为空，因为数据最多到t2这里
    free(t1);        //把后来的t1申请多出来的空间清空掉
    fclose(fp);      //关闭文件
    printf("文件已经成功读取\n");
    printf("请按任意键返回主菜单\n");
    getchar();     //按下任意键就进入下一条语句的函数
    return head; //返回一个头指针，因为在没有创建一个单链表和文件的时候，就是靠这个头指针进行一系列的操作的
}

/************************************************

*函数名：Search（查询）
*功能：可以通过姓名查询,也可以通过类别查询
*返回值：NULL

*************************************************/
void Search(ID *head)
{
    int num; //定义一个变量在确定是否进入switch语句里
    int count = 1;
    ID *p;                    //定义一个结构体变量，用来放头指针
    int flag, searchflag = 1; //变量flag是用来判断是不是有符合要求的数据，变量searchflag是一个while语句的出入口
    char c, temp;             //变量c是来存放姓名的首字符的，变量temp是用来存放Y or y的
    char ch[10];              //数组ch用来放输入的类型
    printf("请输入你希望通过什么方式查询：（请输入序号）\n");
    printf("1.姓名\n");
    printf("2.类别\n");
    printf("3.所有人\n");
    scanf("%d", &num); //选择你想要查询的方式
    getchar();         //吸收回车键
    switch (num)       //switch语句是看你要进入哪个功能
    {
    case 1:
        while (searchflag) //searchflag已经初始化为1，所以进入while中，通过改变searchflag的值确定是不是离开while语句
        {
            flag = 0; //初始化为0
            printf("\n请输入待查找者的首字母，或者查找者的姓: \n");
            scanf("%c", &c);  //存放你的要求，首字母或姓
            getchar();        //吸收回车键
            p = head;         //把形参头指针head给p
            while (p != NULL) //一直循环直到p结点为空
            {
                if (p->name[0] == c) //当姓名的第一个字符和你的要求c一样的时候，进入if语句
                {
                    printf("%d. ", count);
                    count++;
                    printf("姓名： %s\t电话号码: %s\t类型:%s\t邮箱:%s\n", p->name, p->tele, p->style, p->mail);
                    flag = 1; //flag赋值为1，表示为已经查到了数据了
                }
                p = p->next; //p1指针向后移
            }
            if (flag == 0) //这表示为没有找到相关数据
            {
                printf("\n对不起,未能找到符合条件的记录\n");
            }
            printf("\n查找完毕，是否需要重新查询？ Y/N\n");
            scanf("%c", &temp);             //输入是或者否（Y/N）
            getchar();                      //吸收回车键
            if (temp == 'y' || temp == 'Y') //判断是不是y or Y
            {
                searchflag = 1; //回到while继续从头开始
            }
            else
            {
                searchflag = 0; //回到while并且退出
                system("cls");  //为了美观，在网上找了清屏函数
            }
        }
        break;
    case 2:
        while (searchflag) //searchflag已经初始化为1，所以进入while中，通过改变searchflag的值确定是不是离开while语句
        {
            flag = 0; //初始化为0,
            printf("\n请输入被查找人的类别:（如：“办公类”“个人类”“商务类”） \n");
            scanf("%s", ch);  //用字符数据接收字符串
            getchar();        //吸收回车键
            p = head;         //把形参头指针head给p
            while (p != NULL) //searchflag已经初始化为1，所以进入while中，通过改变searchflag的值确定是不是离开while语句
            {
                if (strcmp(p->style, ch) == 0) //当你的类别和你输入的类别一样的时候，stcump会返回0
                {
                    printf("%d. ", count);
                    count++;
                    printf("姓名： %s\t电话号码: %s\t类型:%s\t邮箱:%s\n", p->name, p->tele, p->style, p->mail);
                    flag = 1; //flag赋值为1，表示为已经查到了数据了
                }
                p = p->next; //p1指针向后移
            }
            if (flag == 0) //这表示为没有找到相关数据
            {
                printf("\n对不起,未能找到符合条件的记录\n");
            }
            printf("\n查找完毕，是否需要重新查询？ Y/N\n");
            scanf("%c", &temp); //输入是或者否（Y/N）
            getchar();
            if (temp == 'y' || temp == 'Y') //判断是不是y or Y
            {
                searchflag = 1; //回到while继续从头开始
            }
            else
            {
                searchflag = 0; //回到while并且退出
                system("cls");  //为了美观，在网上找了清屏函数
            }
        }
        break;
    case 3:
        p = head;         //把头指针给p
        while (p != NULL) //p不为空的时候，while一直循环
        {
            printf("%d. ", count);
            count++;
            printf("姓名： %s\t电话号码: %s\t类型:%s\t邮箱:%s\n", p->name, p->tele, p->style, p->mail);
            p = p->next; //p向后移
        }
        printf("查找完成！请按任意键返回主菜单\n");
        getchar();       //输入任意键函数
        system("cls"); //为了美观，在网上找了清屏函数
        break;
    default:
        printf("你输入错了吧，请你输入任意键返回主菜单...\n");
        getchar(); //一个在网上查到的函数，用于你可以按任意键进入下一步
    }
}

/************************************************

*函数名： Delete（删除）
*功能：通过查找姓名来实现删除通讯记录
*返回值：ID *（结构体指针）

*************************************************/
ID *Delete(ID *head)
{
    // ID *p1, *p2, *p3;    //定义三个结构体变量，p3是用来遍历整一个单链表的，p1，p2是用来找那个一样的结点在哪里的
    // char saveflag;       //存放是或者否
    // char temp;           //同上
    // int i=0;               //i是这个函数的关键，因为我尝试了很多种方法，都是有这样那样的问题，虽然这个方法没有效率，但是可行
    // p1 = p2 = p3 = head; //把head赋给p1,p2,p3
    // char s[10];          //存放输入的名字
    // system("cls");       //清屏
    // printf("请输入要删除的姓名:\n");
    // scanf("%s", s);
    // getchar();
    // // while (p3 != NULL) //这个while语句的作用是在遍历整个单链表时，当遇到一样的名字时把i赋值，引导下面的工作
    // // {
    // //     if (strcmp(p3->name, s) == 0) //判断是不是你输入的名字是不是和通讯录中的相等
    // //     {
    // //         i = 1; //当存在一样的名字时，i=1
    // //         break;
    // //     }
    // //     if (strcmp(p3->name, s) && (p3->next) == NULL)
    // //     {
    // //         i = 0; //不存在一样的名字时，i=1
    // //         break;
    // //     }
    // //     p3 = p3->next; //p3指针向后移
    // // }
    // if (i == 1) //当i=1时，开始找那个一样名字的结点在哪里
    // {
    //     while (strcmp(p1->name, s) && p1 != NULL) //当遇到一样名字的时候循环结束，那么这时的p1就是那个名字一样的结点
    //     {
    //         p2 = p1;       //p2永远在p1的前一个结点
    //         p1 = p1->next; //p1指针向后移
    //     }
    // }
    // if (i == 0) //当i=0时，就是没有这个名字的人，返回主菜单
    // {
    //     printf("对不起，没有找到要删除的通讯名单，请检查你要删除的姓名是否正确\n");
    //     printf("请按任意键返回主菜单\n");
    //     getchar(); //按下任意键就进入下一条语句的函数
    // }
    // if ((i == 1) && (p1 != NULL)) //当在遍历完整个链表以后，存在一样的名字（即i==1），并且p1不为空，说明没有走出这个链表
    // {
    //     printf("你要删除的通讯录人为:\n");
    //     printf("姓名:%s\t电话号码:%s\t类型:%s\t邮箱:%s\n", p1->name, p1->tele, p1->style, p1->mail);
    //     printf("请确定是否要删除该记录？Y/N?\n");
    //     scanf("%c", &saveflag);                 //输入，存放Y or N
    //     getchar();                              //吸收回车键
    //     if (saveflag == 'y' || saveflag == 'Y') //当输入是的时候
    //     {
    //         if (p1 == head)      //判断是不是在数据第一个
    //             head = p1->next; //把第一个结点去掉
    //         else
    //             p2->next = p1->next; //p2的next域指向下下个结点的next域
    //         free(p1);                //把p1结点的空间释放
    //         printf("该电话记录已删除成功,是否存盘?Y/N?\n");
    //         scanf("%c", &temp);             //输入，存放Y or N
    //         getchar();                      //吸收回车键
    //         if (temp == 'y' || temp == 'Y') //当输入是的时候
    //         {
    //             Save(head); //调用保存函数
    //             total--;    //人数减一
    //         }
    //         else
    //         {
    //             printf("请在退出系统之前返回主菜单按3进行保存\n");
    //             printf("请按任意键返回主菜单\n");
    //             getchar(); //按下任意键就进入下一条语句的函数
    //         }
    //     }
    //     else
    //     {
    //         printf("该通讯录没有被删除 \n");
    //         printf("请按任意键返回主菜单\n");
    //         getchar(); //按下任意键就进入下一条语句的函数
    //     }
    // }
    return (head); //return一个已经进行修改的链表的头指针
}

/************************************************

*函数名： Add（添加）
*功能：添加人物信息
*返回值：ID *（结构体指针）

*************************************************/
ID *Add(ID *head)
{
    char saveflag; //存放是或者否
    int k = 0;
    int i = 0;
    ID *p1, *p2, *p3, *add;         //add是用来放添加的信息的，p1，p2是用来临时移动的
    p1 = p2 = head;                 //先让它们都等于头指针
    add = (ID *)malloc(sizeof(ID)); //申请动态存储空间
    system("cls");                  //清屏
    while (p1 != NULL)              //这个是把p2移到最后一个结点上去，因为我是从后面插入的，到了后面p1就是为NULL了
    {
        p2 = p1;
        p1 = p1->next;
    }
    printf("请输入添加人的姓名:\n");
    scanf("%s", add->name);
    printf("请输入添加人的电话号码:\n");
    scanf("%s", add->tele);
    printf("请输入添加人的类型:\n");
    scanf("%s", add->style);
    printf("请输入添加人的邮箱:\n");
    scanf("%s", add->mail);
    p3 = head;         //让p3从头开始遍历
    while (p3 != NULL) //当p3不为空时
    {
        if ((strcmp(add->name, p3->name) == 0) && (strcmp(add->tele, p3->tele) == 0))
        {
            free(add);
            printf("你重复输入了，这一条不保存。请按任意键返回主菜单\n");
            i = 1;
            printf("请按任意键返回主菜单\n");
            getchar(); //按下任意键就进入下一条语句的函数
            break;
        }
        if ((strcmp(add->name, p3->name)) && (strcmp(add->tele, p3->tele)) && (p3 == p2)) //一旦到了最后一个结点，并且还没有和他相同的信息的时候
        {
            i = 0;
            break; //跳出第一个循环
        }
        p3 = p3->next;
    }

    if (i == 0)
    {
        add->next = NULL; //指针域赋值为空，方面以后的判断
        if (p1 == head)   //当头结点没有信息的时候
        {
            head = add; //直接给head
        }
        else
        {
            p2->next = add; //最后一个p2结点的next插入add
        }
        total++;
        k++;

        free(p1);
        printf("新添加电话号码成功,是否存盘?(Y/N)\n");
        getchar();                              //吸收回车键
        scanf("%c", &saveflag);                 //输入，存放Y or N
        if (saveflag == 'y' || saveflag == 'Y') //当输入是的时候
        {
            Save(head); //调用保存函数
            total++;
        }
        else
        {
            printf("请在退出系统之前返回主菜单按3进行保存\n");
            printf("请按任意键返回主菜单\n");
            getchar(); //按下任意键就进入下一条语句的函数
        }
    }
    return (head); //return一个已经进行修改的链表的头指针
}

/************************************************

*函数名： Change（修改）
*功能：修改人物信息
*返回值：ID *（结构体指针）

*************************************************/
ID *Change(ID *head)
{
    ID *p1, *p2, *p3;    //定义p1和p2用来在单链表中移动
    char saveflag;       //存放Y or N
    p1 = p2 = p3 = head; //先让它们都等于头指针
    char n[10];          //存放待修改人的姓名
    int i=0;               //作用和删除的一样领导这个函数
    system("cls");       //清屏
    printf("请输入要修改的姓名：\n");
    scanf("%s", n);
    // while (p3 != NULL) //这个while语句的作用是在遍历整个单链表时，当遇到一样的名字时把i赋值，引导下面的工作
    // {
    //     if (strcmp(p3->name, n) == 0) //判断是不是你输入的名字是不是和通讯录中的相等
    //     {
    //         i = 1; //当存在一样的名字时，i=1
    //         break;
    //     }
    //     else
    //     {
    //         i = 0; //不存在一样的名字时，i=1
    //         break;
    //     }
    //     p3 = p3->next; //p3指针向后移
    // }
    if (i == 1) //当i=1时，开始找那个一样名字的结点在哪里
    {
        while (strcmp(p1->name, n) && p1 != NULL) //当遇到一样名字的时候循环结束，那么这时的p1就是那个名字一样的结点
        {
            p2 = p1;       //p2永远在p1的前一个结点
            p1 = p1->next; //p1指针向后移
        }
    }
    if (i == 0) //当i=0时，就是没有这个名字的人，返回主菜单
    {
        printf("对不起，没有找到要删除的通讯名单，请检查你要删除的姓名是否正确\n");
        printf("请按任意键返回主菜单\n");
        getchar(); //按下任意键就进入下一条语句的函数
    }
    if ((i == 1) && (p1 != NULL)) //当在遍历完整个链表以后，存在一样的名字（即i==1），并且p1不为空，说明没有走出这个链表
    {
        printf("你要修改的电话记录为:\n");
        printf("姓名 %s\t电话号码 %s\t类型:%s\t邮箱:%s\n", p1->name, p1->tele, p1->style, p1->mail);
        printf("请输入修改后的号码:\n");
        scanf("%s", p1->tele);
        printf("请输入修改后的类型:\n");
        scanf("%s", p1->style);
        printf("请输入修改后的邮箱:\n");
        scanf("%s", p1->mail);
        printf("该电话记录已修改成功\n");
        printf("通讯人已经新建成功,是否进行保存? (Y/N)\n");
        getchar(); //吸收回车
        scanf("%c", &saveflag);
        if (saveflag == 'y' || saveflag == 'Y') //当输入是的时候
            Save(head);                         //调用保存函数
        else
            printf("请在退出系统之前返回主菜单按3进行保存\n");
        printf("请按任意键返回主菜单\n");
        getchar(); //按下任意键就进入下一条语句的函数
    }

    return (head); //return一个已经进行修改的链表的头指针
}

/************************************************

*函数名： main(主函数)
*功能：无
*返回值：NULL

*************************************************/
int main()
{
    system("stty -icanon");
    ID *head = NULL; //这是这个程序的头，什么功能都是靠这个来进行链接的
    int choice;      //存放用户的选择
    int j = 0;       //这个j是用于功能之间的配合使用
    while (1)
    {
        system("cls"); //清屏
        printf("\n\n");
        printf("\t    # # # # # System Of Communication # # # # #\n");
        printf("\t	  	 1. 建立通讯录\n");
        printf("\t	  	 2. 删除通讯人\n");
        printf("\t	  	 3. 保存通讯录\n");
        printf("\t		 4. 读取通讯录文件  \n");
        printf("\t		 5. 查找通讯人\n");
        printf("\t	  	 6. 添加通讯人\n");
        printf("\t	  	 7. 修改通讯人信息\n");
        printf("\t	  	 8. 退出通讯录系统\n");
        printf("\t\t\t\t\tMade by 元达鹏\n");
        printf("\t    # # # # # # # # # # # # # # # # # # # # # #\n");
        printf("\n\n");
        scanf("%d", &choice); //输入功能
        getchar();            //吸收回车键
        switch (choice)
        {
        case 1:
            head = Create(); //创建
            j = 1;           //让功能7可以进得去
            break;
        case 2:
            head = Delete(head); //删除
            break;
        case 3:
            Save(head); //保存函数
            break;
        case 4:
            head = Read(); //读取文件的函数
            j = 2;         //让功能7可以进得去
            break;
        case 5:
            Search(head); //查找
            break;
        case 6:
            if ((j == 1) || (j == 2)) //当你进入过创建或者读取之后才可以进入添加
            {
                head = Add(head); //添加
            }
            else
            {
                printf("在你添加通讯人的时候请先创建通讯录或者读取通讯录文件\n\n");
                printf("请按任意键返回主菜单\n");
                getchar(); //按下任意键就进入下一条语句的函数
            }
            break;
        case 7:
            if ((j == 1) || (j == 2)) //当你进入过创建或者读取之后才可以进入添加
            {
                head = Change(head); //修改
            }
            else
            {
                printf("在你删除通讯人的时候请先创建通讯录或者读取通讯录文件\n\n");
                printf("请按任意键返回主菜单\n");
                getchar(); //按下任意键就进入下一条语句的函数
            }
            break;
        case 8:
            exit(0); //退出
            break;
        default:
            printf("你输入错了吧，请你重新输入\n");
        }
    }
    return 0;
}