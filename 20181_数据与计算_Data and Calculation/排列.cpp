//�㷨����˼�룺������Ȼ���в��϶Ե�Ԫ�صķ������������ 
#include <iostream>
using namespace std;
int a[1000];               //�������������洢���� 
void Swap_a(int k1,int k2){//�������� 
	int temp;
	temp=a[k1];
	a[k1]=a[k2];
	a[k2]=temp;
}
/*
   num��ʾ���ڲ�����Ŀ�������±꣬n��ʾ������Ԫ������
   һ��1-n��ȫ�����������ĵ�һλ��������������n-1Ϊ���ֱ�Ե������Բ���
 ��n-1�������У�Ȼ��̶���һλ�������Ԫ������ͬ�İ취���Ϳ��Բ�������
 ��ȫ�����ˡ� 
*/ 
void output(int num,int n){//�ݹ飺���ȫ���� 
	if(num==n){            //1���߽粿�֣�������ɺ��һ����� 
		for(int i=0;i<n;i++) cout<<a[i]<<" ";
		cout<<endl;
		return ;
	}
	for (int i=num;i<n;i++){//2���ݹ鲿�֣� num֮ǰ��λ���Ѿ�ȫ���̶� 
	
		Swap_a(num,i);      //ѭ����num�ֱ�������ÿһλ���Ե� 
		output(num+1,n);    //�ݹ����������num�����λ��ȫ���� 
		Swap_a(num,i);      //�ݹ�������ص�ԭ����״̬��׼����λ����һλ�Ե� 
	}
}
int main(){
	int n;
	cout<<"��������������"<<endl;
	cin>>n;
	for (int i=0;i<n;i++){
		a[i]=i+1;
	}
	cout<<"����Ϊ����1-"<<n<<"��ȫ���У�"<<endl; 
	output(0,n);
	return 0;
} 
