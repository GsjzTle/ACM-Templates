**题目大意**

> 给定一棵包含 $n$ 个节点的树，每个节点有个权值 $a_i$ 
>
> 求$∑_{i=1}^n∑_{j=i+1}^n[a_i⊕a_j=a_{lca(i,j)}](i⊕j).$

**解题思路**

>题目保证了 $a_i ≠ 0$ ，所以不存在 $a_u⊕a_v = a_u$，即满足条件的$a_u ⊕ a_v = a_{lca(u,v)}$ 的 $u , v$ 一定在不同分支
>
>这点极大的简单化了本问题
>
>于是在以 $rt$ 为根的子树中，对于节点 $u$ ，满足条件的点的异或值为 $a_u ⊕ a_{rt}$
>
>而 $u$ 对答案产生的贡献只和 $u$ 在二进制下每一位的数值有关系
>
>于是我们可以定义 $f_{ijk}$ 表示异或值为 $i$ 的数 , 它们在二进制下第 $j$ 位为 $k$ 的个数
>
>那么对于 $u$ , 它的贡献可以这么算
>
>```text
>int x = a[u] ^ a[rt];
>if(x <= 1000000) // a[i] <= 1e6
>{
>	for(int i = 17 ; i >= 0 ; i --)
>	{
>		int k = u >> i & 1;
>		ans += (1LL << i) * f[x][i][k ^ 1]; 
>	}
>}
>```
>
>到这本题就差不多结束了
>
>别忘了一个分支内的任意节点不能相互影响，所以需要先对一个分支统计完贡献后，再添加它的信息

```text
const int N = 1e5 + 10 , M = 1e6 + 10;
struct Edge{
	int nex , to;
}edge[N << 2];
int head[N] , TOT;
void add_edge(int u , int v)
{
	edge[++ TOT].nex = head[u];
	edge[TOT].to = v;
	head[u] = TOT;
}
int dep[N] , sz[N] , hson[N] , HH;
int a[N] , f[M][20][2];
ll ans;
void dfs(int u , int far)
{
	sz[u] = 1;
	dep[u] = dep[far] + 1;
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far) continue ;
		dfs(v , u);
		sz[u] += sz[v];
		if(sz[v] > sz[hson[u]]) hson[u] = v;
	}
}
void change(int u , int far , int val)
{
	for(int i = 17 ; i >= 0 ; i --) f[a[u]][i][u >> i & 1] += val;
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far || v == HH) continue ;
		change(v , u , val); 
	}
} 
void calc(int u , int far , int rt)
{
	int x = a[u] ^ a[rt];
	if(x <= 1000000)
	{
		for(int i = 17 ; i >= 0 ; i --)
		{
			int k = u >> i & 1;
			ans += (1LL << i) * f[x][i][k ^ 1]; 
		}
	}
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far || v == HH) continue ;
		calc(v , u , rt);
	}
}
void dsu(int u , int far , int op)
{
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to;
		if(v == far || v == hson[u]) continue ;
		dsu(v , u , 0);
	}
	if(hson[u]) dsu(hson[u] , u , 1) , HH = hson[u];
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to ;
		if(v == far || v == HH) continue ;
		calc(v , u , u) , change(v , u , 1);	
	} 
	HH = 0;
	for(int i = 17 ; i >= 0 ; i --) f[a[u]][i][(u >> i) & 1] ++ ;
	if(!op) change(u , far , -1);	
}
signed main()
{
	ios::sync_with_stdio(false);
	int n ;
	cin >> n;
	rep(i , 1 , n) cin >> a[i];
	rep(i , 2 , n)
	{
		int u , v;
		cin >> u >> v;
		add_edge(u , v) , add_edge(v , u);	
	} 
	dfs(1 , 0);
	dsu(1 , 0 , 0);
	cout << ans << '\n';
	return 0;
}
```