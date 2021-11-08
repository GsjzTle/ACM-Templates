#include<bits/stdc++.h>
#define rep(i , a , b) for(int i = a ; i <= b ; i ++)
#define ll long long
using namespace std;
struct Linear_Basis
{
	ll b[63], nb[63], tot; //bΪ���Ի� , nb������� K С���ֵ , totΪ nb Ԫ�ظ���
	bool zero = false;  // �ж��Ƿ���� 0 
	void Init() //��ʼ��
	{
		tot = 0;
		zero = false;
		memset(b, 0, sizeof(b));
		memset(nb, 0, sizeof(nb));
	}
	void Ins(ll x) //����
	{
		for(int i = 62; i >= 0; i--)
		{
			if(x & (1ll << i))
			{
				if(!b[i])
				{
					b[i] = x;
					return;
				}
				x ^= b[i];
			}
		}
		// x ����ʧ�� 
		zero = true;
		return;
	}
	bool Fin(ll x) //��֤������
	{
		if(x == 0 && b[0]) return 1;
		for(int i = 62; i >= 1; i--)
		{
			int j = i - 1;
			if(x & (1 << j))
			{
				x ^= b[i];
				if(!x) return 1;
			}
		}
		return 0;
	}
	ll Max() //�����ֵ
	{
		ll res = 0;
		for(int i = 62; i >= 0; i--)
		{
			res = max(res, res ^ b[i]);
		}
		return res;
	}
	ll Min() //����Сֵ
	{
		if(zero) return 0;
		for(int i = 0; i <= 62; i++)
		{
			if(b[i]) return b[i];
		}
	}
	ll Query_Max(ll x) // ��� x �ɵõ������ֵ 
	{  
        ll res = x;
        for(int i = 62 ; i >= 0 ; i --){
            res = max(res , res ^ b[i]);
        }
        return res;
    }
    ll Query_Min(ll x) // ��� x �ɵõ�����Сֵ 
	{ 
        ll res = x;
        for(int i = 0 ; i <= 62 ; i ++){
            if(b[i]) res ^= b[i];
        }
        return res;
    }
	void Rebuild()
	{
		for(int i = 62; i >= 0; i--)
		{
			if(b[i] == 0) continue;
			for(int j = i - 1; j >= 0; j--)
			{
				if(b[j] == 0) continue;
				if(b[i] & (1ll << j)) b[i] ^= b[j];
			}
		}
		for(int i = 0; i <= 62; i++)
		{
			if(b[i]) nb[tot++] = b[i];
		}
	}
	ll Kth_Max(ll k) //��K��
	{
		if(zero) k--;
		ll res = 0;
		if(k == 0) return 0;
		if(k >= (1ll << tot)) return -1;
		for(int i = 62; i >= 0; i--)
		{
			if(k & (1ll << i)) res ^= nb[i];
		}
		return res;
	}
} LB;
ll a[55];
signed main()
{
	LB.Init();
	ll n , ma = 0;
	cin >> n;
	rep(i , 1 , n) cin >> a[i] , LB.Ins(a[i]);
	cout << LB.Max() << '\n'; 
	return 0;
}
