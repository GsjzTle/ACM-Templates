问题：

> 给定一个长度为 $N$ 的数组 $A$，$M$ 次询问和一个常数 $K$
> 每次询问给出区间 $[L,R]$，要求在区间中找出若干个数
> 使得这些数的异或和或上 $K$ 的值最大，即 `ans = MAX(sum | K) `

实现：线段树套线性基

思路：

> 区间操作 —— 线段树
> 异或操作 —— 线性基
>
> 首先 $ans=K|sum$，所以并不是 $sum$(异或和) 越大，$ans$ 就越大
>
> 举个例子：$K = 1000$，$sum1 = 1000$，$sum2 = 0111$
> 那么显然 $sum1 > sum2$，$(K|sum1) < (K|sum2)$
>
> 我们发现按位或运算，只要有一个 $1$ 就行了，两个 $1$ 和一个 $1$ 没有区别，所以对于 $K$ 中二进制下为 $1$的所有位，线性基得到的$sum$，这一位都没必要是1，所以我们可以把整个$A$ 数组的 $K$ 是 $1$ 的所有二进制位全部变成 $0$。
>
> 这样等于删掉了不需要的 $1$ ，因为这些 $1$ 存在在这个线性基里时，会导致最大异或和更大，但是这个更大的数对我们最终的答案没有贡献。
>
> 所以我们可以将 $k$ 取反，然后把所有数在加入线性基之前，全部按位异或运算一遍，这样把没用的 $1$ 全部删掉，再加入线性基
>
> 这样求出来的 $max_sum$（最大异或和），每一位都能使得 $K$ 变为更大的数了

```text
const int N = 50007, mod = 1e9 + 7, INF = 2.1e9;
const int Base = 27 * 2;//线性基数组大小，开大一点，嘻嘻嘻
//s < 2 ^ {63} - 1
//说明线性基最多有62个向量
struct LinearBase
{
	int dimension = 27; // dimension 维数，就是线性基的维数 = logs, (s为元素最大值)
	//dimension一定要是logs,错一点就会WA呜呜呜
	//线性基数组
	ll a[Base + 7];//注意这里要加一点，因为下面的循环也是这个数
	LinearBase()
	{
		fill(a, a + Base + 7, 0);
	}
	LinearBase(ll *x, int n)
	{
		build(x, n);
	}
	void insert(ll t)
	{
		// 逆序枚举二进制位
		for(int i = dimension; i >= 0; -- i)
		{
			if(t == 0) return ;
			// 如果 t 的第 i 位为 0，则跳过
			if(!(t >> i & 1)) continue;
			// 如果 a[i] != 0，则用 a[i] 消去 t 的第 i 位上的 1
			if(a[i]) t ^= a[i];
			else
			{
				// 找到可以插入 a[i] 的位置
				// 用 a[0...i - 1] 消去 t 的第 [0, i) 位上的 1
				// 如果某一个 a[k] = 0 也无须担心，因为这时候第 k 位
				//不存在于线性基中，不需要保证 t 的第 k 位为 0
				for(int k = 0; k < i; ++ k)
					if(t >> k & 1) t ^= a[k];
				// 用 t 消去 a[i + 1...L] 的第 i 位上的 1
				for(int k = i + 1; k <= dimension; ++ k)
					if(a[k] >> i & 1) a[k] ^= t;
				// 插入到 a[j] 的位置上
				a[i] = t;
				break;
			}
			// 此时 t 的第 i 位为 0，继续寻找其最高位上的 1
		}
		// 如果没有插入到任何一个位置上，则表明 t 可以由 a 中若干个元素的异或和表示出，即 t 在 span(a) 中
	}
	// 数组 x 表示集合 S，下标范围 [1...n]
	void build(ll *x, int n)
	{
		fill(a, a + Base + 7, 0);
		for(int i = 1; i <= n; ++ i)
			insert(x[i]);
	}
	ll query_max()
	{
		ll res = 0;
		for(int i = 0; i <= dimension; ++ i)
			res ^= a[i];
		return res;
	}
	void mergefrom(const LinearBase &other)
	{
		for(int i = 0; i <= dimension; ++ i)
			insert(other.a[i]);
	}
	static LinearBase merge(const LinearBase &a, const LinearBase &b)
	{
		LinearBase res = a;
		for(int i = 0; i <= 27; ++ i)
			res.insert(b.a[i]);
		return res;
	}
};
int n, m, q, k;
ll a[N];
struct Tree
{
	int l, r;
	LinearBase elem;//element
} tr[N];
void build(int p, int l, int r)
{
	tr[p] = {l, r};
	if(l == r)
	{
		tr[p].elem.insert(a[r]);
		return ;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	tr[p].elem = tr[p].elem.merge(tr[p << 1].elem, tr[p << 1 | 1].elem);
}
LinearBase query(int p, int l, int r)
{
	if(l <= tr[p].l && tr[p].r <= r) return tr[p].elem;
	int mid = (tr[p].l + tr[p].r) >> 1;
	LinearBase res;
	if(l <= mid) res = res.merge(res, query(p << 1, l, r));
	if(r > mid) res = res.merge(res, query(p << 1 | 1, l, r));
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	int T = 1;
	cin >> T;
	while(T --)
	{
		cin >> n >> q >> k ;
		rep(i , 1 , n) 
		{
			cin >> a[i];
			/*k的存在会对求线性基最大值时的主元产生影响，所以预处理一下，a[i]只保留k为0的位，这样贡献最大*/
			for(int j = 0; j < 27; ++ j)
			{
				if((k >> j & 1) && (a[i] >> j & 1))
					a[i] ^= (1 << j);
			}
		}
		build(1, 1, n);
		while(q -- )
		{
			int l, r;
			cin >> l >> r;
			LinearBase res = query(1, l, r);
			cout << (res.query_max() | k) << '\n';
		}
	}
	return 0;
}
```

