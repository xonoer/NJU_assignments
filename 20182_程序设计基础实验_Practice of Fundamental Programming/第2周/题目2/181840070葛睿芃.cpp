#include <bits/stdc++.h> 
using namespace std;
struct TNode{
	int num;
	TNode *next[10];
};
TNode* head=NULL;
void insert_at_root(int x){ //在树根插入数字 
	TNode *p=new TNode;
	p->num=x;
	p->next[0]=head;
	for(int i=1;i<10;i++) p->next[i]=NULL;
	head=p;
	
}
void insert_after(TNode*node, int x,int y){//在x后插入y 
	if(node==NULL) return;
	if(node->num==x){
		for(int i=0;i<10;i++){
			if(node->next[i]==NULL){
				TNode *p=new TNode;
				p->num=y;
				for(int j=0;j<10;j++) p->next[j]=NULL;
				node->next[i]=p;
				break;
			}
		}
	}
	else {
		for(int j=0;j<10;j++) insert_after(node->next[j],x,y);
	}
}
void delete_node(TNode *node,int x){ //删除叶子节点 
	if (node==head&&head->num==x&&head->next[0]==NULL){
		TNode *p=head;
		head=NULL;
		delete p;
		return;
		
	}
	for(int k=0;k<10;k++){
		if(node->next[k]!=NULL&&node->next[k]->num==x&&node->next[k]->next[0]==NULL){
			TNode *p=node->next[k];
			for (int t=k+1;t<10;t++){
				node->next[t-1]=node->next[t];
			}
			node->next[9]=NULL;
			delete p;
		}
	
		else if(node->next[k]!=NULL){
			delete_node(node->next[k],x);
		}
	}
		
}

void print(TNode *node,int n){ //递归输出 
	if(n==0) return;
	cout<<node->num<<" ";
	for(int i=0;i<10;i++){
		if(node->next[i]!=NULL) print(node->next[i],n-1);
	}
	if(node==head) cout<<endl;
}

int main(){
	string s;  
	int x, y;
	while (cin >> s) {
		if(s=="insert_at_root"){
			cin>>x;
			insert_at_root(x);
		}
		else if(s=="insert_after"){
			cin>>x>>y;
			insert_after(head,x,y);
		}
		else if(s=="delete"){
			cin>>x;
			delete_node(head,x);
		}
		else if(s=="print"){
			cin>>x;
			print(head,x);
		}
	}
	return 0;
} 
