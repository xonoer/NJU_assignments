//ʹ��ѭ���ṹ��n�Ľ׳�
#include <iostream>
using namespace std;
int main(){
	int n;
	cout<<"����һ��������:"<<endl; 
	cin>>n;
	long long ans=1;        //���ǵ���̫��ʱ�ᳬ��int�ͷ�Χ�����Կ��˸�long long 
	for(int i=2;i<=n;i++) ans*=i;
	cout<<n<<"�Ľ׳��ǣ�"<<ans<<endl;
	return 0;
} 
