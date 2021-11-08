#include<bits/stdc++.h>
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
#define int long long
using namespace std;
const int N = 1e6 + 10 , mod = 998244353;
int tree[N << 2] , a[N] , fac[N];
int lowbit(int x)
{
	return x & (-x);
}
void update(int pos , int val)
{
	while(pos <= N - 1)
	{
		tree[pos] += val;
		pos += lowbit(pos);
	}
}
int query(int pos)
{
	int res = 0;
	while(pos)
	{
		res += tree[pos];
		pos -= lowbit(pos);
	}
	return res;
}
void init()
{
	fac[0] = 1;
	rep(i , 1 , N - 10) fac[i] = fac[i - 1] * i % mod;
}
int calc(int n)
{
	int rank = 0;
	rep(i , 1 , n) update(i , 1);
	rep(i , 1 , n)
	{
		rank += fac[n - i] * query(a[i] - 1);
		rank %= mod;
		update(a[i] , -1);
	}
	return rank + 1;
}
signed main()
{
	init();
	int n;
	cin >> n;
	rep(i , 1 , n) cin >> a[i];
	cout << calc(n) << '\n';
	return 0;
}
