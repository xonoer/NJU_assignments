#include <iostream>
#define NUM 9 
using namespace std;
void sort(int a[],int num){     //����ѡ�����򷨣����������� 
	for (int i=num-1;i>=0;i--){
		int max=a[0];
		int k=0;
		int temp;
		for (int j=1;j<=i;j++){
			if(a[j]>max){
				k=j;
				max=a[j];
			}
		}
		temp=a[i];
		a[i]=a[k];
		a[k]=temp;
	}
}

int main(){
	int a[NUM]={5,3,4,2,6,7,1,8,9};
	cout<<"Ŀ������Ϊ��5 3 4 2 6 7 1 8 9 "<<endl;
	sort(a,NUM);
	cout<<"��λ��Ϊ:"<<a[NUM/2]<<endl;
	return 0; 
}
