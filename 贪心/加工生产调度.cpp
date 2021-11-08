
#include<bits/stdc++.h>
#define ios std::ios::sync_with_stdio(false)
#define rep(i,a,n) for (int i=a;i<=n;i++)
#define per(i,n,a) for (int i=n;i>=a;i--)
#define repp(i,a,b) for(int i=a;i<b;i++)
#define mm(a,n) memset(a, n, sizeof(a))
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define il inline
#define int long long
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define pi 3.14159265358979323
#define SZ(x) ((ll)(x).size())
#define debug(x) 		cout<<#x<<": "<<x<<endl;
#define debug2(x,y)     cout<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl;
#define debug3(x,y,z)   cout<<#x<<": "<<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl;
#define debug4(a,b,c,d) cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
using namespace std;
const ll INF (0x3f3f3f3f3f3f3f3fll);
const int inf (0x3f3f3f3f);
template<typename T>void read(T &res){bool flag=false;char ch;while(!isdigit(ch=getchar()))(ch=='-')&&(flag=true);
for(res=ch-48;isdigit(ch=getchar());res=(res<<1)+(res<<3)+ch - 48);flag&&(res=-res);}
template<typename T>void Out(T x){if(x<0)putchar('-'),x=-x;if(x>9)Out(x/10);putchar(x%10+'0');}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}
ll pow_mod(ll x,ll n,ll mod){ll res=1;while(n){if(n&1)res=res*x%mod;x=x*x%mod;n>>=1;}return res;}
ll fact_pow(ll n,ll p){ll res=0;while(n){n/=p;res+=n;}return res;}
ll mult(ll a,ll b,ll p){a%=p;b%=p;ll r=0,v=a;while(b){if(b&1){r+=v;if(r>p)r-=p;}v<<=1;if(v>p)v-=p;b>>=1;}return r;}
ll quick_pow(ll a,ll b,ll p){ll r=1,v=a%p;while(b){if(b&1)r=mult(r,v,p);v=mult(v,v,p);b>>=1;}return r;}
bool CH(ll a,ll n,ll x,ll t)
{ll r=quick_pow(a,x,n);ll z=r;for(ll i=1;i<=t;i++){r=mult(r,r,n);if(r==1&&z!=1&&z!=n-1)return true;z=r;}return r!=1;}
bool Miller_Rabin(ll n)
{if(n<2)return false;if(n==2)return true;if(!(n&1))return false;ll x=n-1,t=0;while(!(x&1)){x>>=1;t++;}
srand(time(NULL));ll o=8;for(ll i=0;i<o;i++){ll a=rand()%(n-1)+1;if(CH(a,n,x,t))return false;}return true;}
ll exgcd1(ll a,ll b,ll &x,ll &y){if(!b){x=1,y=0;return a;}ll t=exgcd1(b,a%b,y,x);y-=a/b*x;return t;}
ll get_inv(ll a,ll mod){ll x,y;ll d=exgcd1(a,mod,x,y);return d==1?(x%mod+mod)%mod:-1;}
void exgcd(ll a,ll b ,ll &x,ll &y){if(!b){x=1,y=0;return;}exgcd(b,a%b,x,y);ll t=x;x=y,y=t-(a/b)*y;}
ll INV(ll a,ll b){ll x,y;return exgcd(a,b,x,y),(x%b+b)%b;}
ll crt(ll x,ll p,ll mod){return INV(p/mod,mod)*(p/mod)*x;}
ll FAC(ll x,ll a,ll b)
{if(!x)return 1;ll ans=1;for(ll i=1;i<=b;i++)if(i%a)ans*=i,ans%=b;
ans=pow_mod(ans,x/b,b);for(ll i=1;i<=x%b;i++)if(i%a)ans*=i,ans%=b;return ans*FAC(x/a,a,b)%b;}
ll C(ll n,ll m,ll a,ll b)
{ll N=FAC(n,a,b),M=FAC(m,a,b),Z=FAC(n-m,a,b),sum=0,i;for(i=n;i;i=i/a)sum+=i/a;
for(i=m;i;i=i/a)sum-=i/a;for(i=n-m;i;i=i/a)sum-=i/a;return N*pow_mod(a,sum,b)%b*INV(M,b)%b*INV(Z,b)%b;}
ll exlucas(ll n,ll m,ll p)
{ll t=p,ans=0,i;for(i=2;i*i<=p;i++){ll k=1;while(t%i==0){k*=i,t/=i;}
ans+=crt(C(n,m,i,k),p,k),ans%=p;}if(t>1)ans+=crt(C(n,m,t,t),p,t),ans%=p;return ans % p;}
/*
int prime[100010],minprime[100010] , phi[100010];
int euler(int n)
{int c=0,i,j;phi[1]=1;for(i=2;i<=n;i++){if(!minprime[i])prime[++c]=i,minprime[i]=i,phi[i]=i-1;
for(j=1;j<=c&&i*prime[j]<=n;j++){minprime[i*prime[j]]=prime[j];if(i%prime[j]==0)
{phi[i*prime[j]]=phi[i]*prime[j];break;}else phi[i*prime[j]]=phi[i]*(prime[j]-1);}}return c;}
struct Tree{ll l,r,sum,lazy,maxn,minn;}tree[100000];
il void push_up(ll rt)
{tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
tree[rt].maxn=max(tree[rt<<1].maxn,tree[rt<<1|1].maxn);
tree[rt].minn=min(tree[rt<<1].minn,tree[rt<<1|1].minn);}
il void push_down(ll rt , ll length)
{if(tree[rt].lazy){tree[rt<<1].lazy+=tree[rt].lazy;tree[rt<<1|1].lazy+=tree[rt].lazy;
tree[rt<<1].sum+=(length-(length>>1))*tree[rt].lazy;tree[rt<<1|1].sum+=(length>>1)*tree[rt].lazy;
tree[rt<<1].minn+=tree[rt].lazy;tree[rt<<1|1].minn+=tree[rt].lazy;
tree[rt<<1].maxn+=tree[rt].lazy;tree[rt<<1|1].maxn+=tree[rt].lazy;tree[rt].lazy=0;}}
il void build(ll l , ll r , ll rt , ll *aa)
{tree[rt].lazy=0;tree[rt].l=l;tree[rt].r=r;if(l==r)
{tree[rt].sum=aa[l];tree[rt].minn=tree[rt].sum;tree[rt].maxn=tree[rt].sum;return;}
ll mid=(l+r)>>1;build(l,mid,rt<<1,aa);build(mid+1,r,rt<<1|1,aa);push_up(rt);}
il void update_range(ll L , ll R , ll key , ll rt)
{if(tree[rt].r<L||tree[rt].l>R)return;if(L<=tree[rt].l&&R>=tree[rt].r){tree[rt].sum+=(tree[rt].r-tree[rt].l+1)*key;
tree[rt].minn+=key;tree[rt].maxn+=key;tree[rt].lazy+=key;return;}push_down(rt,tree[rt].r-tree[rt].l+1);
ll mid=(tree[rt].r+tree[rt].l)>>1;if(L<=mid)update_range(L,R,key,rt << 1);
if(R>mid)update_range(L,R,key,rt << 1 | 1);push_up(rt);}
il ll query_range(ll L, ll R, ll rt)
{if(L<=tree[rt].l&&R>=tree[rt].r){return tree[rt].sum;}push_down(rt,tree[rt].r-tree[rt].l+1);
ll mid=(tree[rt].r+tree[rt].l)>>1;ll ans=0;if(L<=mid)ans+=query_range(L,R,rt << 1);
if(R>mid)ans+=query_range(L,R,rt << 1 | 1);return ans;}
il ll query_min(ll L,ll R,ll rt)
{if(L<=tree[rt].l&&R>=tree[rt].r){return tree[rt].minn;}push_down(rt,tree[rt].r-tree[rt].l+1);
ll mid=(tree[rt].r+tree[rt].l)>>1;ll ans=(0x3f3f3f3f3f3f3f3fll);if(L<=mid)ans=min(ans,query_min(L,R,rt << 1));
if(R>mid)ans=min(ans,query_min(L,R,rt << 1 | 1));return ans;}
il ll query_max(ll L, ll R, ll rt)
{if(L<=tree[rt].l&&R>=tree[rt].r){return tree[rt].maxn;}push_down(rt,tree[rt].r-tree[rt].l+1);
ll mid=(tree[rt].r+tree[rt].l)>>1;ll ans=-(0x3f3f3f3f3f3f3f3fll);if(L<=mid)ans=max(ans,query_max(L,R,rt << 1));
if(R>mid)ans=max(ans,query_max(L,R,rt << 1 | 1));return ans;}
namespace linear_seq{
typedef vector<ll> VI;const ll N=1e5+10,mod = 1e9 + 7;
ll Rx[N],Ba[N],_c[N],_md[N];VI Md;
ll PMD(ll a,ll b){ll Rx=1;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)Rx=Rx*a%mod;a=a*a%mod;}return Rx;}
void MUL(ll *a,ll *b,ll k){repp(i,0,k+k)_c[i]=0;repp(i,0,k)if(a[i])repp(j,0,k)_c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
for(ll i=k+k-1;i>=k;i--)if(_c[i])repp(j,0,SZ(Md))_c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
repp(i,0,k)a[i]=_c[i];}ll Solve(ll n,VI a,VI b){ll ans=0,pnt=0,k=a.size();assert(SZ(a)==SZ(b));
repp(i,0,k)_md[k-1-i]=-a[i];_md[k]=1;Md.clear();repp(i,0,k)if(_md[i]!=0)Md.push_back(i);repp(i,0,k)Rx[i]=Ba[i]=0;
Rx[0]=1;while((1ll<<pnt)<=n)pnt++;for(ll p=pnt;p>=0;p--){MUL(Rx,Rx,k);if((n>>p)&1){for(ll i=k-1;i>=0;i--)Rx[i+1]=Rx[i];
Rx[0]=0;repp(j,0,SZ(Md))Rx[Md[j]]=(Rx[Md[j]]-Rx[k]*_md[Md[j]])%mod;}}repp(i,0,k) ans=(ans+Rx[i]*b[i])%mod;
if(ans<0)ans+=mod;return ans;}VI BM(VI s){VI C(1,1),B(1,1);ll L=0,m=1,b=1;repp(n,0,SZ(s)){ll d=0;
repp(i,0,L+1)d=(d+(ll)C[i]*s[n-i])%mod;if(d==0)++m;else if(2*L<=n){VI T=C;ll c=mod-d*PMD(b,mod-2)%mod;
while(SZ(C)<SZ(B)+m)C.push_back(0);repp(i,0,SZ(B))C[i+m]=(C[i+m]+c*B[i])%mod;L=n+1-L;B=T;b=d;m=1;}
else{ll c=mod-d*PMD(b,mod-2)%mod;while(SZ(C)<SZ(B)+m)C.push_back(0);
repp(i,0,SZ(B))C[i+m]=(C[i+m]+c*B[i])%mod;++m;}}return C;}
ll Gao(VI a,ll n){VI c=BM(a);c.erase(c.begin());n--;repp(i,0,SZ(c))c[i]=(mod-c[i])%mod;
return Solve(n,c,VI(a.begin(),a.begin()+SZ(c)));}};
*/
const int N = 3e5 + 10;
struct Edge{
	int nex , to;
}edge[N << 1];
int head[N] , TOT;
void add_edge(int u , int v)
{
	edge[++ TOT].nex = head[u] ;
	edge[TOT].to = v;
	head[u] = TOT;
}
struct node{
	int a , b , id;
}p[N] , q[N];
vector<node>vec1 , vec2;
bool cmp1(node x , node y)
{
	return x.a < y.a;
}
bool cmp2(node x , node y)
{
	return x.b > y.b;
}
signed main()
{
	ios;
	int n , m;
	cin >> n;
	rep(i , 1 , n) cin >> p[i].a;
	rep(i , 1 , n) cin >> p[i].b , p[i].id = i;
	rep(i , 1 , n)
	{
		if(p[i].a <= p[i].b) vec1.pb(p[i]);
		else vec2.pb(p[i]);
	}
	sort(all(vec1) , cmp1) , sort(all(vec2) , cmp2);
	int cnt = 0;
	for(auto j : vec1) q[++ cnt] = j;
	for(auto j : vec2) q[++ cnt] = j; 
	int ta = q[1].a , tb = q[1].a + q[1].b;
	rep(i , 2 , n)
	{
		ta += q[i].a;
		tb = max(ta , tb) + q[i].b;
	}
	cout << tb << '\n';
	rep(i , 1 , n) cout << q[i].id << " ";
	cout << '\n';
	return 0;
}
