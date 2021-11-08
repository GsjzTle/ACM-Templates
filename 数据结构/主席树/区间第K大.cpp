#include<bits/stdc++.h>
#define rep(i,a,n) for (int i=a;i<=n;i++)
using namespace std;
const int N = 3e5 + 10;
struct Chairman_Tree
{
	int l , r , sum;
} tree[N << 5];
vector<int>vec;
int root[N] , a[N] , Ctot;
void update(int l , int r , int pre , int &now , int pos)
{
	tree[++ Ctot] = tree[pre];
	tree[Ctot].sum ++ ;
	now = Ctot;
	if(l == r) return ;
	int mid = l + r >> 1;
	if(pos <= mid) update(l , mid , tree[pre].l , tree[now].l , pos);
	else update(mid + 1 , r , tree[pre].r , tree[now].r , pos);
}
int query(int l , int r , int L , int R , int k)
{
	if(l == r) return l ;
	int mid = l + r >> 1;
	int cha = tree[tree[R].l].sum - tree[tree[L].l].sum;
	if(cha >= k) return query(l , mid , tree[L].l , tree[R].l , k);
	else return query(mid + 1 , r , tree[L].r , tree[R].r , k - cha);
}
int get_id(int x)
{
	return lower_bound(vec.begin() , vec.end() , x) - vec.begin() + 1;
}
void init()
{
	vec.clear();
	rep(i , 0 , Ctot) tree[i].sum = tree[i].l = tree[i].r = 0;
	Ctot = 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	int T = 1;
//	cin >> T;
	while(T --)
	{
		init();
		int n , m ;
		cin >> n >> m;
		rep(i , 1 , n)
		{
			cin >> a[i];
			vec.push_back(a[i]);
		}
		sort(vec.begin() , vec.end());
		vec.erase(unique(vec.begin() , vec.end()) , vec.end()) ;
		rep(i , 1 , n)
		update(1 , n , root[i - 1] , root[i] , get_id(a[i]));
		while(m --)
		{
			int l , r , k;
			cin >> l >> r >> k ;
			int pos = query(1 , n , root[l - 1] , root[r] , k);
			cout << vec[pos - 1] << '\n' ;
		}

	}
	return 0;
}

