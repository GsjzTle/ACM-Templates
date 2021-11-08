/*
gcd(a[1],a[2],a[3]...a[n])=gcd(a[1],a[2]-a[1],a[3]-a[2]...a[n]-a[n-1])
d[i]=a[i]-a[i-1]
gcd(a[l~r])=gcd(a[l], gcd(d[l+1]~d[r]))

树状数组： 
左边就是前缀和 a[i] = d[1] + (d[2] - d[1]) + ... + (d[i] - d[i - 1])

线段树： 
右边就是单点修改区间查询，对于一个差分序列修改的话，就只改l项和r+1两项
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
ll gcd(ll a,ll b){
	return b ? gcd(b , a % b) : a;
}
struct Tree{
	int l, r;
	ll gcd;
} tree[N << 2];

ll n , m , a[N] , d[N] , t[N];
void push_up(ll rt)
{
	tree[rt].gcd = abs(gcd(tree[rt << 1].gcd, tree[rt << 1 | 1].gcd));
}
void build(ll l, ll r, ll rt, ll *a)
{
	tree[rt].l = l, tree[rt].r = r;
	if (l == r)
	{
		tree[rt].gcd = a[l];
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, rt << 1, a);
	build(mid + 1, r, rt << 1 | 1, a);
	push_up(rt);
}
void update(ll rt, ll pos, ll val)
{
	ll l = tree[rt].l, r = tree[rt].r;
	if (l == r)
	{
		tree[rt].gcd += val;
		return;
	}
	ll mid = (l + r) >> 1;
	if (pos <= mid) update(rt << 1, pos, val);
	else update(rt << 1 | 1, pos, val);
	push_up(rt);
}
ll query(ll L, ll R, ll rt)
{
	ll l = tree[rt].l, r = tree[rt].r;
	if (L <= l && r <= R) return tree[rt].gcd;
	ll mid = (l + r) >> 1 , g = 0;
	if (L <= mid) g = abs(gcd(g, query(L, R, rt << 1)));
	if (R > mid) g = abs(gcd(g, query(L, R, rt << 1 | 1)));
	return g;
}
ll lowbit(ll x){
	return x & -x;
}
void add(ll pos, ll x){
	while (pos <= N - 9) t[pos] += x, pos += lowbit(pos);
}
ll ask(ll pos)
{
	ll res = 0;
	while (pos) res += t[pos], pos -= lowbit(pos);
	return res;
}
void update_range(ll l, ll r, ll k)
{
	update(1, l, k), update(1, r + 1, -k);
	add(l, k), add(r + 1, -k);
}
ll query_gcd(int l, int r)
{
	ll g = query(l + 1, r, 1);
	return abs(gcd(g, ask(l)));
}

signed main()
{
	ios::sync_with_stdio(false);
	
	cin >> n >> m;

	for (int i = 1; i <= n; i ++) cin >> a[i];

	for (int i = 1; i <= n + 1; i ++)
	{
		d[i] = a[i] - a[i - 1]; // 差分数组

		add(i, d[i]);
	}

	build(1, n + 1, 1, d); // 多开一个防止 r + 1 越界

	for (int i = 1; i <= m; i ++)
	{
		char op;
		
		cin >> op ;
		
		if (op == 'C')
		{
			int l, r;
			
			ll k;

			cin >> l >> r >> k;

			update_range(l, r, k);
		}
		else if (op == 'Q')
		{
			int l, r;

			cin >> l >> r;

			cout << query_gcd(l, r) << '\n';
		}
	}
	return 0;
}
