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
		if(c % g != 0) {      // �޽�
			cout << "-1\n";
			continue ;
		}
		exgcd(a , b , x , y);
		x *= c / g , y *= c / g;
		ll p = b / g , q = a / g , k;
		if(x < 0) k = ceil((1.0 - x) / p) , x += p * k , y -= q * k;  //�� x ��ߵ���С������
		else k = (x - 1) / p , x -= p * k , y += q * k;				  //�� x ���͵���С������
		if(y > 0) 	 //����������
		{
			cout << (y - 1) / q + 1 << " ";  	//�� y ���� 1 �ķ�������Ϊ��ĸ���
			cout << x << " ";					//��ǰ�� x ��Ϊ��С������ x
			cout << (y - 1) % q + 1 << " "; 	//�� y ȡ����С������
			cout << x + (y - 1) / q * p << " ";	//�� x ���������
			cout << y << '\n';					//�ؽ⼴Ϊ y ���ֵ
		}
		else 		//��������
		{
			cout << x << " ";								  //��ǰ�� x ��Ϊ��С�������� x 
			cout << y + q * (ll)ceil((1.0 - y) / q) << '\n';  //��y��ߵ�������
		}
	}
	return 0;
}
