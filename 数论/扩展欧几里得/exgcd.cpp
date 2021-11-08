#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void exgcd(ll a , ll b , ll &x , ll &y)
{
	if(!b){
		x = 1 , y = 0;
		return;
	}
	exgcd(b , a % b , x , y);
	ll t = x;
	x = y , y = t - (a / b) * y;
}
signed main()
{
	int T = 1;
	cin >> T;
	while(T --)
	{
		ll a , b , c , x = 0 , y = 0;
		cin >> a >> b >> c;
		ll g = __gcd(a , b);
		if(c % g != 0) {      // 无解
			cout << "-1\n";
			continue ;
		}
		exgcd(a , b , x , y);
		x *= c / g , y *= c / g;
		ll p = b / g , q = a / g , k;
		if(x < 0) k = ceil((1.0 - x) / p) , x += p * k , y -= q * k;  //将 x 提高到最小正整数
		else k = (x - 1) / p , x -= p * k , y += q * k;				  //将 x 降低到最小正整数
		if(y > 0) 	 //有正整数解
		{
			cout << (y - 1) / q + 1 << " ";  	//将 y 减到 1 的方案数即为解的个数
			cout << x << " ";					//当前的 x 即为最小正整数 x
			cout << (y - 1) % q + 1 << " "; 	//将 y 取到最小正整数
			cout << x + (y - 1) / q * p << " ";	//将 x 提升到最大
			cout << y << '\n';					//特解即为 y 最大值
		}
		else 		//无整数解
		{
			cout << x << " ";								  //当前的 x 即为最小的正整数 x 
			cout << y + q * (ll)ceil((1.0 - y) / q) << '\n';  //将y提高到正整数
		}
	}
	return 0;
}
