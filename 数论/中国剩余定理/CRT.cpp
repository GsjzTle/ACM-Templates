#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
#define ll long long
using namespace std;
ll n , p[20], q[20];
ll ex_gcd(ll a, ll b, ll &x, ll &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll d = ex_gcd(b, a % b, x, y);
	ll temp = x;
	x = y, y = temp - a / b * y;
	return d;
}
ll CRT(ll *p, ll *q, ll n /*方程组数*/)
{
	ll x, y, a = 0, m, LCM = 1;
	rep(i , 1 , n) LCM *= p[i];
	rep(i , 1 , n)
	{
		m = LCM / p[i];
		ex_gcd(p[i], m, x, y);
		a = (a + y * m * q[i]) % LCM;
	}
	return a > 0 ? a : a + LCM;
}
signed main()
{
	cin >> n;
	rep(i, 1, n) cin >> p[i] >> q[i];
	cout << CRT(p, q, n) << '\n';
	return 0;
}
