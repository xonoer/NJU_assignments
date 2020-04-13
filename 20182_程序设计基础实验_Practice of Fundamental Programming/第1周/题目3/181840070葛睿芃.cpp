#include <iostream>
#include <cstdio>
int hash1[2333];	//�����ϣ����¡�������� 
int hash2[2467];
int hash3[2659];
int hash4[2789];
int hash5[3067];
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
//�����ϣ���� 
int ht_num1(char *s){    //��ϣ���� 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%2333;
	}
	return res;
}
int ht_num2(char *s){    //��ϣ���� 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%2467;
	}
	return res;
}
int ht_num3(char *s){    //��ϣ���� 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%2659;
	}
	return res;
}
int ht_num4(char *s){    //��ϣ���� 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%2789;
	}
	return res;
}
int ht_num5(char *s){    //��ϣ���� 
	int res=0;
	for (char*c=s;*c!='\0';++c){
		res=res*26+(*c-'a');
		res=res%3067;
	}
	return res;
}
//�����ϣ�������� 
void ht_insert(char *s){   //���뵥�� 
	hash1[ht_num1(s)]=1;
	hash2[ht_num2(s)]=1;
	hash3[ht_num3(s)]=1;
	hash4[ht_num4(s)]=1;
	hash5[ht_num5(s)]=1;
}
bool ht_find(char *s){ //Ѱ�ҵ��� 
	if (hash1[ht_num1(s)]==0) return false;
	else if (hash2[ht_num2(s)]==0) return false;
	else if (hash3[ht_num3(s)]==0) return false;
	else if (hash4[ht_num4(s)]==0) return false;
	else if (hash5[ht_num5(s)]==0) return false;
	else return true;
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
