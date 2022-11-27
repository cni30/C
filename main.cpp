#include <iostream>
#include <cstdio>
#include <deque>
#include <queue>        //ʹ�������ȶ������䵱��
#include <cstring>
#include <climits>

using namespace std;
const long long INF = 1000000000;       //��ʾ�ޣ��������㲻����
const int MAX_N = 3100;                 //���㼯���ֵ

class edge
{
public:
    int to;                 //�յ�
    long long cost;         //Ȩֵ

    edge()
    {
    }

    edge(int _to, long long _cost)      //�յ㼰��ߵ�Ȩֵ
    {
        to = _to;
        cost = _cost;
    }

    bool operator<(const edge &e) const
    {
        return cost > e.cost;
    }
};

class dequeGraph
{
public:
    deque<edge> vertex[MAX_N];
    int v;

    dequeGraph(int _v)
    {
        v = _v;
    }

    void insert(int from, int to, long long cost)
    {
        vertex[from].push_back(edge(to, cost));
    }

    void copy(dequeGraph *graph)
    {
        for (int i = 1; i <= v; ++i)
        {
            graph->vertex[i] = vertex[i];
        }
    }
};

void prim(dequeGraph *graph, long long dis[], int path[], int n, int s)
{
    bool mark[MAX_N];
    priority_queue<edge> q;
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= n; ++i)
    {
        dis[i] = INF;       //ȫ��ʼ��Ϊ���ֵ
    }
    memset(path, 0, sizeof(path));
    memset(mark, 0, sizeof(mark));
    dis[s] = 0;
    q.push(edge(s, 0));
    while (!q.empty())
    {
        while (mark[q.top().to] && !q.empty())
        {
            q.pop();
        }
        if (q.empty())
        {
            break;
        }
        int index = q.top().to;
        mark[index] = true;
        q.pop();
        for (deque<edge>::iterator it = graph->vertex[index].begin(); it != graph->vertex[index].end(); it++)
        {
            if (it->cost < dis[it->to] && !mark[it->to])
            {
                dis[it->to] = it->cost;
                path[it->to] = index;
                q.push(edge(it->to, dis[it->to]));
            }
        }
    }
}

int primMain()
{
    long long dis[MAX_N], sum = 0;
    int path[MAX_N];
    int n, m;
    printf("������ͼ�Ķ�����:\n");
    scanf("%d", &n);
    dequeGraph graph = dequeGraph(n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            printf("������Ӷ��� %d �� %d Ȩֵ:", i, j);
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
    printf("%d", sum);
    return 0;
}

int main()
{
    primMain();
    return 0;
}