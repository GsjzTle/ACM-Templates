```text
#define ull unsigned long long
using namespace std;
const int N = 2e5 + 10;
const int Max = 2e6 + 10;
const ull base = 131;
struct Hash{
	ull power[Max] , hash1[Max] , hash2[Max];
	ull get_hash1(int l , int r){
		return hash1[r] - hash1[l - 1] * power[r - l + 1];
	}
	ull get_hash2(int l , int r){
		return hash2[l] - hash2[r + 1] * power[r - l + 1];
	}
	void hash_init(int n)
	{
		power[1] = base;
		for(int i = 2 ; i <= n ; i ++) power[i] = power[i - 1] * base;
	}
	void hash_pre(char *s)
	{
		int len = strlen(s + 1);
		hash1[1] = s[1] - 'a' + 1 , hash1[len + 1] = '\0';
		for(int i = 2 ; i <= len ; i ++) hash1[i] = hash1[i - 1] * base + s[i] - 'a' + 1;
	}
	void hash_suf(char *s) 
	{
		int len = strlen(s + 1);
		hash2[len] = s[len] - 'a' + 1 , hash2[len + 1] = '\0';
		for(int i = len - 1 ; i >= 1 ; i --) hash2[i] = hash2[i + 1] * base + s[i] - 'a' + 1;
	}
}ha;
char s[N];
unordered_map<int , int>mp;
signed main()
{
	ha.hash_init(N - 10);
	int n , res = 0;
	cin >> n;
	while(n --)
	{
		cin >> s + 1;
		int len = strlen(s + 1);
		ha.hash_pre(s); // 千万别传成 s + 1
		int now = ha.get_hash1(1 , len);
		if(!mp.count(now)) res ++ , mp[now] ++ ; 
	}
	cout << res << '\n';
	return 0;

```

