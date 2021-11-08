int far[N] , size[N];
int find(int x)
{
	if(x == far[x]) return x;
	return far[x] = find(far[x]);
}
void Union(int x , int y)
{
	int tx = find(x) , ty = find(y);
	if(tx == ty) return ; 
	if(size[tx] > size[ty]) swap(tx , ty);
	far[tx] = ty , size[ty] += size[tx];
}
void init(int n)
{
	for(int i = 1 ; i <= n ; i ++) far[i] = i , size[i] = 1;
}
