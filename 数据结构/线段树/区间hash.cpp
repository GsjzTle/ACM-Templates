#include<bits/stdc++.h>
#define int long long
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
using namespace std;
const int N = 1e6 + 10;
const int mod = 998244353;// prime : 1610612741
struct Seg_Tree{
	int l , r , max , hash , lazy;
}tree[N << 2];
int a[N] , p[N] , q[N]; 
void push_up(int rt , int len1 , int len2)
{
	tree[rt].hash = tree[rt << 1].hash * p[len2] + tree[rt << 1 | 1].hash;
	tree[rt].hash %= mod;
}
void build(int l , int r , int rt , int *a)
{
	tree[rt].l = l , tree[rt].r = r , tree[rt].lazy = 0;
	if(l == r)
	{
		tree[rt].hash = a[l] % mod;
		return ;
	}
	int mid = l + r >> 1;
	build(l , mid , rt << 1 , a);
	build(mid + 1 , r , rt << 1 | 1 , a);
	push_up(rt , mid - l + 1 , r - mid);
}
void f(int rt , int l , int r , int k)
{
	tree[rt].lazy += k , tree[rt].lazy %= mod;
	tree[rt].hash += k * q[r - l];
	tree[rt].hash % mod;
}
void push_down(int rt , int l , int r)
{
	int x = tree[rt].lazy;
	int mid = l + r >> 1;
	f(rt << 1 , l , mid , x);
	f(rt << 1 | 1 , mid + 1 , r , x);
	tree[rt].lazy = 0;
}
void update_range(int L , int R , int rt , int val)
{
	int l = tree[rt].l , r = tree[rt].r;
	int mid = l + r >> 1;
	if(L <= l && r <= R) 
	{
		tree[rt].lazy += val , tree[rt].lazy %= mod;
		tree[rt].hash += val * q[r - l];
		tree[rt].hash %= mod;
		return ;
	}
	push_down(rt , l , r);
	if(L <= mid) update_range(L , R , rt << 1 , val);
	if(R > mid) update_range(L , R , rt << 1 | 1 , val);
	push_up(rt , mid - l + 1 , r - mid);
}
int query_range(int rt , int L , int R)
{
	int l = tree[rt].l , r = tree[rt].r;
	int ans = 0;
	int mid = l + r >> 1;
	push_down(rt , l , r);
	if(L <= l && r <= R) return tree[rt].hash % mod;
	else if(R <= mid) return query_range(rt << 1 , L , R) % mod;
	else if(L > mid) return query_range(rt << 1 | 1 , L , R) % mod; 
	else 
	{
		int s = query_range(rt << 1 , L , R);
		int t = query_range(rt << 1 | 1 , L , R);
		ans = s * p[min(R , r) - mid] % mod + t;
		ans %= mod;
	}
	return ans % mod;
}
void init()
{
	q[0] = 1 , p[0] = 1; 
	rep(i , 1 , N - 10) p[i] = p[i - 1] * 131 , p[i] %= mod , q[i] = (q[i - 1] + p[i]) % mod;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	init();
	int n ;
	cin >> n;
	rep(i , 1 , n) cin >> a[i];
	build(1 , n , 1 , a);
//	cout << query_range(1 , 1 , 5) << " " << query_range(1 , 6 , 10) << '\n';
//	cout << query_range(1 , 1 , 3) << " " << query_range(1 , 4 , 6) << '\n';
	return 0;
}
