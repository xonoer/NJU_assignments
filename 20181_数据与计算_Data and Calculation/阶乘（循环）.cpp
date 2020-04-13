//使用循环结构求n的阶乘
#include <iostream>
using namespace std;
int main(){
	int n;
	cout<<"输入一个正整数:"<<endl; 
	cin>>n;
	long long ans=1;        //考虑到数太大时会超过int型范围，所以开了个long long 
	for(int i=2;i<=n;i++) ans*=i;
	cout<<n<<"的阶乘是："<<ans<<endl;
	return 0;
} 
