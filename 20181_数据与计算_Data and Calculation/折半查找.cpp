#include <bits/stdc++.h>
#define MAX 10
using namespace std;
struct student{
		string name;
		int num;
	};
	student a[MAX];    //����ṹ�壬���������ѧ�� 

void Findit(int x,int y,int k){   //���ֲ��ң��ݹ��㷨 
	int m=(x+y)/2;
	if(x>y){
		cout<<"Number Error, not found!"<<endl;  //�ݹ�߽�1��δ�ҵ��� 
		return ;
	}
	if(a[m].num==k) {                           //�ݹ�߽�2���ҵ��� 
		cout<<"The name of number "<<a[m].num<<" is "<<a[m].name<<endl;
	}
	else if(a[m].num>k) Findit(x,m-1,k);        //���ݴ�С�ݹ���� 
	else Findit(m+1,y,k);
}
/* 
   ����������ԣ�����ѧ�����������ĳ��������������У�������ͼû����ʾ�������ش�˵���� 

*/
int main(){
	
	for(int i=0;i<MAX;i++){            //����������ѧ�� 
		cout<<"Input name and number of student NO."<<i+1<<endl;
		cin>>a[i].name;
		cin>>a[i].num; 
	}
	for(int i=MAX-1;i>0;i--)             //ð�����򣬴�С��������ѧ�Ŵ���������� 
	for(int j=0;j<i;j++){
		if(a[j].num>a[j+1].num) swap(a[j],a[j+1]);
	}
	int k;
	cout<<"**Please input student number:"<<endl;
	cin>>k;
	Findit(0,MAX-1,k);
	return 0;
	
} 
