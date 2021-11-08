const int N = 5e5 + 10;
struct Edge{
	int nex , to;
}edge[N << 1];
int dep[N] , f[N][30] , head[N] , tot , ans[N] , siz[N];
void add_edge(int u , int v)
{
	edge[++ tot].nex = head[u];
	edge[tot].to = v;
	head[u] = tot;
}
void dfs(int u , int far)
{
	siz[u] = 1;
	dep[u] = dep[far] + 1;
	f[u][0] = far;
	for(int i = 1 ; (1 << i) <= dep[u] ; i ++)	
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far) continue ;		
		dfs(v , u);
		siz[u] += siz[v];
	}
} 
int lca(int x , int y)
{
	if(dep[x] < dep[y]) swap(x , y);
	per(i , 20 , 0)
	{
		if(dep[f[x][i]] >= dep[y]) x = f[x][i];
		if(x == y) return x;
	}
	per(i , 20 , 0)
		if(f[x][i] != f[y][i])
			x = f[x][i] , y = f[y][i];
	return f[x][0];
}
