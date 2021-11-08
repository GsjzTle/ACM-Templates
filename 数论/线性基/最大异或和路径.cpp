#include<bits/stdc++.h>
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
#define ll long long
using namespace std;
struct Linear_Basis
{
	ll b[63], nb[63], tot; //b为线性基 , nb用来求第 K 小异或值 , tot为 nb 元素个数
	bool zero = false;  // 判断是否存在 0 
	void Init() //初始化
	{
		tot = 0;
		zero = false;
		memset(b, 0, sizeof(b));
		memset(nb, 0, sizeof(nb));
	}
	void Ins(ll x) //插入
	{
		for(int i = 62; i >= 0; i--)
		{
			if(x & (1ll << i))
			{
				if(!b[i])
				{
					b[i] = x;
					return;
				}
				x ^= b[i];
			}
		}
		// x 插入失败 
		zero = true;
		return;
	}
	bool Fin(ll x) //验证存在性
	{
		if(x == 0 && b[0]) return 1;
		for(int i = 62; i >= 1; i--)
		{
			int j = i - 1;
			if(x & (1 << j))
			{
				x ^= b[i];
				if(!x) return 1;
			}
		}
		return 0;
	}
	ll Max() //求最大值
	{
		ll res = 0;
		for(int i = 62; i >= 0; i--)
		{
			res = max(res, res ^ b[i]);
		}
		return res;
	}
	ll Min() //求最小值
	{
		if(zero) return 0;
		for(int i = 0; i <= 62; i++)
		{
			if(b[i]) return b[i];
		}
	}
	ll Query_Max(ll x) // 异或 x 可得到的最大值 
	{  
        ll res = x;
        for(int i = 62 ; i >= 0 ; i --){
            res = max(res , res ^ b[i]);
        }
        return res;
    }
    ll Query_Min(ll x) // 异或 x 可得到的最小值 
	{ 
        ll res = x;
        for(int i = 0 ; i <= 62 ; i ++){
            if(b[i]) res ^= b[i];
        }
        return res;
    }
	void Rebuild()
	{
		for(int i = 62; i >= 0; i--)
		{
			if(b[i] == 0) continue;
			for(int j = i - 1; j >= 0; j--)
			{
				if(b[j] == 0) continue;
				if(b[i] & (1ll << j)) b[i] ^= b[j];
			}
		}
		for(int i = 0; i <= 62; i++)
		{
			if(b[i]) nb[tot++] = b[i];
		}
	}
	ll Kth_Max(ll k) //第K大
	{
		if(zero) k--;
		ll res = 0;
		if(k == 0) return 0;
		if(k >= (1ll << tot)) return -1;
		for(int i = 62; i >= 0; i--)
		{
			if(k & (1ll << i)) res ^= nb[i];
		}
		return res;
	}
} LB;
const int N = 1e5 + 10;
struct Edge{
	int nex , to;
	ll w;
}edge[N << 1];
int head[N] , TOT;
void add_edge(int u , int v , ll w)
{
	edge[++ TOT].nex = head[u];
	edge[TOT].to = v;
	edge[TOT].w = w;
	head[u] = TOT;
}
int n , m , vis[N];
ll dis[N];
void dfs(int u , int far)
{
	vis[u] = 1;
	for(int i = head[u] ; i ; i = edge[i].nex)
	{
		int v = edge[i].to ;
		ll w = edge[i].w;
		if(v == far) continue ;
		if(vis[v]) 
		{
			LB.Ins(dis[v] ^ dis[u] ^ w);
			continue ;
		}
		dis[v] = dis[u] ^ w;
		dfs(v , u);
	}
}
signed main()
{
	LB.Init();
	cin >> n >> m;
	rep(i , 1 , m)
	{
		int u , v;
		ll w;
		cin >> u >> v >> w;
		add_edge(u , v , w) , add_edge(v , u , w);
	}
	dfs(1 , 0);
	cout << LB.Query_Max(dis[n]) << '\n';
	return 0;
}
