+ 给出一个长度为n的序列，有四种操作。
+ $Q$ $X$ $Y$：询问区间 $[x,y]$ 的最大值
+ $A$ $X$ $Y$：询问区间 $[x,y]$的历史最大值
+ $P$ $X$ $Y$ $Z$：将区间 $[x,y]$ 中的每个数增加 $z$
+ $C$ $X$ $Y$ $Z$：将区间 $[x,y]$ 中的每个数都变成 $z$

```text
#include<bits/stdc++.h>
#define int long long
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
using namespace std;
const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n, m , a[N];
struct Tree
{
	int l, r, ma, hma; // hma 历史最大值 
	int add, hadd, se, hse; //add 加的值 , se 赋的值
	//had 和 hse分别代表 ad和 se 的历史最大值。
} tree[N << 2];
void push_up(int rt)
{
	tree[rt].ma = max(tree[rt << 1].ma, tree[rt << 1 | 1].ma);
	tree[rt].hma = max(tree[rt << 1].hma, tree[rt << 1 | 1].hma);
}
void push_down(int rt)
{
	for(int i = 0 ; i <= 1 ; i ++) // 枚举左右儿子
	{
		int now = rt << 1 | i; 
		tree[now].hma = max(tree[now].hma, tree[now].ma + tree[rt].hadd);
		if(tree[now].hse != -inf) tree[now].hse = max(tree[now].hse, tree[now].se + tree[rt].hadd);
		else tree[now].hadd = max(tree[now].hadd, tree[rt].hadd + tree[now].add);
		tree[now].hma = max(tree[now].hma, tree[rt].hse);
		tree[now].hse = max(tree[now].hse, tree[rt].hse);
		if(tree[rt].add != 0)
		{
			tree[now].ma += tree[rt].add , tree[now].hma = max(tree[now].hma, tree[now].ma);
			if (tree[now].se == -inf)
			{
				tree[now].add += tree[rt].add;
				tree[now].hadd = max(tree[now].hadd, tree[now].add);
			}
			else
			{
				tree[now].se += tree[rt].add;
				tree[now].hse = max(tree[now].hse, tree[now].se);
			}
		}
		else if(tree[rt].se != -inf)
		{
			tree[now].ma = tree[rt].se;
			tree[now].hma = max(tree[now].hma, tree[now].ma);
			tree[now].se = tree[rt].se;
			tree[now].hse = max(tree[rt].se, tree[now].hse);
			tree[now].add = 0;
		}
	}
	tree[rt].se = tree[rt].hse = -inf;
	tree[rt].add = tree[rt].hadd = 0;
}
void build(int rt, int l, int r , int *a)
{
	tree[rt].l = l , tree[rt].r = r , tree[rt].se = tree[rt].hse = -inf;
	if(l == r)
	{
		tree[rt].ma = a[l];
		tree[rt].hma = tree[rt].ma;
		tree[rt].add = tree[rt].hadd = 0;
		tree[rt].se = tree[rt].hse = -inf;
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid , a);
	build(rt << 1 | 1, mid + 1, r , a);
	push_up(rt);
}
void add(int rt, int l, int r, int x)
{
	if(tree[rt].l >= l && tree[rt].r <= r)
	{
		tree[rt].ma += x;
		tree[rt].hma = max(tree[rt].hma, tree[rt].ma);
		if(tree[rt].se == -inf)
		{
			tree[rt].add += x;
			tree[rt].hadd = max(tree[rt].hadd, tree[rt].add);
		}
		else
		{
			tree[rt].se += x;
			tree[rt].hse = max(tree[rt].hse, tree[rt].se);
		}
		return;
	}
	push_down(rt);
	int mid = (tree[rt].l + tree[rt].r) >> 1;
	if(l <= mid) add(rt << 1, l, r, x);
	if(r > mid) add(rt << 1 | 1, l, r, x);
	push_up(rt);
}
void change(int rt, int l, int r, int x)
{
	if(tree[rt].l >= l && tree[rt].r <= r)
	{
		tree[rt].ma = tree[rt].se = x;
		tree[rt].hma = max(tree[rt].hma, tree[rt].ma);
		tree[rt].hse = max(x, tree[rt].hse);
		tree[rt].add = 0;
		return;
	}
	push_down(rt);
	int mid = (tree[rt].l + tree[rt].r) >> 1;
	if(l <= mid) change(rt << 1, l, r, x);
	if(r > mid) change(rt << 1 | 1, l, r, x);
	push_up(rt);
}
int query_max(int rt, int l, int r)
{
	if(tree[rt].l >= l && tree[rt].r <= r) return tree[rt].ma;
	push_down(rt);
	int mid = (tree[rt].l + tree[rt].r) >> 1;
	if (r <= mid) return query_max(rt << 1, l, r);
	else if (l > mid) return query_max(rt << 1 | 1, l, r);
	else return max(query_max(rt << 1, l, mid), query_max(rt << 1 | 1, mid + 1, r));
}
int query_hmax(int rt, int l, int r)
{
	if(tree[rt].l >= l && tree[rt].r <= r) return tree[rt].hma;
	push_down(rt);
	int mid = (tree[rt].l + tree[rt].r) >> 1;
	if(r <= mid) return query_hmax(rt << 1, l, r);
	else if(l > mid) return query_hmax(rt << 1 | 1, l, r);
	else return max(query_hmax(rt << 1, l, mid), query_hmax(rt << 1 | 1, mid + 1, r));
}
signed main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	rep(i , 1 , n) cin >> a[i]; 
	build(1, 1, n , a);
	cin >> m;
	rep(i , 1 , m)
	{
		int x, y, z;
		char op;
		cin >> op;
		if(op == 'A')
		{
			cin >> x >> y;
			cout << query_hmax(1 , x , y) << '\n';
		}
		else if(op == 'C')
		{
			cin >> x >> y >> z;
			change(1, x, y, z);
		}
		else if(op == 'P')
		{
			cin >> x >> y >> z;
			add(1, x, y, z);
		}
		else
		{
			cin >> x >> y;
			cout << query_max(1 , x , y) << '\n';
		}
	}
	return 0;
}
```

