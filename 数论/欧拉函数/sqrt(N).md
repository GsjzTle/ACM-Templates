```text
ll get_phi(ll n)
{
	ll ans = n;
	for(ll i = 2 ; i * i <= n ; i ++)
	{
		if(n % i == 0)
		{
			ans -= ans / i;
			while(n % i == 0) n /= i;
		}
	}
	if(n > 1) ans -= ans / n;
	return ans;
}
```

