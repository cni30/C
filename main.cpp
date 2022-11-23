#include <iostream>

using namespace std;

const int N = 10;
int n;
int path[N];
int st[N];  //用于记录该数字是否已经被使用过

void dfs(int u)
{
    if (n == u)        //到了最后一层时
    {
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        puts("");
        return;
    }
    for (int i = 1; i <= n; i++)    //枚举出每种情况
    {
        if (!st[i])     //如果该数字没被使用过
        {
            path[u] = i;
            st[i] = true;      //记录一下该值已用
            dfs(u + 1);     //递归进下一层
            path[u]=0;         //欢迎现场，但可有可无，因为下一次还是会给path[u]先赋值，本来就会覆盖
            st[i] = false;     //递归结束，回溯，还原现场
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0);

    return 0;
}