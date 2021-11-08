#include <bits/stdc++.h>
#define int long long
#define ll long long
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, b, a) for (int i = b; i >= a; i--)
#define go(u) for (int i = head[u], v = e[i].v; i; i = e[i].nx, v = e[i].v)
using namespace std;
const int N = (1 << 17) + 5;
int n , mod;
inline int add(int x, int y)
{
	return 0ll + x + y >= mod ? 0ll + x + y - mod : x + y;
}
inline int dec(int x, int y)
{
	return x - y < 0 ? x - y + mod : x - y;
}
inline int mul(int x, int y)
{
	return 1ll * x * y - 1ll * x * y / mod * mod;
}
int ksm(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		(y & 1) ? res = mul(res, x) : 0;
	return res;
}
const double Pi = acos(-1.0);
struct cp
{
	double x, y;
	inline cp() {}
	inline cp(double xx, double yy) : x(xx), y(yy) {}
	inline cp operator+(const cp &b) const
	{
		return cp(x + b.x, y + b.y);
	}
	inline cp operator-(const cp &b) const
	{
		return cp(x - b.x, y - b.y);
	}
	inline cp operator*(const cp &b) const
	{
		return cp(x * b.x - y * b.y, x * b.y + y * b.x);
	}
	inline cp operator*(const double &b) const
	{
		return cp(x * b, y * b);
	}
	inline cp operator~() const
	{
		return cp(x, -y);
	}
} w[2][N];
int r[21][N], ifac[N], lg[N], inv[N];
double iv[21];
void Pre()
{
	iv[0] = 1;
	rep(Dd, 1, 17)
	{
		rep(i, 0, (1 << Dd) - 1) r[Dd][i] = (r[Dd][i >> 1] >> 1) | ((i & 1) << (Dd - 1));
		lg[1 << Dd] = Dd, iv[Dd] = iv[Dd - 1] * 0.5;
	}
	inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
	rep(i, 2, 131072) inv[i] = mul(mod - mod / i, inv[mod % i]), ifac[i] = mul(ifac[i - 1], inv[i]);
	for (int i = 1, Dd = 0; i < 131072; i <<= 1, ++Dd)
		rep(k, 0, i - 1)
		w[1][i + k] = cp(cos(Pi * k * iv[Dd]), sin(Pi * k * iv[Dd])),
		              w[0][i + k] = cp(cos(Pi * k * iv[Dd]), -sin(Pi * k * iv[Dd]));
}
int lim, Dd;
void FFT(cp *A, int ty)
{
	rep(i, 0, lim - 1) if (i < r[Dd][i]) swap(A[i], A[r[Dd][i]]);
	cp t;
	for (int mid = 1; mid < lim; mid <<= 1)
		for (int j = 0; j < lim; j += (mid << 1))
			rep(k, 0, mid - 1)
			A[j + k + mid] = A[j + k] - (t = w[ty][mid + k] * A[j + k + mid]),
			                 A[j + k] = A[j + k] + t;
	if (!ty)
		rep(i, 0, lim - 1) A[i] = A[i] * iv[Dd];
}
void MTT(int *a, int *b, int len, int *c)
{
	static cp f[N], g[N], p[N], q[N];
	lim = len, Dd = lg[lim];
	rep(i, 0, len - 1) f[i] = cp(a[i] >> 16, a[i] & 65535), g[i] = cp(b[i] >> 16, b[i] & 65535);
	rep(i, len, lim - 1) f[i] = g[i] = cp(0, 0);
	FFT(f, 1), FFT(g, 1);
	rep(i, 0, lim - 1)
	{
		cp t, f0, f1, g0, g1;
		t = ~f[i ? lim - i : 0], f0 = (f[i] - t) * cp(0, -0.5), f1 = (f[i] + t) * 0.5;
		t = ~g[i ? lim - i : 0], g0 = (g[i] - t) * cp(0, -0.5), g1 = (g[i] + t) * 0.5;
		p[i] = f1 * g1, q[i] = f1 * g0 + f0 * g1 + f0 * g0 * cp(0, 1);
	}
	FFT(p, 0), FFT(q, 0);
	rep(i, 0, lim - 1) c[i] = ((((ll)(p[i].x + 0.5) % mod << 16) % mod << 16) + ((ll)(q[i].x + 0.5) << 16) + ((ll)(q[i].y + 0.5))) % mod;
}
void calc(int *a, int *b, int n, int k)
{
	static int f[N], g[N], h[N], sum[N], isum[N];
	int len = 1;
	while (len <= n + n) len <<= 1;
	rep(i, 0, n) f[i] = mul(a[i], mul(ifac[i], ifac[n - i]));
	for (int i = n - 1; i >= 0; i -= 2) f[i] = mod - f[i];
	int t = dec(k, n);
	rep(i, 0, n + n) g[i] = add(i, t);
	sum[0] = g[0];
	rep(i, 1, n + n) sum[i] = mul(sum[i - 1], g[i]);
	isum[n + n] = ksm(sum[n + n], mod - 2);
	per(i, n + n, 1) isum[i - 1] = mul(isum[i], g[i]);
	rep(i, 1, n + n) g[i] = mul(isum[i], sum[i - 1]);
	g[0] = isum[0];
	rep(i, n + 1, len - 1) f[i] = 0;
	rep(i, n + n + 1, len - 1) g[i] = 0;
	MTT(f, g, len, h);
	int res = 1, p1 = k - n, p2 = k;
	rep(i, p1, p2) res = 1ll * res * i % mod;
	res = dec(res, 0);
	rep(i, 0, n) g[i] = (0ll + mod + p1 + i) % mod;
	sum[0] = g[0];
	rep(i, 1, n) sum[i] = mul(sum[i - 1], g[i]);
	isum[n] = ksm(sum[n], mod - 2);
	per(i, n, 1) isum[i - 1] = mul(isum[i], g[i]);
	rep(i, 1, n) g[i] = mul(isum[i], sum[i - 1]);
	g[0] = isum[0];
	for (int i = 0; i <= n; p2 = add(p2, 1), ++i)
		b[i] = mul(h[i + n], res), res = mul(res, mul(g[i], p2 + 1));
}
int solve(int bl)
{
	static int a[N], b[N], c[N];
	int s = 0;
	for (int p = bl; p; p >>= 1)
		++s;
	a[0] = 1, --s;
	int qwq = ksm(bl, mod - 2);
	for (int p = 0; s >= 0; --s)
	{
		if (p)
		{
			calc(a, b, p, p + 1);
			rep(i, 0, p) a[p + i + 1] = b[i];
			a[p << 1 | 1] = 0;
			calc(a, b, p << 1, mul(p, qwq));
			p <<= 1;
			rep(i, 0, p) a[i] = mul(a[i], b[i]);
		}
		if (bl >> s & 1)
		{
			rep(i, 0, p) a[i] = mul(a[i], (1ll * bl * i + p + 1) % mod);
			p |= 1, a[p] = 1;
			rep(i, 1, p) a[p] = mul(a[p], (1ll * bl * p + i) % mod);
		}
	}
	int res = 1;
	rep(i, 0, bl - 1) res = mul(res, a[i]);
	return res;
}
int GetFac(int n)
{
	int s = sqrt(n), res = solve(s);
	rep(i, s * s + 1, n) res = mul(res, i);
	return res;
}
int Fac(int n)
{
	Pre();
	if (n > mod - 1 - n)
	{
		int res = ksm(GetFac(mod - 1 - n), mod - 2);
		return (mod - 1 - n) & 1 ? res : mod - res;
	}
	return GetFac(n);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
	{
		cin >> n >> mod;
		cout << Fac(n) << '\n';
	}
	return 0;
}
