//算法基本思想：运用自然排列不断对调元素的方法组成新排列 
#include <iostream>
using namespace std;
int a[1000];               //这个程序用数组存储排列 
void Swap_a(int k1,int k2){//交换函数 
	int temp;
	temp=a[k1];
	a[k1]=a[k2];
	a[k2]=temp;
}
/*
   num表示正在操作的目标数组下标，n表示排列总元素数。
   一个1-n的全排列数，它的第一位数，与其他所有n-1为数分别对调，可以产生
 出n-1个新排列，然后固定第一位，后面的元素用相同的办法，就可以产生所有
 的全排列了。 
*/ 
void output(int num,int n){//递归：输出全排列 
	if(num==n){            //1）边界部分：排列完成后的一次输出 
		for(int i=0;i<n;i++) cout<<a[i]<<" ";
		cout<<endl;
		return ;
	}
	for (int i=num;i<n;i++){//2）递归部分： num之前的位数已经全部固定 
	
		Swap_a(num,i);      //循环：num分别与后面的每一位数对调 
		output(num+1,n);    //递归操作，即将num后面的位数全排列 
		Swap_a(num,i);      //递归结束，回到原来的状态，准备该位与下一位对调 
	}
}
int main(){
	int n;
	cout<<"请输入正整数："<<endl;
	cin>>n;
	for (int i=0;i<n;i++){
		a[i]=i+1;
	}
	cout<<"以下为所有1-"<<n<<"的全排列："<<endl; 
	output(0,n);
	return 0;
} 
