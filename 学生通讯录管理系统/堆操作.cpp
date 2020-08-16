#include <cstdio>
#include <iostream>
#define inf 0x3f3f3f3f
using namespace std;

const int Max_e = 1000;
const int Max_v = 30;
int f[Max_v + 1], v, e;
int edge[Max_v][Max_v], book[Max_v]; //
//book:标记点是否加入到生成树中,全局变量初始为0(未加入) edge:邻接矩阵

struct A
{
    int distance; //distance:各个顶点到"生成树"的距离
    int index;    //记录生成树中的点(起点)
} dis[Max_v];

struct B
{
    int mmin1;
    int index;
} mmin;

struct E
{
    int st;
    int et;
    int w;
} Edge[Max_e];

/**打印信息*/
void PrintEdgeMes()
{
    cout << "---------------------------" << endl;
    cout << "权值\t起点\t终点\t" << endl;
    for (int i = 1; i <= e; i++)
    {
        cout << Edge[i].w << "\t" << Edge[i].st << "\t" << Edge[i].et << "\t" << endl;
    }
    cout << "---------------------------" << endl;
    cout << endl;
}

/**交换两条边的信息*/
void Swap(int i, int j)
{
    int st, et, w;
    st = Edge[i].st;
    Edge[i].st = Edge[j].st;
    Edge[j].st = st;
    et = Edge[i].et;
    Edge[i].et = Edge[j].et;
    Edge[j].et = et;
    w = Edge[i].w;
    Edge[i].w = Edge[j].w;
    Edge[j].w = w;
}
/**筛选法调整堆*/
void HeapAdjust(int s, int m)
{
    //s根结点,m序列长度
    Edge[0] = Edge[s]; //保存根结点信息
    for (int i = 2 * s; i <= m; i *= 2)
    { //沿着权值较大的孩子结点向下筛选
        if (i < m && Edge[i].w < Edge[i + 1].w)
            i++;
        if (Edge[0].w >= Edge[i].w)
            break; //根结点的权值大于两个孩子,0号位置的信息应该在s位置上
        Edge[s] = Edge[i];
        s = i; //否则0号位的信息应该在i,更新根结点,继续找他的左右堆,直到找到叶子结点,一次调整完毕
    }
    Edge[s] = Edge[0];
}

/**建立大根堆*/
void CreatHeap()
{
    int n = e;
    //所有大于n/2的位置上都是叶子结点,我们从叶子最后一个非叶子结点筛选
    for (int i = n / 2; i > 0; i--)
    {
        HeapAdjust(i, e); //不断的调整堆
    }
}

/**对边进行排序(堆排序)*/
void HeapSort()
{
    CreatHeap(); //把无序序列建成大根堆
    for (int i = e; i > 1; i--)
    {
        //1:堆顶元素的位置,i:未排序的最后一个
        Swap(1, i);           //将堆顶元素与没有排序(1-i)的的最后一个记录交换
        HeapAdjust(1, i - 1); //除了堆顶信息,剩下的继续调整为大根堆
    }
}

/**找到第一个标记*/
int getf(int n)
{
    if (f[n] == n)
        return n;
    else
    {
        f[n] = getf(f[n]); //在找到最终的那个点之前遇到的点都"属于最终的那个点"
        return f[n];
    }
}

/**判断边的顶点是否属于一个连通分量*/
int merge(int st, int et)
{
    int t1, t2;
    t1 = getf(st);
    t2 = getf(et);
    if (t1 != t2)
    {               //t1是否是一个连通分量
        f[t1] = t2; //标记值都靠近左边的值
        return 1;
    }
    return 0;
}

/* -------Kruskal算法简介(适用于稀疏图)-------
   按照边的权值大小排序,每次从剩余的边中选择权
   值较小且边的两个顶点不在同一个集合内的边加
   入到生成树中,直到加入n-1条边为止 */
void MiniSpanTree_Kruskal()
{
    //对边进行排序(堆排序)
    HeapSort();
    int count = 0;
    //打印对边排序的结果
    cout << endl
         << "对所有边排序(堆排序)的结果为:" << endl;
    PrintEdgeMes();
    for (int i = 1; i <= v; i++)
        f[i] = i; //各顶点自成一个连通分量
    //枚举边
    cout << "Kruskal算法选用的边极其权值为:" << endl;
    cout << "-----------------------------------" << endl;
    cout << "起点\t终点\t权值" << endl;
    for (int i = 1; i <= e; i++)
    {
        if (merge(Edge[i].st, Edge[i].et))
        {
            count++;
            //检查这两个点是否在同一个集合中,如果不在返回1,就选用这条边
            cout << Edge[i].st << "\t" << Edge[i].et << "\t" << Edge[i].w << "\t" << endl;
            if (count == v - 1) //选了n-1条边时退出循环
                break;
        }
    }
    cout << "-----------------------------------" << endl;
}

/*-------Prim算法简介(适用于稠密图)-------
  我们从1号顶点开始,找到与选过的点相连接的
  最短边,并且这条边可以连接到没有被选中的
  点.这样一直重复n-1次即可找到最小生成树
*/
int main()
{
    cout << "--------------Kruskal算法--------------" << endl
         << endl;
    cout << "请输入顶点数和边数:";
    cin >> v >> e;
    cout << "请依次输入e条边及其权值:" << endl;
    for (int i = 1; i <= e; i++)
        cin >> Edge[i].st >> Edge[i].et >> Edge[i].w;
    MiniSpanTree_Kruskal();
    cout << endl
         << "---------------------------------------" << endl;
    cout << ">>Enter键进入Prim算法" << endl;
    system("pause");
    system("cls");
    int count;
    cout << "-----------------Prim算法-----------------" << endl
         << endl;
    count = 0; //加入到生成树中的顶点数置为0
    cout << "请输入顶点数和边数:";
    cin >> v >> e;
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            if (i == j)
                edge[i][j] = 0;
            else
                edge[i][j] = inf;
        }
    }

    int st, et, w, j;
    cout << "请依次输入e条边及其权值:" << endl;
    for (int i = 1; i <= e; i++)
    {
        cin >> st >> et >> w;
        edge[st][et] = w; //无向图
        edge[et][st] = w;
    }
    //先把一号顶点加入到生成树中
    for (int i = 1; i <= v; i++)
    {
        dis[i].distance = edge[1][i];
        dis[i].index = 1; //目前记录的最短路径都是从1出发的
    }

    book[1] = 1;
    count++;
    cout << endl
         << "Prim算法选用的边及其权值为:" << endl;
    cout << "-----------------------------------" << endl;
    cout << "起点\t终点\t权值" << endl;
    while (count < v)
    {
        mmin.mmin1 = inf; //最短的边
        for (int i = 1; i <= v; i++)
        {
            if (book[i] == 0 && dis[i].distance < mmin.mmin1)
            {
                mmin.mmin1 = dis[i].distance;
                j = i; //新加入的顶点
                mmin.index = dis[i].index;
            }
        }
        cout << mmin.index << "\t" << j << "\t" << mmin.mmin1 << endl;
        book[j] = 1;
        count++;
        for (int k = 1; k <= v; k++)
        { //枚举j连接的顶点,更新各顶点到生成树之间的距离
            if (book[k] == 0 && dis[k].distance > edge[j][k])
            {
                dis[k].distance = edge[j][k];
                dis[k].index = j;
                //如果这个点不在生成树中,而且有更短的距离
            }
        }
    }
    cout << "-----------------------------------" << endl
         << endl;
    cout << "-------------------------------------------" << endl;
    return 0;
}
