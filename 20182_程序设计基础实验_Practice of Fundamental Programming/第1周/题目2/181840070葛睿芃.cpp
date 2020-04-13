#include <iostream>
#include <cstdio>
struct Node{			//����ͻ���� 
	char dic[201];
	Node *next;
};
Node* hash[2333];     //��ϣ�� 
using namespace std;
void to_lower(char *s){ //ת��ΪСд 
	for(char *c=s;*c!='\0';c++){
		if(*c>='A'&&*c<='Z') *c=*c-'A'+'a';
	}
}
bool str_equal(char *s1,char *s2){  //�ж��ַ������ 
	int i;
	for(i=0;s1[i];i++){
		if(s1[i]!=s2[i]) return false;
	}
	if(s2[i]) return false;
	return true;
}
void str_copy(char *s1,char *s2){  //�ַ������� 
	int i;
	for (i=0;s1[i];i++){
		s2[i]=s1[i];
	}
	s2[i]='\0';
}
int ht_num(char *s){    //��ϣ���� 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%2333;
	}
	return res;
}
void ht_insert(char *s){   //���뵥�� 
	int num=ht_num(s);
	Node* p=new Node;
	str_copy(s,p->dic);
	p->next=hash[num];
	hash[num]=p;
}
bool ht_find(char *s){ //Ѱ�ҵ��� 
	int num=ht_num(s);
	if (hash[num]==NULL) return false;
	else {
		for (Node* q=hash[num];q!=NULL;q=q->next){
			if(str_equal(s,q->dic)) return true;
		}
		return false;
	}
}
int main(){
	char art[9999];
	char tar[201];
	char word[201];
	FILE *fp=fopen("article.txt","r");
	fgets(art,9999,fp);
	to_lower(art); 
	int init=0;
	while(art[init]){
		int end=init;
		while(art[end]>='a'&&art[end]<='z') end++;
		for(int i=init;i<end;i++){
			word[i-init]=art[i];
		}
		word[end-init]='\0'; //ȡ������ 
		ht_insert(word);
		init=end+1;
	}
	while(cin>>tar){ //ѭ���ж� 
		to_lower(tar);
		if (ht_find(tar)) cout<<"True"<<endl;
		else cout<<"False"<<endl;
	}
	return 0;
} 
