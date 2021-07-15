## 题目链接

[点我跳转](https://atcoder.jp/contests/abc192/tasks/abc192_f) 

## 题目大意

>给定 $N$ 个物品和一个 $X$ ，第 $i$ 个物品的重量为 $ai$，你可以从中选择任意个物品(不能不选)
>
>假定选择了 $S$ 个物品，物品的总重量为 $V$
>
>那么再满足 $(X - V) \% S = 0$ 的前提下还需要支付 $(X - V) / S$ 的 $money$
>
>问最少需要支付多少 $money$

## 解题思路

>**当 $S$ 一定时**
>
>+ 为满足 $(X - V) \% S = 0$，则 $V$ 需满足 $V = X \% S$
>
>+ 为了使支付的 $money$ 最少, 则 $V$ 要尽可能大
>
>于是可以枚举 $S$
>
>并定义 $dp[i][j][k]$ 表示从前 $i$  个物品中选择了 $j$ 个物品使得总重量最大，且这 $j$ 个物品的总重量 $\% S = k$  
>
>那么对于每个物品只有两种状态 ： 选 $or$ 不选
>
>于是不难得到 ：
>
>>$dp[i][j][k] = dp[i - 1][j][k]$
>>
>>$dp[i][j][k] = dp[i - 1][j - 1][(k - a[i] % S + S) % S] + a[i]$
>
>最后取最小的 $(X - dp[N][S][X \% S]) / S$ 即可

## AC_Code

```cpp
#include<bits/stdc++.h>

#define rep(i , a , b) for(int i = a ; i <= b ; i ++)

#define int long long

using namespace std;

const int N = 1e2 + 10;

int a[N] , dp[N][N][N];

signed main()
{
	int n , x , mi = 1e18;
	
	cin >> n >> x;

	rep(i , 1 , n) cin >> a[i];
	
	rep(S , 1 , n)
	{
		memset(dp , -1 , sizeof(dp));
		
		dp[0][0][0] = 0;
		
		rep(i , 1 , n) rep(j , 0 , S) rep(k , 0 , S - 1)
		{
			dp[i][j][k] = dp[i - 1][j][k];
				
			if(j > 0 && ~dp[i - 1][j - 1][(k - a[i] % S + S) % S]) 
			
			dp[i][j][k] = max(dp[i][j][k] , dp[i - 1][j - 1][(k - a[i] % S + S) % S] + a[i]);
			
		}
		
		int res = dp[n][S][x % S];
		
		if(~res) mi = min(mi , (x - dp[n][S][x % S]) / S);
	}
	
	cout << mi << '\n';
	
	return 0;
} 
```