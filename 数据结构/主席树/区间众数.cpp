#include<bits/stdc++.h>
#define rep(i,a,n) for (int i=a;i<=n;i++)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define int long long
using namespace std;

const int N = 5e5 + 10;

struct Tree{
	int l , r , sum;
}tree[N << 5];

int root[N] , Cnt;

void update(int l , int r , int pre , int &now , int pos)
{
	tree[++ Cnt] = tree[pre];
	
	tree[Cnt].sum ++ ;
	
	now = Cnt;
	
	if(l == r) return ;
	
	int mid = l + r >> 1;
	
	if(pos <= mid) update(l , mid , tree[pre].l , tree[now].l , pos);
	
	else update(mid + 1 , r , tree[pre].r , tree[now].r , pos);
}

int query(int l , int r , int L , int R , int len)
{
	if(l == r) return l;
	
	int mid = l + r >> 1;
	
	int Lsum = tree[tree[R].l].sum - tree[tree[L].l].sum;
	
	int Rsum = tree[tree[R].r].sum - tree[tree[L].r].sum;
	
	int ans = 0;
	
	/*
	
	这里其实取 max 其实是可以改成 return 的
	
	因为如果 Lsum > len , 那么 Rsum 就必然小于 len 
	
	*/
	
	if(Lsum > len) ans = max(ans , query(l , mid , tree[L].l , tree[R].l , len));
	
	if(Rsum > len) ans = max(ans , query(mid + 1 , r , tree[L].r , tree[R].r , len));
	
	return ans;
}

int a[N];

vector<int>vec;

int get_id(int x)
{
	return lower_bound(all(vec) , x) - vec.begin() + 1;
}

signed main()
{
	ios::sync_with_stdio(false);
	
	cin.tie(0) , cout.tie(0);
	
	int n , m;
	
	cin >> n >> m;
	
	rep(i , 1 , n) cin >> a[i] , vec.pb(a[i]);
	
	sort(all(vec));
	
	vec.erase(unique(all(vec)) , vec.end());
	
	int nn = vec.size();
	
	rep(i , 1 , n) a[i] = get_id(a[i]) , update(1 , nn , root[i - 1] , root[i] , a[i]);
	
	while(m --)
	{
		int l , r;
		
		cin >> l >> r;
		
		int res = query(1 , nn , root[l - 1] , root[r] , (r - l + 1) / 2);
		
		if(res) res = vec[res - 1];
		
		cout << res << '\n';
	}
	
	return 0;
} 
