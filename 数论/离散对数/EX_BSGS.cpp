#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a, b, p, ans;
struct EX_BSGS
{
	ll mul(ll x, ll n, ll mod)
	{
		ll ans = mod != 1;
		for(x %= mod; n; n >>= 1, x = x * x % mod) if (n & 1) ans = ans * x % mod;
		return ans;
	}
	ll BSGS(ll a, ll b, ll p, ll ad)
	{
		map<ll, ll> mp;
		a %= p, b %= p, mp.clear();
		if(!a) return !b ? 0 : -1;
		ll t = ceil(sqrt(p)), x = b;
		for(ll i = 0; i <= t; i++) mp[x] = i, x = x * a % p;
		a = mul(a, t, p), x = a * ad % p; //upd: 原来的 x = a 改为了 x = a * ad % p
		for(ll i = 1; i <= t; i++)
		{
			if(mp.count(x)) return i * t - mp[x];
			x = x * a % p;
		}
		return -1;
	}
	ll exbsgs(ll a, ll b, ll p)
	{
		a %= p, b %= p;
		ll g = 0, ad = 1, d, ans;
		while((d = __gcd(a, p)) != 1)
		{
			if (b % d) return -1;
			g++, b /= d, p /= d, ad = (ad * a / d) % p;
			if(ad == b) return g;
		}
		if(~(ans = BSGS(a, b, p, ad))) return ans + g;
		return -1;
	}
}ebs;
signed main()
{
	while(cin >> a >> p >> b)
	{
		if(!a && !b && !p) break;
		ans = ebs.exbsgs(a, b, p);
		if(~ans) cout << ans << '\n';
		else cout << "No Solution\n";
	}
	return 0;
}
