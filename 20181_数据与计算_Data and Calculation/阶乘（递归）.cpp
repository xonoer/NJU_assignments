//ʹ�õݹ�ṹ��n�Ľ׳�
#include <iostream>
using namespace std;
long long f(int n){
	if(n==1||n==2) return n;
	else return f(n-1)*n;
} 
int main(){
	int n;
	cout<<"����һ����������"<<endl;
	cin>>n;
	cout<<n<<"�Ľ׳�Ϊ"<<f(n)<<endl; 
	return 0;
} 
