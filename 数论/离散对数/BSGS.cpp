#include <bits/stdc++.h>
#define ll long long 
using namespace std;
struct BSGS
{
	ll power(ll a, ll b, ll c) //������
	{
		if(b == 0) return 1 % c;
		ll ans = 1, t = a;
		while (b > 0)
		{
			if (b % 2 == 1) ans = ans * t % c;
			b >>= 1;
			t = t * t % c;
		}
		return ans;
	}
	ll bsgs(ll a, ll b, ll p) //bsgs
	{
		map<ll, ll> hash;
		hash.clear(); //����һ��Hash��
		b %= p;
		ll t = sqrt(p) + 1;
		for(ll i = 0; i < t; ++i) hash[(ll)b * power(a, i, p) % p] = i; //��ÿ��j��Ӧ��ֵ����Hash��
		a = power(a, t, p);
		if(!a) return b == 0 ? 1 : -1; //����
		for(ll i = 1; i <= t; ++i) //��Hash���в����Ƿ���i��Ӧ��jֵ
		{
			ll val = power(a, i, p);
			int j = hash.find(val) == hash.end() ? -1 : hash[val];
			if (j >= 0 && i * t - j >= 0)
				return i * t - j;
		}
		return -1; //�޽ⷵ��-1
	}
} bs;
signed main()
{
	ll p , a , b;
	cin >> p >> a >> b;
	ll ans = bs.bsgs(a, b, p);
	if(~ans) cout << ans << '\n';
	else cout << "no solution\n";
	return 0;
}
