```text
#include<bits/stdc++.h>
using namespace std;
int main(){
	int c=0;
	do{
		if(c)printf("#%d AC\n",c);
		++c;
		system("./make");
		system("./1");
		system("./2");
	}while(!system("diff 1.out 2.out"));
	printf("#%d WA\n",c);
	return 0;
}
```

