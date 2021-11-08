```text
#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct Tree
{
	ll l,r,sum,lazy,maxn,minn;
} tree[N << 2];
void push_up(ll rt)
{
	tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
	tree[rt].maxn=max(tree[rt<<1].maxn,tree[rt<<1|1].maxn);
	tree[rt].minn=min(tree[rt<<1].minn,tree[rt<<1|1].minn);
}
void push_down(ll rt , ll len)
{
	if(tree[rt].lazy)
	{
		tree[rt<<1].lazy+=tree[rt].lazy,tree[rt<<1|1].lazy+=tree[rt].lazy;
		tree[rt<<1].sum+=(len-(len>>1))*tree[rt].lazy,tree[rt<<1|1].sum+=(len>>1)*tree[rt].lazy;
		tree[rt<<1].minn+=tree[rt].lazy,tree[rt<<1|1].minn+=tree[rt].lazy;
		tree[rt<<1].maxn+=tree[rt].lazy,tree[rt<<1|1].maxn+=tree[rt].lazy;
		tree[rt].lazy=0;
	}
}
void build(ll l , ll r , ll rt , ll *aa)
{
	tree[rt].lazy=0;
	tree[rt].l=l;
	tree[rt].r=r;
	if(l==r)
	{
		tree[rt].sum=aa[l];
		tree[rt].minn=tree[rt].sum;
		tree[rt].maxn=tree[rt].sum;
		return;
	}
	ll mid=(l+r)>>1;
	build(l,mid,rt<<1,aa);
	build(mid+1,r,rt<<1|1,aa);
	push_up(rt);
}
void update_range(ll L , ll R , ll key , ll rt)
{
	if(tree[rt].r<L||tree[rt].l>R)return;
	if(L<=tree[rt].l&&R>=tree[rt].r)
	{
		tree[rt].sum+=(tree[rt].r-tree[rt].l+1)*key;
		tree[rt].minn+=key;
		tree[rt].maxn+=key;
		tree[rt].lazy+=key;
		return;
	}
	push_down(rt,tree[rt].r-tree[rt].l+1);
	ll mid=(tree[rt].r+tree[rt].l)>>1;
	if(L<=mid)update_range(L,R,key,rt << 1);
	if(R>mid)update_range(L,R,key,rt << 1 | 1);
	push_up(rt);
}
ll query_range(ll L, ll R, ll rt)
{
	if(L<=tree[rt].l&&R>=tree[rt].r)
	{
		return tree[rt].sum;
	}
	push_down(rt,tree[rt].r-tree[rt].l+1);
	ll mid=(tree[rt].r+tree[rt].l)>>1;
	ll ans=0;
	if(L<=mid)ans+=query_range(L,R,rt << 1);
	if(R>mid)ans+=query_range(L,R,rt << 1 | 1);
	return ans;
}
ll query_min(ll L,ll R,ll rt)
{
	if(L<=tree[rt].l&&R>=tree[rt].r)
	{
		return tree[rt].minn;
	}
	push_down(rt,tree[rt].r-tree[rt].l+1);
	ll mid=(tree[rt].r+tree[rt].l)>>1;
	ll ans=(0x3f3f3f3f3f3f3f3fll);
	if(L<=mid)ans=min(ans,query_min(L,R,rt << 1));
	if(R>mid)ans=min(ans,query_min(L,R,rt << 1 | 1));
	return ans;
}
ll query_max(ll L, ll R, ll rt)
{
	if(L<=tree[rt].l&&R>=tree[rt].r)
	{
		return tree[rt].maxn;
	}
	push_down(rt,tree[rt].r-tree[rt].l+1);
	ll mid=(tree[rt].r+tree[rt].l)>>1;
	ll ans=-(0x3f3f3f3f3f3f3f3fll);
	if(L<=mid)ans=max(ans,query_max(L,R,rt << 1));
	if(R>mid)ans=max(ans,query_max(L,R,rt << 1 | 1));
	return ans;
}
int a[N];
signed main()
{
	ios::sync_with_stdio(false); 
	int n , m;
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i ++) cin >> a[i];
	build(1 , n , 1 , a);
	while(m --)
	{
		int op ;
		cin >> op;
		if(op == 1)
		{
			int l , r , k;
			cin >> l >> r >> k;
			update_range(l , r , k , 1);
		}
		else
		{
			int l , r;
			cin >> l >> r;
			cout << query_range(l , r , 1) << '\n';
		}
	}
	return 0;
}
```

