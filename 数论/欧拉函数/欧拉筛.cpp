int prime[1000010] , minprime[1000010] , phi[1000010];
int euler(int n)
{
	int c = 0 , i , j;
	phi[1] = 1;
	for(i = 2 ; i <= n ; i ++)
	{
		if(!minprime[i]) prime[++ c] = i , minprime[i] = i , phi[i] = i - 1;
		for(j = 1 ; j <= c && i * prime[j] <= n ; j ++)
		{
			minprime[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	return c;
}
