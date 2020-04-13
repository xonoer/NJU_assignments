#include <iostream>
#define NUM 9 
using namespace std;
void sort(int a[],int num){     //利用选择排序法，给数据排序 
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
	cout<<"目标数组为：5 3 4 2 6 7 1 8 9 "<<endl;
	sort(a,NUM);
	cout<<"中位数为:"<<a[NUM/2]<<endl;
	return 0; 
}
