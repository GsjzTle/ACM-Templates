#include<bits/stdc++.h>
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
using namespace std;
const int N = 1e3 + 10 , M = 5e4 + 10;
struct Edge{
    int nex, to;
} edge[M << 2];
int n, m, len, ans, T;
int head[M], far[N], link[N], pre[N], vis[N], ti[N];
//复杂度 O(n(nlogn+m)) ，不过和匈牙利一样跑不满。
// ans表示最大匹配边数
// link[i] 表示点 i 与点 link[i] 匹配
// link[i] = 0 的点没有被匹配 
queue<int> q;
void add_edge(int x, int y)
{
    edge[++len].nex = head[x];
    edge[len].to = y;
    head[x] = len;
}
int find(int x)
{
    return far[x] == x ? x : far[x] = find(far[x]);
}
int lca(int x, int y)
{
    for(++ T ; ; swap(x, y))
    {
        if (!x) continue;
        x = find(x);
        if (ti[x] == T) return x;
        ti[x] = T;
        x = pre[link[x]];
    }
}
void flower(int x, int y, int p)
{
    while (find(x) != p)
    {
        pre[x] = y , y = link[x];
        if (vis[y] == 2) vis[y] = 1, q.push(y);
        if (find(x) == x) far[x] = p;
        if (find(y) == y) far[y] = p;
        x = pre[y];
    }
}
bool bfs(int s)
{
   	rep(i , 1 , n) far[i] = i;
    memset(vis, 0, sizeof(vis)) , memset(pre, 0, sizeof(pre));
    while (!q.empty()) q.pop();
    vis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u] ; i ; i = edge[i].nex)
        {
            int v = edge[i].to;
            if (find(v) == find(u) || vis[v] == 2) continue;
            if (!vis[v])
            {
                vis[v] = 2 , pre[v] = u;
                if (!link[v])
                {
                    for (int now = v, last, tmp; now; now = last)
                    {
                        last = link[tmp = pre[now]];
                        link[now] = tmp;
                        link[tmp] = now;
                    }
                    return 1;
                }
                vis[link[v]] = 1;
                q.push(link[v]);
            }
            else
            {
                int p = lca(u, v);
                flower(u, v, p);
                flower(v, u, p);
            }
        }
    }
    return 0;
}
signed main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i , 1 , m)
    {
    	int x , y; 
        cin >> x >> y;
        add_edge(x, y) , add_edge(y, x);
    }
    rep(i , 1 , n) if(!link[i]) ans += bfs(i);
	cout << ans << '\n';
	rep(i , 1 , n) cout << link[i] << " \n"[i == n];
	return 0;
}
