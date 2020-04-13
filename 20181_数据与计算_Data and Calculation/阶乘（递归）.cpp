//使用递归结构求n的阶乘
#include <iostream>
using namespace std;
long long f(int n){
	if(n==1||n==2) return n;
	else return f(n-1)*n;
} 
int main(){
	int n;
	cout<<"输入一个正整数："<<endl;
	cin>>n;
	cout<<n<<"的阶乘为"<<f(n)<<endl; 
	return 0;
} 
