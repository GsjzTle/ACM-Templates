const int N = 5e5 + 10;
int g[N], dep[N], f[N][21], hson[N], high[N], top[N];
vector<int> G[N], U[N], V[N];
void dfs1(int u , int far)
{
	high[u] = dep[u] = dep[far] + 1;
	for (auto v : G[u])
	{
		if(v == far) continue ;
		f[v][0] = u;
		for (int i = 0; f[v][i]; i++) f[v][i + 1] = f[f[v][i]][i];
		dfs1(v , u);
		if (high[v] > high[u]) high[u] = high[v], hson[u] = v;
	}
}
void dfs2(int u, int tp , int far)
{
	top[u] = tp;
	if (u == tp)
	{
		for (int i = 0, o = u; i <= high[u] - dep[u] ; i ++)
			U[u].push_back(o), o = f[o][0];
		for (int i = 0, o = u; i <= high[u] - dep[u] ; i ++)
			V[u].push_back(o), o = hson[o];
	}
	if (hson[u]) dfs2(hson[u], tp , u);
	for (auto v : G[u]) if (v != hson[u] && v != far) dfs2(v, v , u);
}
int get_far(int u, int k)
{
	if (!k) return u;
	u = f[u][g[k]], k -= 1 << g[k], k -= dep[u] - dep[top[u]], u = top[u];
	return k >= 0 ? U[u][k] : V[u][-k];
}
void init(int n)
{
	g[0] = -1;
	for(int i = 1 ; i <= n ; i ++) g[i] = g[i >> 1] + 1;
}
