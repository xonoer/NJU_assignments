#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct Node{
	int num;
	Node* next;
};
Node* head=NULL; 
void insert_at_beginning(int x){ //在表头插入数字 
	Node *p=new Node;
	p->num=x;
	p->next=head;
	head=p;
}
void insert_at_ending(int x){ //在表尾插入数字 
	Node *p=new Node;
	p->num=x;
	p->next=NULL;
	Node *tail=head;
	while(tail->next!=NULL){
		tail=tail->next;
	}
	tail->next=p;
}
void insert_after(int x,int y){ //在x后插入y 
	Node *q;
	for(q=head;q!=NULL;q=q->next){
		if(q->num==x) break;
	} 
	if(q!=NULL){
		Node *p=new Node;
		p->num=y;
		p->next=q->next;
		q->next=p;
	}
}
void delete_node(int x){ //删除节点 
	if(head->num==x){
		Node *p=head;
		head=head->next;
		delete p;
	}
	for(Node *q=head;q->next!=NULL;q=q->next){
		if(q->next->num==x){
			Node *p=q->next;
			q->next=p->next;
			delete p;
			return;
		}
	}
}
void print(int n){ //输出前n个数字 
	Node *q=head;
	int i=0;
	while(q!=NULL){
		if(i==n) break;
		cout<<q->num<<" ";
		q=q->next;
		i++;
	}
	cout<<endl;
}
void reverse_print(Node *node,int n){ //递归逆序输出 
	if(node->next!=NULL){
		reverse_print(node->next,n-1);
	}	
	if(n!=0){
		cout<<node->num<<" ";
	}
	if(node==head){
		cout<<endl;
	}
}
int main(){
	char com[25];
	int x,y;
	while(cin>>com){
		if(strcmp(com,"insert_at_beginning")==0){
			cin>>x;
			insert_at_beginning(x);
		}
		else if(strcmp(com,"insert_at_ending")==0){
			cin>>x;
			insert_at_ending(x);
		}
		else if(strcmp(com,"insert_after")==0){
			cin>>x>>y;
			insert_after(x,y);
		}
		else if(strcmp(com,"delete")==0){
			cin>>x;
			delete_node(x);
		}
		else if(strcmp(com,"print")==0){
			cin>>x;
			print(x);
		}
		else if(strcmp(com,"reverse_print")==0){
			cin>>x;
			reverse_print(head,x);
		}
		else{
			cout<<"Error! Invalid command!"<<endl;
		} 
	}
	return 0;
} 
