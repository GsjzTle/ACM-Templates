#include<bits/stdc++.h>
#define int long long
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 2e5 + 10;
struct node{
    int dis , pos;
    bool operator <( const node &x )const{
        return x.dis < dis;
    }
};
struct Edge{
    int to , dis , nex;
}edge[N << 1];
int head[N], dis[N] , tot , vis[N] , n , m , s;
inline void add_edge(int u , int v , int d)
{
    edge[++ tot].dis = d;
    edge[tot].to = v;
    edge[tot].nex = head[u];
    head[u] = tot;
}
inline void dijkstra(int s)
{
    memset(dis , inf , sizeof(dis)) ;
    dis[s] = 0;
    priority_queue <node> que;
    que.push(node{0, s});
    while(!que.empty())
    {
        node tmp = que.top();
        que.pop();
        int u = tmp.pos, d = tmp.dis;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u] ; i ; i = edge[i].nex)
        {
            int v = edge[i].to;
            if(dis[v] > dis[u] + edge[i].dis)
            {
                dis[v] = dis[u] + edge[i].dis;
                if(!vis[v]) que.push(node{dis[v] , v});
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    rep(i , 1 , m)
    {
        int u , v , w;
        cin >> u >> v >> w;
        add_edge(u , v , w);
    }
    dijkstra(s);
    rep(i , 1 , n) cout << dis[i] << " ";
    cout << '\n';
    return 0;
}
