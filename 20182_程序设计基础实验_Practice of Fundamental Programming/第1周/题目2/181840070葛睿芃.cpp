#include <iostream>
#include <cstdio>
struct Node{			//·À³åÍ»Á´±í 
	char dic[201];
	Node *next;
};
Node* hash[2333];     //¹þÏ£±í 
using namespace std;
void to_lower(char *s){ //×ª»»ÎªÐ¡Ð´ 
	for(char *c=s;*c!='\0';c++){
		if(*c>='A'&&*c<='Z') *c=*c-'A'+'a';
	}
}
bool str_equal(char *s1,char *s2){  //ÅÐ¶Ï×Ö·û´®ÏàµÈ 
	int i;
	for(i=0;s1[i];i++){
		if(s1[i]!=s2[i]) return false;
	}
	if(s2[i]) return false;
	return true;
}
void str_copy(char *s1,char *s2){  //×Ö·û´®¸´ÖÆ 
	int i;
	for (i=0;s1[i];i++){
		s2[i]=s1[i];
	}
	s2[i]='\0';
}
int ht_num(char *s){    //¹þÏ£º¯Êý 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%2333;
	}
	return res;
}
void ht_insert(char *s){   //¼ÓÈëµ¥´Ê 
	int num=ht_num(s);
	Node* p=new Node;
	str_copy(s,p->dic);
	p->next=hash[num];
	hash[num]=p;
}
bool ht_find(char *s){ //Ñ°ÕÒµ¥´Ê 
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
		word[end-init]='\0'; //È¡³öµ¥´Ê 
		ht_insert(word);
		init=end+1;
	}
	while(cin>>tar){ //Ñ­»·ÅÐ¶Ï 
		to_lower(tar);
		if (ht_find(tar)) cout<<"True"<<endl;
		else cout<<"False"<<endl;
	}
	return 0;
} 
