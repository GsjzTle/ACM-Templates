#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define ll long long
const int N = 1e7 + 10;
int vis[N] , p[N] , pn , mu[N] , sum[N];
void init(int n)
{
	mu[1] = 1;
	rep(i , 2 , n)
	{
		if(!vis[i])
		{
			p[++ pn] = i;
			mu[i] = -1;
		}
		for(int j = 1 ; j <= pn && i * p[j] <= n ; j ++)
		{
			vis[i * p[j]] = 1;
			if(i % p[j] == 0)
			{
				mu[i * p[j]] = 0;
				break;
			}
			else mu[i * p[j]] =- mu[i];
		}
	}
	rep(i , 1 ,pn) for(int j = p[i] ; j <= n ; j += p[i]) sum[j] += mu[j / p[i]];
	rep(i , 1 , n) sum[i] += sum[i - 1];
}
ll solve(int n , int m)
{
	int mi = min(n , m);
	ll ans = 0;
	for(int l = 1 , r = 0 ; l <= mi ; l = r + 1)
	{
		r = min(n / (n / l) , m / (m / l));
		ans += 1ll * (n / l) * (m / l) * (sum[r] - sum[l - 1]);
	}
	return ans;
}
signed main()
{
	init(10000000);
	int T = 1 , n , m;
	cin >> T;
	while(T --) 
	{
		cin >> n >> m;
		cout << solve(n , m) << '\n';
	}
	return 0;
}
