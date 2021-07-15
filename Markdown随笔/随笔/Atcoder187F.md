## 题目链接

[点我跳转](https://atcoder.jp/contests/abc187/tasks/abc187_f) 

## 题目大意

> 给你一张完全图，你可以删除任意数量的边
>
> 要求删除完后剩余的所有子图必须是完全图
>
> 问完全子图数量最少是多少

## 解题思路

>定义 $ok[i]$ 表示状态为 $i$ 时所对应的点构成的图是否为完全图 ($1$ 为是 , $0$ 为否)
>
>判断完全图可直接暴力枚举任意两点检查是否有边
>
>定义 $dp[i]$ 表示状态为 $i$ 时所对应的点构成的所有子图都为完全图，且子图数最小
>
>其中 $dp[0] = 0$
>
>那么不难得到当 $ok[j] = 1$ 时
>
> $dp[i] = min(dp[i] , dp[i$ ^$j] + 1)$  , （ $j$ 为 $i$ 的子集 ） 
>
>答案为 $dp[1 << n - 1]$

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1LL << 19 , M = 20;
int n , m , dp[N] , ok[N] , g[M][M];
signed main()
{
	cin >> n >> m;
	for(int i = 1 ; i <= m ; i ++)
	{
		int x , y;
		cin >> x >> y;
		g[x][y] = g[y][x] = 1;
 	}
 	int sum = 1 << n;
	for(int i = 0 ; i < sum ; i ++)
	{
		ok[i] = 1;
		for(int j = 1 ; j <= n ; j ++) if(i >> (j - 1) & 1) 
		{
			for(int k = j + 1 ; k <= n ; k ++) if(i >> (k - 1) & 1)		
			{
				if(!g[j][k]) { ok[i] = 0 ; break ; }		
			}
			if(!ok[i]) break ;
		} 
		dp[i] = 1e9; 
	}
	dp[0] = 0;
	for(int i = 0 ; i < sum ; i ++)
	{
		for(int j = i ; j ; j = (j - 1) & i) if(ok[j]) 
		{
			dp[i] = min(dp[i] , dp[i ^ j] + 1);
		}
	}
	cout << dp[sum - 1] << '\n';
	return 0;
}
```