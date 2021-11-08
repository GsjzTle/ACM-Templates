1. 以任意一点 $P$ 作为根节点，通过 $DFS$ 寻找离它最远的点 $Q$
2. 再次从点 $Q$ 作为根节点，通过 $DFS$ 寻找离它最远的 $W$
3. 直径即为 $dep[W]$

```text
int dep[N] , pos , ma;
void dfs(int u , int far)
{
	dep[u] = dep[far] + 1;
	if(dep[u] > ma) ma = dep[u] , pos = u;
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far) continue ;
		dfs(v , u);
	}
}
int calc()
{
	ma = 0;
	dfs(1 , 0); 
	//memset(dep , 0 , sizeof(dep)); 
	dfs(pos , 0);
	return ma - 1;
}
```

