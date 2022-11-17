#include <iostream>

using namespace std;

const int N = 10;
int n;
char q[N][N];
bool col[N], dg[N], udg[N];  //用于记录该位置是否已经被使用过

void dfs(int u)
{
    if (n == u)        //到了最后一层时
    {
        for (int i = 0; i < n; i++)
            puts(q[i]);
        puts("");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (!col[i] && !dg[i + u] && !udg[i - u + n])     //如果该数字没被使用过
        {
            q[u][i] = 'Q';
            //记录一下该值已用,y=x+b 和 y=-x+b，利用截距b来做下标，保持唯一映射关系就行，同一截距就是同一条对角线
            col[i] = dg[i + u] = udg[i - u + n] = true;
            dfs(u + 1);     //递归进下一层
            col[i] = dg[i + u] = udg[i - u + n] = false;      //递归结束，回溯，还原现场
            q[u][i] = '.';                                    //还原现场
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            q[i][j] = '.';            //先把数组全初始化为 ‘.’


    dfs(0);

    return 0;
}