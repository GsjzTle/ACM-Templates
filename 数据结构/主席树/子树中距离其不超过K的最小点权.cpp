#include<bits/stdc++.h>
using namespace std;
const int inf (0x3f3f3f3f);
const int N = 3e5 + 10;
struct Edge{
	int nex , to;
}edge[N << 1];
int head[N] , TOT;
void add_edge(int u , int v)
{
	edge[++ TOT].nex = head[u] ;
	edge[TOT].to = v;
	head[u] = TOT;
}
struct CTree{
	int l , r , mi = inf;
}tree[N << 5];
int root[N] , Ctot;
void push_up(int rt)
{
	tree[rt].mi = min(tree[tree[rt].l].mi , tree[tree[rt].r].mi);
}
void update(int l , int r , int pre , int &now , int pos , int val)
{
	tree[++ Ctot] = tree[pre];
	now = Ctot;
	if(l == r)
	{
		tree[now].mi = val;
		return ;
	}
	int mid = l + r >> 1;
	if(pos <= mid) update(l , mid , tree[pre].l , tree[now].l , pos , val);
	else update(mid + 1 , r , tree[pre].r , tree[now].r , pos , val);
	push_up(now);
}
int query(int l , int r , int rt , int L , int R)
{
	if(L <= l && r <= R) return tree[rt].mi;
	int mid = l + r >> 1 , mi = inf;
	if(L <= mid) mi = min(mi , query(l , mid , tree[rt].l , L , R));
	if(R >  mid) mi = min(mi , query(mid + 1 , r , tree[rt].r , L , R));
	return mi;
}
int n , r , m , last , x , k , ma;
int tot , a[N] , dfl[N] , dfr[N] , dep[N] , vis[N] , id[N];
void dfs(int u , int far)
{
	dep[u] = dep[far] + 1;
	ma = max(ma , dep[u]);
	dfl[u] = ++ tot;
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far) continue ;
		dfs(v , u);
	}
	dfr[u] = tot;
}
void bfs(int st)
{
	int cnt = 0;
	queue<int>que;
	que.push(st);
	vis[st] = 1;
	update(1 , n , root[0] , root[++ cnt] , dfl[st] , a[st]);
	id[1] = cnt;
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int i = head[u] ; i ; i = edge[i].nex)
		{
			int v = edge[i].to;
			if(vis[v]) continue ;
			vis[v] = 1 , que.push(v);
			update(1 , n , root[cnt] , root[cnt + 1] , dfl[v] , a[v]);
			id[dep[v]] = ++ cnt;
		}
	}
}
vector<int>vec;
int get(int x){
	return lower_bound(all(vec) , x) - vec.begin() + 1;
}
signed main()
{
	cin >> n >> r;
	rep(i , 1 , n) cin >> a[i] , vec.pb(a[i]);
	sort(all(vec));
	vec.erase(unique(all(vec)) , vec.end());
	rep(i , 1 , n) a[i] = get(a[i]);
	rep(i , 2 , n)
	{
		int u , v;
		cin >> u >> v;
		add_edge(u , v) , add_edge(v , u);
	}
	dfs(r , 0) , bfs(r);
	cin >> m;
	rep(i , 1 , m)
	{
		int p , q;
		cin >> p >> q;
		x = (p + last) % n + 1;
		k = (q + last) % n;
		int ha = query(1 , n , root[id[min(dep[x] + k , ma)]] , dfl[x] , dfr[x]) - 1;
		if(ha < 0) while(1);
		last = vec[ha];
		cout << last << '\n';	
	}
	return 0;
}
