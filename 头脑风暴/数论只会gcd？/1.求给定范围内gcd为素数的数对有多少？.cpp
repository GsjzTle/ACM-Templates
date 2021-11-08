#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e7 + 10;
int n , prime[N] , minprime[N] , phi[N];
ll sum[N];
int euler(int n)
{
	int c=0,i,j;
	phi[1]=1;
	for(i=2; i<=n; i++)
	{
		if(!minprime[i])prime[++c]=i,minprime[i]=i,phi[i]=i-1;
		for(j=1; j<=c&&i*prime[j]<=n; j++)
		{
			minprime[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(int i = 1 ; i <= n ; i ++) sum[i] = sum[i - 1] + phi[i];
	return c;
}
signed main()
{
	ll res = 0;
	cin >> n;
	int cnt = euler(n);
	for(int i = 1 ; i <= cnt ; i ++) res += 2 * sum[n / prime[i]] - 1;
	cout << res << '\n';
	return 0;
}
