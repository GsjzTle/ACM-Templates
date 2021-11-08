$1 \leq N \leq 2 \times 10^9$

```text
int prime[]={2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 , 41 , 43 , 47 , 53};
int n , ma , res;
void dfs(int pos , int cnt , int now , int up)
{
	if(now > n || pos > 15) return ;
	if(cnt > ma) ma = cnt , res = now;
	else if(cnt == ma) res = min(res , now);
	rep(i , 1 , up)
	{
		if(now * prime[pos] > n) break ;
		now = now * prime[pos];
		dfs(pos + 1 , cnt * (i + 1) , now , i);
	}
}
signed main()
{
	cin >> n;
	dfs(0 , 1 , 1 , 32);
	cout << res << '\n';
	return 0;
}
```

