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
	dfs(1 , 0) , memset(dep , 0 , sizeof(dep)) , dfs(pos , 0);
	return ma - 1;
}

