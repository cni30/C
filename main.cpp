#include <iostream>

using namespace std;

const int N = 10;
int n;
int path[N];
int st[N];  //���ڼ�¼�������Ƿ��Ѿ���ʹ�ù�

void dfs(int u)
{
    if (n == u)        //�������һ��ʱ
    {
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        puts("");
        return;
    }
    for (int i = 1; i <= n; i++)    //ö�ٳ�ÿ�����
    {
        if (!st[i])     //���������û��ʹ�ù�
        {
            path[u] = i;
            st[i] = true;      //��¼һ�¸�ֵ����
            dfs(u + 1);     //�ݹ����һ��
            path[u]=0;         //��ӭ�ֳ��������п��ޣ���Ϊ��һ�λ��ǻ��path[u]�ȸ�ֵ�������ͻḲ��
            st[i] = false;     //�ݹ���������ݣ���ԭ�ֳ�
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0);

    return 0;
}