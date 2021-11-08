int dep[N] , f[N][30];
void dfs(int u , int far)
{
	dep[u] = dep[far] + 1;
	f[u][0] = far;
	for(int i = 1 ; (1 << i) <= dep[u] ; i ++)	
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far) continue ;		
		dfs(v , u);
 	}
} 
int get_far(int x , int k)
{
	if(!k) return x;
    int t = dep[x] - k;
    per(i , 20 , 0) if(dep[f[x][i]] > t) x = f[x][i];
    return f[x][0];
}
