```text
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10 , mod = 998244353;
int fac[N] , inv[N];
int pow_mod(int x , int n , int mod)
{
	int res = 1;
	while(n)
	{
		if(n & 1) res = res * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}
void init()
{
	int up = N - 10;
	fac[0] = 1;
	for(int i = 1 ; i <= up ; i ++) fac[i] = fac[i - 1] * i % mod;
	inv[up] = pow_mod(fac[up] , mod - 2 , mod);
	for(int i = up - 1 ; i >= 0 ; i --) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int C(int n , int m)
{
	if(n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
signed main()
{
	init();
	int n , m ;
	cin >> n >> m ;
	cout << C(n , m) << '\n';
	return 0;
}
```

