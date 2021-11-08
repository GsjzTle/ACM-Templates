**复杂度 $O(M+NlogN)$**

```text
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#define rep(i, a, n) for (int i = a; i <= n; i++)
#define per(i, n, a) for (int i = n; i >= a; i--)
#define il inline
using namespace std;
using namespace __gnu_pbds;
const int inf(0x3f3f3f3f);
typedef __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, pairing_heap_tag> heap;
template <typename T>
void read(T &res)
{
	bool flag = false;
	char ch;
	while (!isdigit(ch = getchar()))
		(ch == '-') && (flag = true);
	for (res = ch - 48; isdigit(ch = getchar()); res = (res << 1) + (res << 3) + ch - 48)
		;
	flag && (res = -res);
}
template <typename T>
void Out(T x)
{
	if (x < 0)
		putchar('-'), x = -x;
	if (x > 9)
		Out(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10;
heap que;
heap::point_iterator id[N];
struct Edge
{
	int nex, to, w;
} edge[N << 1];
int head[N], tot;
il void add_edge(int u, int v, int w)
{
	edge[++tot].nex = head[u];
	edge[tot].to = v;
	edge[tot].w = w;
	head[u] = tot;
}
int n, m, s, dis[N];
il void dij(int st)
{
	memset(dis, inf, sizeof(dis));
	dis[st] = 0;
	id[st] = que.push(make_pair(0, st));
	while (!que.empty())
	{
		int u = que.top().second;
		que.pop();
		for (int i = head[u]; i; i = edge[i].nex)
		{
			int v = edge[i].to;
			int w = edge[i].w;
			if (w + dis[u] < dis[v])
			{
				dis[v] = dis[u] + edge[i].w;
				if (id[edge[i].to] != 0)
					que.modify(id[v], make_pair(dis[v], v));
				else
					id[v] = que.push(make_pair(dis[v], v));
			}
		}
	}
}
signed main()
{
	read(n), read(m), read(s);
	rep(i, 1, m)
	{
		int u, v, w;
		read(u), read(v), read(w);
		add_edge(u, v, w);
	}
	dij(s);
	rep(i, 1, n) Out(dis[i]), putchar(' ');
	return 0;
}
```

