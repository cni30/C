#include <iostream>
#include <cstdio>
#include <deque>
#include <queue>        //使用其优先队列来充当堆
#include <cstring>
#include <climits>

using namespace std;
const long long INF = 1000000000;       //表示∞，即两顶点不相连
const int MAX_N = 3100;                 //顶点集最大值

class edge                  //定义边类
{
public:
    int to;                 //终点
    long long cost;         //权值

    edge()                  //构造方法
    {
    }

    edge(int _to, long long _cost)      //终点及其边的权值
    {
        to = _to;
        cost = _cost;
    }

    //重载 “<” 运算符，这相当于定义了一个函数，如，a<b，即先分别传入a,b参数，再进行"<"的比较，最终返回比较结果
    //此处同理，重载了"<"运算符，使其能够对edge方法进行比较，其比较结果即是cost>e.cost的比较值（1或0）
    bool operator<(const edge &e) const
    {
        return cost > e.cost;
    }
};

class dequeGraph                   //定义图的双端队列容器  double-ended queue
{
public:
    deque<edge> vertex[MAX_N];     //类型为edge的顶点集合
    int v;

    dequeGraph(int _v)             //构造dequeGraph方法
    {
        v = _v;
    }

    void insert(int from, int to, long long cost)       //定义插入函数，传入起点，终点，权值三个参数
    {
        vertex[from].push_back(edge(to, cost));      //在队尾添加edge
    }

//    void copy(dequeGraph *graph)
//    {
//        for (int i = 1; i <= v; ++i)
//        {
//            graph->vertex[i] = vertex[i];
//        }
//    }
};

//定义prim函数，传入 图，权值，路径，顶点数量，开始生成点 五个参数
void prim(dequeGraph *graph, long long dis[], int path[], int n, int s)
{
    bool mark[MAX_N];           //用于标记已在生成树中的顶点
    priority_queue<edge> q;     //使用STL中的优先队列，实现最小堆排序(最大堆：父节点<子节点)
    memset(dis, 0, sizeof(dis));    //memset即memory set，先将dis数组全初始化为0
    for (int i = 1; i <= n; ++i)                 //先将n个顶点对应的权值初始化为∞
    {
        dis[i] = INF;       //全初始化为最大值
    }
    memset(path, 0, sizeof(path));      //初始化路径值为0
    memset(mark, 0, sizeof(mark));      //初始化标记数组为0
    dis[s] = 0;             //开始生成点到自己权值为0
    q.push(edge(s, 0));     //将edge压入优先队列
    while (!q.empty())                  //若q不为空
    {
        while (mark[q.top().to] && !q.empty())      //如果该终点未被标记且q不为空
        {
            q.pop();                                //将未被标记且最小的值弹出
        }
        if (q.empty())                              //队空即结束
        {
            break;
        }
        int index = q.top().to;                     //记录堆顶对应的终点
        mark[index] = true;                         //标记该顶点
        q.pop();

        //遍历deque，iterator：迭代器，用于遍历STL容器
        // 这里构建一个名为it的迭代器，用于遍历deque<edge>容器，it初始化为刚刚被纳入生成树的顶点，遍历这个顶点的关联边
        for (deque<edge>::iterator it = graph->vertex[index].begin(); it != graph->vertex[index].end(); it++)
        {
            if (it->cost < dis[it->to] && !mark[it->to])        //如果遍历到的权值比当前权值表内的小且该顶点未被标记
            {
                dis[it->to] = it->cost;                         //替换权值
                path[it->to] = index;                           //记录权值对应的路径
                q.push(edge(it->to, dis[it->to]));  //再次压入堆中，进行堆排序
            }
        }
        if (path[index] != 0)
            printf("\n|%d|-->|%d|\t权值为:%d4"
                   "0"
                   "6"
                   "3"
                   "4"
                   "6\n", path[index], index,dis[index]);
    }
}

int primMain()
{
    long long dis[MAX_N], sum = 0;      //sum用于计算最小生成树的权值和
    int path[MAX_N];
    int n, m;
    printf("请输入图的顶点数:");
    scanf("%d", &n);
    dequeGraph graph = dequeGraph(n);       //构建该图
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            //既可以生成无向图，也可以生成有向图
            printf("请输入从顶点 %d 到 %d 权值（0表示不存在边）: ", i, j);
            scanf("%d", &m);
            if (m)
            {
                graph.insert(i, j, m);
            }
        }
    }
    prim(&graph, dis, path, n, 1);
    for (int i = 1; i <= n; ++i)
    {
        sum += dis[i];
    }
    printf("\n最小生成树的权值和为：%d", sum);
    return 0;
}

int main()
{
    primMain();
    return 0;
}