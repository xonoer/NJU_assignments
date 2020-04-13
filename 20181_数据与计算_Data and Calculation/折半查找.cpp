#include <bits/stdc++.h>
#define MAX 10
using namespace std;
struct student{
		string name;
		int num;
	};
	student a[MAX];    //定义结构体，存放姓名，学号 

void Findit(int x,int y,int k){   //二分查找，递归算法 
	int m=(x+y)/2;
	if(x>y){
		cout<<"Number Error, not found!"<<endl;  //递归边界1（未找到） 
		return ;
	}
	if(a[m].num==k) {                           //递归边界2（找到） 
		cout<<"The name of number "<<a[m].num<<" is "<<a[m].name<<endl;
	}
	else if(a[m].num>k) Findit(x,m-1,k);        //根据大小递归查找 
	else Findit(m+1,y,k);
}
/* 
   经过程序测试，输入学号如果是乱序的程序仍能正常运行，不过截图没有显示出来，特此说明！ 

*/
int main(){
	
	for(int i=0;i<MAX;i++){            //输入姓名、学号 
		cout<<"Input name and number of student NO."<<i+1<<endl;
		cin>>a[i].name;
		cin>>a[i].num; 
	}
	for(int i=MAX-1;i>0;i--)             //冒泡排序，从小到大排列学号存放于数组中 
	for(int j=0;j<i;j++){
		if(a[j].num>a[j+1].num) swap(a[j],a[j+1]);
	}
	int k;
	cout<<"**Please input student number:"<<endl;
	cin>>k;
	Findit(0,MAX-1,k);
	return 0;
	
} 
