#include <iostream>
#include <cstring> 
#include <cstdio> 
using namespace std;
int tot=0;                             //tot代表称量总次数，初始为0，每次称量时，tot值会加1 ； 
void Findit (int n,int m){             //n代表总硬币数，m代表假币所在位置 
	int a[n];                          //用数组代表所有硬币； 
	memset(a,0,sizeof(a));             //初始化数组值为0； 
	a[m-1]=1;                          //将假币所在位置数组值设定为1； 
	if(n==1) cout<<"总次数："<<tot<<endl;     //只有一个硬币时，必为假币，输出总次数 
	if(n==2) {
		tot++;                         //称量开始 
		cout<<"第"<<tot<<"次:"<<endl; 
		if(a[0]==1) cout<<"第1堆有假币"<<endl; //检验两个硬币中的假币（把值为“1”看做天平翘起来） 
		else cout<<"第2堆有假币"<<endl;
		cout<<"总次数："<<tot<<endl;  //两个硬币一称， 结束 
		return;
	} 
	if(n>=3) {
		int n1,add1=0,add2=0,add3=0;
		if(n%3==2) n1=n/3+1;           //确定两个数量相同的硬币组 作为称量对象，数量为n1; 另一堆一定比n1多1或少1或相等 
		else n1=n/3;
		for (int i=0;i<n1;i++)
			add1+=a[i];
		for (int i=n1;i<2*n1;i++)
			add2+=a[i];
		for (int i=2*n1;i<n;i++)
			add3+=a[i];
		
		tot++;                             //称量开始 （称一次，翘起来的一堆重新分组，若相平，第三组重新分组） 
		cout<<"第"<<tot<<"次:"<<endl; 
		if(add1==1){                         //为方便，将所有数组对应位置值的和相加，为1则这一堆有假币 
			cout<<"第1堆有假币"<<endl;        //这三个if其实只需要一次称量判定 
			Findit(n1,m);
		}	
		if(add2==1){
			cout<<"第2堆有假币"<<endl;
			Findit(n1,m-n1);
		}
		if(add3==1){
			cout<<"第3堆有假币"<<endl;
			Findit(n-2*n1,m-2*n1);
		}		
	}
} 

int main(){
	int n,m;
	cout<<"输入两个数（第一个为硬币总数，第二个为假币所在位置）"<<endl;
	cin>>n>>m;
	Findit(n,m);

	return 0;
}



/*
注：程序不能给出最少次数，这和假币所在位置有关 
当硬币总数相同时，若假币位置不一样，可能称量次数就不一样。
如输入 100 1 时，只需称4次，而输入100 25 时，要称量5次 
*/
