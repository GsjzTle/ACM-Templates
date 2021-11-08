#include<bits/stdc++.h>
#define rep(i , a , n) for (int i = a ; i <= n ; i ++)
using namespace std;

template<typename T>void read(T &res)
{
	bool flag = false;
	char ch;
	while(!isdigit(ch = getchar()))(ch == '-') && (flag = true);
	for(res = ch - 48 ; isdigit(ch = getchar()); res = (res << 1) + (res << 3) + ch - 48);
	flag && (res =- res);
}

const int N = 1e6 + 10;

struct Chairman_Tree
{
	int l , r , sum;
} tree[N << 5];

vector<int>vec;

int root[N] , a[N] , Ctot , last[N]; //last[i]��ʾ��һ�γ��� i ��λ��

int n , m;

void update(int l , int r , int pre , int &now , int pos , int val)
{
	tree[++ Ctot] = tree[pre];

	tree[Ctot].sum += val;

	now = Ctot;

	if(l == r) return ;

	int mid = l + r >> 1;

	if(pos <= mid) update(l , mid , tree[pre].l , tree[now].l , pos , val);

	else update(mid + 1 , r , tree[pre].r , tree[now].r , pos , val);
}

int query(int l , int r , int L , int id)
{
	if(L <= l) return tree[id].sum;

	int mid = l + r >> 1;

	if(L <= mid) return query(l , mid , L , tree[id].l) + tree[tree[id].r].sum;

	return query(mid + 1 , r , L , tree[id].r);
}

int get_id(int x)
{
	return lower_bound(vec.begin() , vec.end() , x) - vec.begin() + 1;
}

signed main()
{

	read(n);

	rep(i , 1 , n)
	{
		read(a[i]);

		vec.push_back(a[i]);
	}

	sort(vec.begin() , vec.end());

	vec.erase(unique(vec.begin() , vec.end()) , vec.end()) ;

	rep(i , 1 , n)
	{
		if(last[a[i]])
		{
			int help = 0;

			update(1 , n , root[i - 1] , help , last[a[i]] , -1);

			/*
			���� help ��ת�� root[i - 1] , �ڰ� help ���ϵ� last[a[i]] --
			�ٰ� help ת�Ƹ� root[i] , ͬʱ�� root[i] ���ϵ� i ++
			*/

			update(1 , n , help , root[i] , i , 1);
		}

		else update(1 , n , root[i - 1] , root[i] , i , 1);

		last[a[i]] = i;
	}

	read(m);

	while(m --)
	{
		int l , r;

		read(l) , read(r);

		cout << query(1 , n , l , root[r]) << '\n';
	}

	return 0;
}
