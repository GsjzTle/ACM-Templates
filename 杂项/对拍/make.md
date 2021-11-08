```text
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define int long long
#define debug(x) cout << #x << " : " << x << '\n';
using namespace std;
const int N = 3e5 + 10;
int random(int n)
{
	return (long long)(rand() * rand()) % n;
}
int far[N] , vis[N];
int find(int x)
{
	if(x == far[x]) return x;
	return far[x] = find(far[x]);
}
map<pair<int , int> , int>mp;
signed main()
{
    freopen("make.out","w",stdout);
	srand((unsigned int)(time(0)));

	int n = random(5) + 3 , m = random(20) + 5;
	cout << n << " " << m << '\n';

	return 0;
}
```

