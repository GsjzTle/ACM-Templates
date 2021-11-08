#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace PhoRho { //Phollard-Rho
    ll gcd(ll a, ll b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    ll fastpow(ll x, ll p, ll mod) {
        ll ans = 1;
        while (p) {
            if (p & 1) ans = (__int128) ans * x % mod;
            x = (__int128) x * x % mod;
            p >>= 1;
        }
        return ans;
    }
    ll max_factor;
    bool MillerRabin(ll x, ll b) {
        ll k = x - 1;
        while (k) {
            ll cur = fastpow(b, k, x);
            if (cur != 1 && cur != x - 1) return false;
            if ((k & 1) == 1 || cur == x - 1) return true;
            k >>= 1;
        }
        return true;
    }
    bool prime(ll x) {
        if (x == 46856248255981ll || x < 2) return false;
        if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251) return true;
        return MillerRabin(x, 2) && MillerRabin(x, 3) && MillerRabin(x, 7) && MillerRabin(x, 61);
    }
    ll f(ll x, ll c, ll n) {
        return ((__int128) x * x + c) % n;
    }
    ll PRho(ll x) {
        ll s = 0, t = 0, c = 1ll * rand() * (x - 1) + 1;
        int stp = 0, goal = 1;
        ll val = 1;
        for (goal = 1;; goal <<= 1, s = t, val = 1) {
            for (stp = 1; stp <= goal; ++stp) {
                t = f(t, c, x);
                val = (__int128) val * abs(t - s) % x;
                if (stp % 127 == 0) {
                    ll d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            ll d = gcd(val, x);
            if (d > 1) return d;
        }
    }
    void fac(ll x) {
        if (x <= max_factor || x < 2) {
            return;
        }
        if (prime(x)) {
            max_factor = max_factor > x ? max_factor : x;
            return;
        }
        ll p = x;
        while (p >= x) p = PRho(x);
        while ((x % p == 0)) x /= p;
        fac(x);
        fac(p);
    }
    ll divide(ll n) {
        srand((unsigned) time(0));
        max_factor = 0;
        fac(n);
        return max_factor;
    }
}
namespace DLP {
    const int N = 1111111;
    ll fastpow(ll a, ll n) { //快速幂
        ll res = 1;
        while (n > 0) {
            if (n & 1) res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
    ll fastpow(ll a, ll n, ll p) { //针对特别大的数的快速幂
        ll res = 1;
        a %= p;
        while (n > 0) {
            if (n & 1) res = (__int128) res * a % p;
            a = (__int128) a * a % p;
            n >>= 1;
        }
        return res;
    }
    int prime[N], ptot;
    bool ispr[N];
    struct pt {
        ll p;
        int c;
    };
    void getprime() { //获取10^6以内的质数
        memset(ispr, 1, sizeof(ispr));
        for (int i = 2; i < N; ++i) {
            if (ispr[i]) prime[++ptot] = i;
            for (int j = 1; j <= ptot && prime[j] <= (N - 1) / i; ++j) {
                ispr[i * prime[j]] = 0;
                if (!i % prime[j]) break;
            }
        }
    }
    bool cmp(pt x, pt y) {
        return x.p < y.p;
    }
    void findorg(vector<pt> &v, ll num) { //num分解质因数
        while (num >= N) {   //大于10^6的部分，每次用Pho-Rho算法找出最大的一个质因子，然后除掉即可
            ll maxf = PhoRho::divide(num);
            int cnt = 0;
            while (num % maxf == 0) {
                cnt++;
                num = num / maxf;
            }
            v.push_back((pt) {maxf, cnt});
        }
        if (ptot == 0) getprime();
        for (int i = 1; i <= ptot && prime[i] <= num; ++i) { //剩下的就是不大于10^6的质因子了，直接暴力枚举
            if (num % prime[i] == 0) {
                int cnt = 0;
                while (num % prime[i] == 0) {
                    cnt++;
                    num /= prime[i];
                }
                v.push_back((pt) {prime[i], cnt});
            }
        }
        if (num > 1) v.push_back((pt) {num, 1});
        sort(v.begin(), v.end(), cmp);
    }
    int getorg(ll p, ll phi, vector<pt> &v) { //获取ord
        for (int k = 2;; k++) {
            int flag = 1;
            for (int i = 0; i < (int) v.size(); ++i) {
                if (fastpow(k, phi / v[i].p, p) == 1) {
                    flag = 0;
                    break;
                }
            }
            if (flag) return k;
        }
    }
    ll BSGS(ll a, ll b, ll p, ll mod) { //BSGS模板
        a %= mod , b %= mod;
        if (b == 1) return 0;
        if (a == 0) {
            if (b == 0) return 1;
            else return -1;
        }
        ll t = 1;
        int m = int(sqrt(1.0 * p) + 1);
        ll base = b;
        unordered_map<ll, ll> vis;
        for (int i = 0; i < m; ++i) {
            vis[base] = i;
            base = (__int128) base * a % mod;
        }
        base = fastpow(a, m, mod);
        ll now = t;
        for (int i = 1; i <= m + 1; ++i) {
            now = (__int128) now * base % mod;
            if (vis.count(now)) return i * m - vis[now];
        }
        return -1;
    }
    ll getksi(ll g, ll h, ll p, ll c, ll n, ll mod) {  //得到合并后的解集，然后上BSGS
        vector<ll> pi;
        ll tp = 1;
        for (int i = 0; i <= c; ++i) {
            pi.push_back(tp);
            tp *= p;
        }
        ll gq = fastpow(g, pi[c - 1], mod);
        ll inv = 0;
        tp = 1;
        for (int i = c - 1; i >= 0; --i) {
            ll tx = tp * BSGS(gq, fastpow((__int128) h * fastpow(g, pi[c] - inv, mod) % mod, pi[i], mod), p, mod);
            inv += tx;
            tp *= p;
        }
        return inv;
    }
    ll exgcd(ll a, ll b, ll &x, ll &y) { //exgcd模板
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
    ll getinv(ll a, ll p) { //扩欧求逆元
        if (a == 0) return 1;
        ll x, y;
        exgcd(a, p, x, y);
        return (x % p + p) % p;
    }
    ll gcd(ll x, ll y) { //gcd
        if (x % y == 0) return y;
        return gcd(y, x % y);
    }
    ll ExgcdSolve(ll a, ll b, ll c, ll &x, ll &y) { //求解exgcd
        ll d;
        if (c % (d = gcd(a, b))) return -1;
        a /= d;
        b /= d;
        c /= d;
        exgcd(a, b, x, y);
        x = (__int128) x * c % b;
        while (x <= 0) x += b;
        return x;
    }
    ll crt(vector<ll> ksi, vector<pt> v) { //crt
        int sz = v.size();
        ll M = 1, ans = 0;
        vector<ll> m;
        for (int i = 0; i < sz; ++i) {
            m.push_back(fastpow(v[i].p, v[i].c));
            M *= m[i];
        }
        for (int i = 0; i < sz; ++i) {
            ll Mi = M / m[i];
            ans = ((__int128) ans + (__int128) Mi * getinv(Mi, m[i]) * ksi[i]) % M;
        }
        if (ans < 0) ans += M;
        return ans;
    }
    ll getx(ll h, ll g, ll N, ll mod, vector<pt> &v) { //获取解集，然后用crt合并
        vector<ll> ksi;
        for (pt tp:v) {
            ll tg = fastpow(g, N / fastpow(tp.p, tp.c), mod);
            ll th = fastpow(h, N / fastpow(tp.p, tp.c), mod);
            ksi.push_back(getksi(tg, th, tp.p, tp.c, N, mod));
        }
        return crt(ksi, v);
    }
    ll solve(ll a, ll b, ll p) { //求解a^x = b(mod p)的最小解
        if (b == 1) return 0;
        ll phiP = p - 1;
        vector<pt> v;
        findorg(v, phiP);
        int rt = getorg(p, phiP, v);
        ll x = getx(a, rt, phiP, p, v);
        ll y = getx(b, rt, phiP, p, v);
        ll aa = 0, bb = 0;
        if (x == 0) {
            if (y == 0) return 1;
            else if (y == 1) return 0;
            else return -1;
        } else return ExgcdSolve(x, phiP, y, aa, bb);
    }
};
signed main()
{
	ll p , a , b;
	cin >> p >> a >> b;
	ll ans = DLP::solve(a , b , p);
	if(~ans) cout << ans << '\n';
	else cout << "no solution\n";
	return 0;
} 
