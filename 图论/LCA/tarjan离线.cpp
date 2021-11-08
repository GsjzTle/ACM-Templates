const int N = 5e5 + 10;
int father[N] , vis[N];
vector<int>mat[N];
vector<int>Q[N];
struct pnode{
	int x , y;
	int lca;
}query[N];
void init()
{
	rep(i , 1  ,N)
	father[i] = i , vis[i] = 0;
}
int find(int x)
{
	if(father[x] == x)	return x;
	else	return father[x] = find(father[x]);
}
void tarjan(int u)
{
	vis[u] = 1;
	for(auto it : Q[u])
	{
		if(query[it].x == u)
		{
			if(vis[query[it].x])
			query[it].lca = find(query[it].y);
		}
		else 
		{
			if(vis[query[it].y])
			query[it].lca = find(query[it].x);
		}
	}
	for(auto v : mat[u])
	{
		if(vis[v])
		continue;
		tarjan(v);
		father[v] = u;
		
	}
}
signed main()
{
	init();
	int n , m , s;
	cin >> n >> m >> s;
	rep(i , 1 , n - 1)
	{
		int x , y ;
		cin >> x >> y;
		mat[x].pb(y) , mat[y].pb(x);
	}
	rep(i , 1 , m)
	{
		cin >> query[i].x >> query[i].y;
		Q[query[i].x].pb(i) , Q[query[i].y].pb(i);
	} 
	tarjan(s);
	rep(i , 1 , m)
	cout << query[i].lca << '\n';
	return 0;
}
