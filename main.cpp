#include <iostream>
#include <cstdio>
#include <deque>
#include <queue>        //ʹ�������ȶ������䵱��
#include <cstring>
#include <climits>

using namespace std;
const long long INF = 1000000000;       //��ʾ�ޣ��������㲻����
const int MAX_N = 3100;                 //���㼯���ֵ

class edge                  //�������
{
public:
    int to;                 //�յ�
    long long cost;         //Ȩֵ

    edge()                  //���췽��
    {
    }

    edge(int _to, long long _cost)      //�յ㼰��ߵ�Ȩֵ
    {
        to = _to;
        cost = _cost;
    }

    //���� ��<�� ����������൱�ڶ�����һ���������磬a<b�����ȷֱ���a,b�������ٽ���"<"�ıȽϣ����շ��رȽϽ��
    //�˴�ͬ��������"<"�������ʹ���ܹ���edge�������бȽϣ���ȽϽ������cost>e.cost�ıȽ�ֵ��1��0��
    bool operator<(const edge &e) const
    {
        return cost > e.cost;
    }
};

class dequeGraph                   //����ͼ��˫�˶�������  double-ended queue
{
public:
    deque<edge> vertex[MAX_N];     //����Ϊedge�Ķ��㼯��
    int v;

    dequeGraph(int _v)             //����dequeGraph����
    {
        v = _v;
    }

    void insert(int from, int to, long long cost)       //������뺯����������㣬�յ㣬Ȩֵ��������
    {
        vertex[from].push_back(edge(to, cost));      //�ڶ�β���edge
    }

//    void copy(dequeGraph *graph)
//    {
//        for (int i = 1; i <= v; ++i)
//        {
//            graph->vertex[i] = vertex[i];
//        }
//    }
};

//����prim���������� ͼ��Ȩֵ��·����������������ʼ���ɵ� �������
void prim(dequeGraph *graph, long long dis[], int path[], int n, int s)
{
    bool mark[MAX_N];           //���ڱ�������������еĶ���
    priority_queue<edge> q;     //ʹ��STL�е����ȶ��У�ʵ����С������(���ѣ����ڵ�<�ӽڵ�)
    memset(dis, 0, sizeof(dis));    //memset��memory set���Ƚ�dis����ȫ��ʼ��Ϊ0
    for (int i = 1; i <= n; ++i)                 //�Ƚ�n�������Ӧ��Ȩֵ��ʼ��Ϊ��
    {
        dis[i] = INF;       //ȫ��ʼ��Ϊ���ֵ
    }
    memset(path, 0, sizeof(path));      //��ʼ��·��ֵΪ0
    memset(mark, 0, sizeof(mark));      //��ʼ���������Ϊ0
    dis[s] = 0;             //��ʼ���ɵ㵽�Լ�ȨֵΪ0
    q.push(edge(s, 0));     //��edgeѹ�����ȶ���
    while (!q.empty())                  //��q��Ϊ��
    {
        while (mark[q.top().to] && !q.empty())      //������յ�δ�������q��Ϊ��
        {
            q.pop();                                //��δ���������С��ֵ����
        }
        if (q.empty())                              //�ӿռ�����
        {
            break;
        }
        int index = q.top().to;                     //��¼�Ѷ���Ӧ���յ�
        mark[index] = true;                         //��Ǹö���
        q.pop();

        //����deque��iterator�������������ڱ���STL����
        // ���ﹹ��һ����Ϊit�ĵ����������ڱ���deque<edge>������it��ʼ��Ϊ�ոձ������������Ķ��㣬�����������Ĺ�����
        for (deque<edge>::iterator it = graph->vertex[index].begin(); it != graph->vertex[index].end(); it++)
        {
            if (it->cost < dis[it->to] && !mark[it->to])        //�����������Ȩֵ�ȵ�ǰȨֵ���ڵ�С�Ҹö���δ�����
            {
                dis[it->to] = it->cost;                         //�滻Ȩֵ
                path[it->to] = index;                           //��¼Ȩֵ��Ӧ��·��
                q.push(edge(it->to, dis[it->to]));  //�ٴ�ѹ����У����ж�����
            }
        }
        if (path[index] != 0)
            printf("\n|%d|-->|%d|\tȨֵΪ:%d4"
                   "0"
                   "6"
                   "3"
                   "4"
                   "6\n", path[index], index,dis[index]);
    }
}

int primMain()
{
    long long dis[MAX_N], sum = 0;      //sum���ڼ�����С��������Ȩֵ��
    int path[MAX_N];
    int n, m;
    printf("������ͼ�Ķ�����:");
    scanf("%d", &n);
    dequeGraph graph = dequeGraph(n);       //������ͼ
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            //�ȿ�����������ͼ��Ҳ������������ͼ
            printf("������Ӷ��� %d �� %d Ȩֵ��0��ʾ�����ڱߣ�: ", i, j);
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
    printf("\n��С��������Ȩֵ��Ϊ��%d", sum);
    return 0;
}

int main()
{
    primMain();
    return 0;
}