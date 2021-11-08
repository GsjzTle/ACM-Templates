如果是全局动态第$k$大，可以树状数组上二分。
注意：因为没有离散化，时间和空间的常数都很大。
时间复杂度：$O(n * logn * log(up))$，空间复杂度：$O(n * logn * log(up))$。其中$up$是权值上限。
给定$n$个整数构成的序列，将对于指定的闭区间查询其区间内的第$k$小值。支持点修改。
输入$l , r , k$表示查询$[l , r]$区间内第$k$小值。
思路：第$i$棵权值线段树维护的是$[i - lowbit(i) + 1 , i]$而不是$[1,i]$的信息。修改时修改$logn$棵树。询问时进行$logn$次两棵线段树做差。

```text
int n , m ;
int a[N] ;
char s[5] ;
int lowbit(int x) { return x & (-x) ; }
struct Tree
{
	int up , cnt ;
	int lson[N * 300] , rson[N * 300] , sum[N * 300] ;
	int rt[N * 300] ;
	vector<int> vx , vy ;
	void init()
	{
		up = 1e9 , cnt = 0 ;
		mem0(lson) , mem0(rson) , mem0(sum) , mem0(rt) ;
	}
	void update(int &now , int l , int r , int x , int y)
	{
		if(now == 0)  now = ++ cnt ;
		sum[now] += y ;
		if(l == r)  return ;
		int mid = (l + r) >> 1 ;
		if(x <= mid)  update(lson[now] , l , mid , x , y) ;
		else  update(rson[now] , mid + 1 , r , x , y) ;
	}
	void add(int i , int x , int y)
	{
		for(int j = i ; j <= n ; j += lowbit(j))
		update(rt[j] , 0 , up , x , y) ;
	}
	int query(int l , int r , int k)
	{
		if(l == r)  return l ;
		int num = 0 , mid = (l + r) >> 1 ;
		int sizx = sz(vx) , sizy = sz(vy) ;
		for(auto x : vx)  num -= sum[lson[x]] ;
		for(auto y : vy)  num += sum[lson[y]] ;
		if(k <= num)
		{			
			rep(i , 0 , sizx - 1)  vx[i] = lson[vx[i]] ;
			rep(i , 0 , sizy - 1)  vy[i] = lson[vy[i]] ;
			return query(l , mid , k) ;
		}
		else
		{
			rep(i , 0 , sizx - 1)  vx[i] = rson[vx[i]] ;
			rep(i , 0 , sizy - 1)  vy[i] = rson[vy[i]] ;
			return query(mid + 1 , r , k - num) ;
		}
	}
	void ask(int l , int r , int k)
	{
		cl(vx) , cl(vy) ;
		for(int j = l - 1 ; j >= 1 ; j -= lowbit(j))  vx.pb(rt[j]) ;
		for(int j = r ; j >= 1 ; j -= lowbit(j))  vy.pb(rt[j]) ;
		w(query(0 , up , k)) , en() ;
	}
} tree ;
signed main()
{
	rr(n , m) ;
	rep(i , 1 , n)  r(a[i]) ;
	tree.init() ;
	rep(i , 1 , n)  tree.add(i , a[i] , 1) ;
	s[0] = 'Q' ;
	rep(i , 1 , m)
	{
		rst(s) ;
		if(s[0] == 'Q')
		{
			int l , r , k ;
			rr(l , r) , r(k) ;
			tree.ask(l , r , k) ;
		}
		else
		{
			int x , y ;
			rr(x , y) ;
			tree.add(x , a[x] , -1) ;
			a[x] = y ;
			tree.add(x , a[x] , 1) ;
		}
	}
	return 0 ;
} 
```