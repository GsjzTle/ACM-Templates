```
int cnt[N];
void prime_cnt(int n)
{
	for(int i = 2 ; i <= n ; i ++)
	{
		if(cnt[i]) continue ;
		for(int j = i ; j <= n ; j += i) cnt[j] ++ ;
	}
}
```

