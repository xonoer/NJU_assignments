#include <iostream>
#define NUM 9 
using namespace std;
void sort(int a[], int num){
	if(num%2){ 
	for (int i=0;i<num;i++){
		int small=0, big=0;
		for (int j=0;j<num;j++){
			if(a[j]<a[i]) small++;
			if(a[j]>a[i]) big++;
		}
		if(small==big) cout<<"中位数为"<<a[i]<<endl;;
	}
	return ;
	}
	else {
	for (int i=0;i<num;i++){
		int small=0, big=0;
		for (int j=0;j<num;j++){
			if(a[j]<a[i]) small++;
			if(a[j]>a[i]) big++;
		}
		if(((small+1)==big)||(small==(big+1))) cout<<"中位数为"<<a[i]<<endl;;
	
	
}
return;
    }
}

int main(){
	int a[NUM]={5,3,4,2,6,7,1,8,9};
	int b[NUM+1]={0,2,5,4,1,3,9,6,8,7 }; 
	cout<<"目标数组为：5 3 4 2 6 7 1 8 9 "<<endl;
	sort(a,NUM);
	cout<<"目标数组为：0 2 5 4 1 3 9 6 8 7"<<endl;
	sort(b,NUM+1); 
	return 0; 
}
