#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 50;
int n , m , Q;
int max(int x , int y) { return x > y ? x : y; }
struct segy
{
	int mx[N], tag[N];
	void change(int rt, int l, int r, int L, int R, int val)
	{
		mx[rt] = max(mx[rt], val);
		if (l == L && r == R)
		{
			tag[rt] = max(tag[rt], val);
			return;
		}
		int Mid = L + R >> 1;
		if (r <= Mid)
			change(rt << 1, l, r, L, Mid, val);
		else if (l > Mid)
			change(rt << 1 | 1, l, r, Mid + 1, R, val);
		else
			change(rt << 1, l, Mid, L, Mid, val), change(rt << 1 | 1, Mid + 1, r, Mid + 1, R, val);
	}
	int query(int rt, int l, int r, int L, int R)
	{
		if (l == L && r == R)
			return mx[rt];
		int ans = tag[rt], Mid = L + R >> 1;
		if (r <= Mid)
			ans = max(ans, query(rt << 1, l, r, L, Mid));
		else if (l > Mid)
			ans = max(ans, query(rt << 1 | 1, l, r, Mid + 1, R));
		else
			ans = max(ans, max(query(rt << 1, l, Mid, L, Mid), query(rt << 1 | 1, Mid + 1, r, Mid + 1, R)));
		return ans;
	}
};
struct segx
{
	segy mx[N], tag[N];
	void change(int rt, int l, int r, int L, int R, int ll, int rr, int val)
	{
		mx[rt].change(1, ll, rr, 1, m, val);
		if (l == L && r == R)
		{
			tag[rt].change(1, ll, rr, 1, m, val);
			return;
		}
		int Mid = L + R >> 1;
		if (r <= Mid)
			change(rt << 1, l, r, L, Mid, ll, rr, val);
		else if (l > Mid)
			change(rt << 1 | 1, l, r, Mid + 1, R, ll, rr, val);
		else
			change(rt << 1, l, Mid, L, Mid, ll, rr, val), change(rt << 1 | 1, Mid + 1, r, Mid + 1, R, ll, rr, val);
	}
	int query(int rt, int l, int r, int L, int R, int ll, int rr)
	{
		if (l == L && r == R)
			return mx[rt].query(1, ll, rr, 1, m);
		int ans = tag[rt].query(1, ll, rr, 1, m), Mid = L + R >> 1;
		if (r <= Mid)
			ans = max(ans, query(rt << 1, l, r, L, Mid, ll, rr));
		else if (l > Mid)
			ans = max(ans, query(rt << 1 | 1, l, r, Mid + 1, R, ll, rr));
		else
			ans = max(ans, max(query(rt << 1, l, Mid, L, Mid, ll, rr), query(rt << 1 | 1, Mid + 1, r, Mid + 1, R, ll, rr)));
		return ans;
	}
} t;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);;
	cin >> n >> m >> Q;
	while (Q --)
	{
		int a, b, k, x, y;
		cin >> a >> b >> k >> x >> y;
		++x, ++y;
		int r = t.query(1, x, x + a - 1, 1, n, y, y + b - 1) + k;
		t.change(1, x, x + a - 1, 1, n, y, y + b - 1, r);
	}
	cout << t.query(1, 1, n, 1, n, 1, m) << '\n';
	return 0;
}
