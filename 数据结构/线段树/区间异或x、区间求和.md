- 给定 $n$ 个数的序列 $a$，$m$ 次操作，操作有两种：
  1. 求 $\displaystyle\sum_{i=l}^r a_i$
  2. 把 $a_l\sim a_r$ 异或上 $x$
- $1\le n\le 10^5$，$1\le m\le 5\times 10^4$，$0\le a_i\le 10^6$，$1\le x\le 10^6$

把每个数进行二进制拆分，然后按位组成 $21$ 个新序列 ($2^{21}>10^6$) 

再对于每个序列建立一棵线段树维护（有点类似二维线段树

```tet
const int N = 3e5 + 10;
struct Tree{
	int lazy;
	int l , r , cnt;
}tree[N][25];
void push_up(int rt , int id)
{
	tree[rt][id].cnt = tree[rt << 1][id].cnt + tree[rt << 1 | 1][id].cnt;
}
void F(int rt , int id)
{
	int l = tree[rt][id].l , r = tree[rt][id].r;
	tree[rt][id].cnt = (r - l + 1) - tree[rt][id].cnt;
	tree[rt][id].lazy ^= 1;
}
void push_down(int rt , int id)
{
	int &x = tree[rt][id].lazy;
	if(x)
	{
		F(rt << 1 , id) , F(rt << 1 | 1 , id);
		x = 0;
	}
}
void build(int l , int r , int rt , int *a)
{
	rep(id , 0 , 22) tree[rt][id].l = l , tree[rt][id].r = r;
	if(l == r)
	{
		rep(id , 0 , 22) tree[rt][id].cnt = a[l] >> id & 1;
		return ;
	}
	int mid = l + r >> 1;
	build(l , mid , rt << 1 , a) , build(mid + 1 , r , rt << 1 | 1 , a);
	rep(id , 0 , 22) push_up(rt , id);
}
void update_range(int L , int R , int rt , int x)
{
	int l = tree[rt][0].l , r = tree[rt][0].r;
	if(L <= l && r <= R) 
	{
		rep(id , 0 , 22)
		{	
			int num = x >> id & 1;
			if(!num) continue ;
			tree[rt][id].cnt = (r - l + 1) - tree[rt][id].cnt;
			tree[rt][id].lazy ^= 1;
		}
		return ;
	}
	rep(id , 0 , 22) push_down(rt , id);
	int mid = l + r >> 1;
	if(L <= mid) update_range(L , R , rt << 1 , x); 
	if(R >  mid) update_range(L , R , rt << 1 | 1 , x);
	rep(id , 0 , 22) push_up(rt , id);
}
int query_range(int L , int R , int rt)
{
	int l = tree[rt][0].l , r = tree[rt][0].r;
	int sum = 0;
	if(L <= l && r <= R)
	{
		rep(id , 0 , 22) sum += (1ll << id) * tree[rt][id].cnt;
		return sum;
	}
	int mid = l + r >> 1;
	rep(id , 0 , 22) push_down(rt , id);
	if(L <= mid) sum += query_range(L , R , rt << 1);
	if(R >  mid) sum += query_range(L , R , rt << 1 | 1);
	return sum; 
}
int n , m , a[N];
signed main()
{
	cin >> n;
	rep(i , 1 , n) cin >> a[i];
	build(1 , n , 1 , a);
	cin >> m;
	while(m --)
	{
		int op , l , r , x;
		cin >> op >> l >> r;
		if(op == 1) cout << query_range(l , r , 1) << '\n';
		else 
		{
			cin >> x;
			update_range(l , r , 1 , x);
		}
	}
	return 0;
}
```

