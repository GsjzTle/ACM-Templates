const int N = 5e5 + 10;
struct Ctree{
	int l , r , mi = inf;
}tree[N * 40];
int root[N] , Ctot;
void push_up(int rt)
{
	tree[rt].mi = min(tree[tree[rt].l].mi , tree[tree[rt].r].mi);
}
void update(int l , int r , int pre , int &now , int pos , int val)
{
	tree[++ Ctot] = tree[pre];
	now = Ctot;
	if(l == r)
	{
		tree[now].mi = val;
		return ;
	}
	int mid = l + r >> 1;
	if(pos <= mid) update(l , mid , tree[pre].l , tree[now].l , pos , val);
	else update(mid + 1 , r , tree[pre].r , tree[now].r , pos , val);
	push_up(now);
}
int query(int l , int r , int rt , int L , int R)
{
	if(L <= l && r <= R) return tree[rt].mi;
	int mid = l + r >> 1 , mi = inf;
	if(L <= mid) mi = min(mi , query(l , mid , tree[rt].l , L , R));
	if(R >  mid) mi = min(mi , query(mid + 1 , r , tree[rt].r , L , R));
	return mi; 
}
int n , m , a[N] , pre[N];
vector<int>vec;
int get(int x){
	return lower_bound(all(vec) , x) - vec.begin() + 1;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	cin >> n ;
	rep(i , 1 , n) cin >> a[i] , vec.pb(a[i]);
	sort(all(vec));
	vec.erase(unique(all(vec)) , vec.end());
	rep(i , 1 , n) 
	{
		a[i] = get(a[i]);
		if(!pre[a[i]]) pre[a[i]] = -i; 
		if(pre[a[i]] > 0) 
		{
			int t = 0;
			update(1 , n , root[i - 1] , t , pre[a[i]] , inf);
			update(1 , n , t , root[i] , i , pre[a[i]]);
		}
		else update(1 , n , root[i - 1] , root[i] , i , pre[a[i]]);
		pre[a[i]] = i; 
	}
	cin >> m;
	while(m --)
	{
		int l , r;
		cin >> l >> r;
		int mi = query(1 , n , root[r] , l , r);
		if(mi >= l) cout << 0 << '\n';
		else cout << vec[a[abs(mi)] - 1] << '\n';
	}
	return 0;
}
