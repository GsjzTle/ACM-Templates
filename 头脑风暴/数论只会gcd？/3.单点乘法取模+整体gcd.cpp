#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll pow_mod(ll x,ll n,ll mod)
{
	ll res = 1;
	while(n)
	{
		if(n & 1) res = res * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}
int prime[200010] , minprime[200010];
int euler(int n)
{
	int c = 0 , i , j;
	for(i = 2 ; i <= n ; i ++)
	{
		if(!minprime[i]) prime[++ c] = i , minprime[i] = i;
		for(j = 1 ; j <= c && i * prime[j] <= n ; j ++)
		{
			minprime[i * prime[j]] = prime[j];
			if(i % prime[j] == 0) break ;
		}
	}
	return c;
}
const ll mod = 1e9 + 7;
const int N = 3e5 + 10;
int n , q , I , X , a[N] , pre[N];
map<int , int>f[N];
multiset<int>se[N];
signed main()
{	
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	int sum = euler(200000);
	ll gcdd = 1;
	cin >> n >> q;
	for(int i = 1 ; i <= n ; i ++) cin >> a[i];
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 2 ; j * j <= a[i] ; j ++) if(a[i] % j == 0)
		{
			int c = 0;
			while(a[i] % j == 0) a[i] /= j , c ++ ;
			f[i][j] = c;
			se[j].insert(c);
		}
		if(a[i] > 1) f[i][a[i]] = 1 , se[a[i]].insert(1);
	}
	for(int i = 1 ; i <= sum ; i ++)
	{
		int p = prime[i];
		if(se[p].size() == n)
		{
			auto j = *se[p].begin();
			gcdd = gcdd * pow_mod(1LL * p , 1LL * j , mod) % mod;
			pre[p] = j;
		}
	}
	while(q --)
	{
		cin >> I >> X;
		for(int j = 1 ; prime[j] * prime[j] <= X && j <= sum ; j ++) if(X % prime[j] == 0)
		{
			int c = 0 , p = prime[j];
			while(X % p == 0) X /= p , c ++ ;
			if(f[I].count(p))
			{
				auto it = se[p].find(f[I][p]);
				se[p].erase(it);
			}
			f[I][p] += c;
			se[p].insert(f[I][p]);
			if(se[p].size() == n)
			{
				auto it = *se[p].begin();
				gcdd = gcdd * pow_mod(p , it - pre[p] , mod) % mod;
				pre[p] = it;
			}
		}
		if(X > 1)
		{
			if(f[I].count(X))
			{
				auto it = se[X].find(f[I][X]);
				se[X].erase(it);
			}		
			f[I][X] += 1;
			se[X].insert(f[I][X]);
			if(se[X].size() == n)
			{
				auto it = *se[X].begin();
				gcdd = gcdd * pow_mod(X , it - pre[X] , mod) % mod;
				pre[X] = it;
			}
		}
		cout << gcdd << '\n';
	}
	return 0;
}
