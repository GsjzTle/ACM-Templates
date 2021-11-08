int far[N] , dep[N];
int find(int x)
{
	if(x == far[x]) return x;
	return find(far[x]);
}
void Union(int x , int y)
{
	int tx = find(x) , ty = find(y);
	if(tx == ty) return ; 
	if(dep[tx] < dep[ty]) far[tx] = ty;
	else 
	{
		far[ty] = tx;
		if(dep[tx] == dep[ty]) dep[tx] ++ ;
	}
}
void init(int n)
{
	for(int i = 1 ; i <= n ; i ++) far[i] = i , dep[i] = 1;
}
