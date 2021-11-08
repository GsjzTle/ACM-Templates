#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
struct Tree{
	int l , r , far , dep;
}tree[N << 5];
int root[N] , Ctot;
int n , m;
void build(int &now , int l , int r)
{
	now = ++ Ctot;
	if(l == r)
	{
		tree[now].far = l , tree[now].dep = 1;
		return ;
	}
	int mid = l + r >> 1;
	build(tree[now].l , l , mid);
	build(tree[now].r , mid + 1 , r);
}
void update(int l , int r , int pre , int &now , int pos , int F)
{
	tree[++ Ctot] = tree[pre];
	now = Ctot;
	if(l == r)
	{
		tree[now].far = F;
		tree[now].dep = tree[pre].dep;
		return ;
	}
	int mid = l + r >> 1;
	if(pos <= mid) update(l , mid , tree[pre].l , tree[now].l , pos , F);
	else update(mid + 1 , r , tree[pre].r , tree[now].r , pos , F);
}
int query(int l , int r , int rt , int pos)
{
	if(l == r) return rt;
	int mid = l + r >> 1;
	if(pos <= mid) return query(l , mid , tree[rt].l , pos);
	else return query(mid + 1 , r , tree[rt].r , pos);
}
int find(int x , int i)
{
	int x_id = query(1 , n , root[i] , x);
	int F = tree[x_id].far;
	if(F == x) return F;
	return find(F , i); // ��·��ѹ�� 
}
void Union(int x , int y , int i)
{
	int tx = find(x , i);
	int ty = find(y , i);
	if(tx == ty) return ;
	int tx_id = query(1 , n , root[i] , tx); // �ҵ����ȶ�Ӧ�ı�� 
	int ty_id = query(1 , n , root[i] , ty); // ��ʱ�� root[i] ���� root[i - 1] 
	int dep_x = tree[tx_id].dep , dep_y = tree[ty_id].dep;	
	if(dep_x > dep_y) swap(tx_id , ty_id) , swap(tx , ty);
	update(1 , n , root[i - 1] , root[i] , tx , ty); // Ϊ root[i] �����·�֧ 
	if(dep_x == dep_y) 
	{
		ty_id = query(1 , n , root[i] , ty);
		tree[ty_id].dep ++ ;
	}
}
signed main()
{
	cin >> n >> m;
	build(root[0] , 1 , n);
	for(int i = 1 ; i <= m ; i ++)
	{
		int op , a , b , k;
		cin >> op;
		if(op == 1)
		{
			cin >> a >> b;
			root[i] = root[i - 1];
			Union(a , b , i);
		}
		else if(op == 2)
		{
			cin >> k;
			root[i] = root[k];
		}
		else if(op == 3)
		{
			cin >> a >> b;
			root[i] = root[i - 1];
			if(find(a , i) == find(b , i)) puts("1");
			else puts("0");
		}
	}
	return 0;
}
