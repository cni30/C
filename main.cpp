#include <iostream>

using namespace std;

const int N = 10;
int n;
char q[N][N];
bool col[N], dg[N], udg[N];  //���ڼ�¼��λ���Ƿ��Ѿ���ʹ�ù�

void dfs(int u)
{
    if (n == u)        //�������һ��ʱ
    {
        for (int i = 0; i < n; i++)
            puts(q[i]);
        puts("");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (!col[i] && !dg[i + u] && !udg[i - u + n])     //���������û��ʹ�ù�
        {
            q[u][i] = 'Q';
            //��¼һ�¸�ֵ����,y=x+b �� y=-x+b�����ýؾ�b�����±꣬����Ψһӳ���ϵ���У�ͬһ�ؾ����ͬһ���Խ���
            col[i] = dg[i + u] = udg[i - u + n] = true;
            dfs(u + 1);     //�ݹ����һ��
            col[i] = dg[i + u] = udg[i - u + n] = false;      //�ݹ���������ݣ���ԭ�ֳ�
            q[u][i] = '.';                                    //��ԭ�ֳ�
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            q[i][j] = '.';            //�Ȱ�����ȫ��ʼ��Ϊ ��.��


    dfs(0);

    return 0;
}