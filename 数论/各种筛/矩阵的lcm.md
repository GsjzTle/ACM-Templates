$A_{i,j}=lcm(i,j)$，$O(NM)$

```text
for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= m ; j ++)
if(!a[i][j])
{
	for(int k = 1 ; i * k <= n && j * k <= m ; k ++) 
		a[i * k][j * k] = i * k * j;
}
```

