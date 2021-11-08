+ 给定 $a,p,b$，求满足 $a^x≡b \pmod p$ 的最小自然数 $x$ 
+ $a,p,b≤10^9$（$p$ 不要求为质数）
+ 复杂度为 $O(\sqrt{p} + log^2p)$，$log^2p$ 是约分和求公约数产生的

```text
#include <bits/stdc++.h>
#define int long long
using namespace std;
int fpow(int a, int b, int p)
{
	int sum = 1;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) sum = sum * a % p;
	return sum;
}
int bsgs(int a, int b, int p)
{
	map<int, int>hash;
	hash.clear();
	int m = sqrt(p) + 1;
	for (int i = 1; i <= m; i++)
		b = b * a % p, hash[b] = i;
	int tt = fpow(a, m, p);
	for (int i = 1, res = 1; i <= m; i++)
	{
		res = res * tt % p;
		if (hash.find(res) != hash.end()) return (i * m - hash[res] + p) % p;
	}
	return -1;
}
void exgcd(int a, int b, int& x, int& y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int inv(int a, int b)
{
	int X0, Y0;
	exgcd(a, b, X0, Y0);
	return (X0 % b + b) % b;
}
int exbsgs(int a, int b, int p)
{
	if (b == 1 || p == 1) return 0;
	int d, cnt = 0, res = 1;
	while ((d = __gcd(a, p)) != 1)
	{
		if (b % d) return -1;
		cnt++;
		b /= d;
		p /= d;
		res = res * a / d % p;
		if (res == b) return cnt;
	}
	int ans = bsgs(a, b * inv(res, p) % p, p);
	if (ans == -1) return -1;
	return ans + cnt;
}
signed main()
{
	while(1)
	{
		int a , b , p;
		cin >> a >> p >> b;
		if(!a && !b && !p) return 0;
		int ans = exbsgs(a % p , b % p , p);
		if(~ans) cout << ans << '\n';
		else cout << "No Solution\n";
	}
	return 0;
}
```

