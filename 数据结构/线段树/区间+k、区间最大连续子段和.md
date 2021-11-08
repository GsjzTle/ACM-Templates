给定一个整数序列 $a$，支持两种操作：

- `1 l r x` 表示给区间 $[l,r]$ 中每个数加上 $x$
- `2 l r` 表示查询区间 $[l,r]$ 的最大子段和（可以为 $0$）

复杂度 $O((n+m)\log^3 n+q\log n)$

```text
const int N = 400500;
const long long INF = 2e18;
int n, w[N], m;
long long lazy[N << 2];
struct LINE
{ //一次函数
	int k;
	long long b;
	LINE operator+(const LINE &tree) const
	{
		return (LINE){
			k + tree.k, b + tree.b};
	}
};
pair<LINE, long long> max(LINE tree, LINE b) //对两个一次函数取x=0时的最值，同时给出max的选取不发生变化的最大值C(即 x>C 时max变成另一个)
{
	if (tree.k < b.k || (tree.k == b.k && tree.b < b.b))
		swap(tree, b);
	if (tree.b >= b.b)
		return make_pair(tree, INF);
	return make_pair(b, (b.b - tree.b) / (tree.k - b.k));
}
struct Node
{
	LINE ls, rs, ans, sum;
	long long x; //增量>x时子树内会有max的选取发生变化
	Node operator+(const Node &tree) const
	{
		Node t;
		t.x = min(x, tree.x);
		pair<LINE, long long> tmp = max(ls, sum + tree.ls);
		t.ls = tmp.first, t.x = min(t.x, tmp.second);
		tmp = max(tree.rs, rs + tree.sum);
		t.rs = tmp.first, t.x = min(t.x, tmp.second);
		tmp = max(ans, tree.ans);
		t.x = min(t.x, tmp.second);
		tmp = max(tmp.first, rs + tree.ls);
		t.ans = tmp.first, t.x = min(t.x, tmp.second);
		t.sum = sum + tree.sum;
		return t;
	}
} tree[N << 2];
void build(int rt, int l, int r)
{	
	if (l == r)
	{
		LINE t = {1, w[l]};
		tree[rt] = (Node){
			t, t, t, t, INF};
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
	tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void upd(int rt, long long w)
{
	lazy[rt] += w;
	tree[rt].x -= w;
	tree[rt].ls.b += tree[rt].ls.k * w;
	tree[rt].rs.b += tree[rt].rs.k * w;
	tree[rt].ans.b += tree[rt].ans.k * w;
	tree[rt].sum.b += tree[rt].sum.k * w;
}
void upd(int rt, int l, int r, long long w)
{
	if (w > tree[rt].x) //如果增量使得子树内有max发生变化则递归下去重构
	{
		long long t = lazy[rt] + w;
		lazy[rt] = 0;
		int mid = (l + r) >> 1;
		upd(rt << 1, l, mid, t), upd(rt << 1 | 1, mid + 1, r, t);
		tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
	}
	else upd(rt, w);
}
void pushdown(int rt)
{
	if (lazy[rt])
	{
		long long t = lazy[rt];
		lazy[rt] = 0;
		upd(rt << 1, t), upd(rt << 1 | 1, t);
	}
}
void update_range(int rt, int l, int r, int L, int R, int x)
{
	if (L <= l && r <= R)
	{
		upd(rt, l, r, x);
		return;
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update_range(rt << 1, l, mid, L, R, x);
	if (R  > mid) update_range(rt << 1 | 1, mid + 1, r, L, R, x);
	tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
Node query(int rt, int l, int r, int L, int R)
{
	if (l >= L && r <= R) return tree[rt];
	pushdown(rt);
	int mid = (l + r) >> 1;
	if (R <= mid) return query(rt << 1, l, mid, L, R);
	if (L  > mid) return query(rt << 1 | 1, mid + 1, r, L, R);
	return query(rt << 1, l, mid, L, mid) + query(rt << 1 | 1, mid + 1, r, mid + 1, R);
}
signed main()
{
	cin >> n >> m;
	rep(i, 1, n) cin >> w[i];
	build(1, 1, n);
	while (m--)
	{
		int op, l, r, x;
		cin >> op >> l >> r;
		if (op == 1)
		{
			cin >> x;
			update_range(1, 1, n, l, r, x);
		}
		else cout << max(0ll , query(1 , 1 , n , l , r).ans.b) << '\n';
	}
	return 0;
}
```

