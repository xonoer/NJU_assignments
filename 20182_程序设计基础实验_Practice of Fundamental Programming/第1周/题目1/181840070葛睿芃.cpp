#include <iostream>
#include <cstdio>
using namespace std;
void to_lower(char *s){ //转换为小写 
	for(char *c=s;*c!='\0';c++){
		if(*c>='A'&&*c<='Z') *c=*c-'A'+'a';
	}
}
bool str_equal(char *s1,char *s2){ //判断字符串相等 
	int i;
	for(i=0;s1[i];i++){
		if(s1[i]!=s2[i]) return false;
	}
	if(s2[i]) return false;
	return true;
}
int main(){
	char art[2001];
	char tar[201];
	char word[201];
	FILE *fp=fopen("article.txt","r");
	fgets(art,2001,fp);
	cin>>tar;
	to_lower(art); 
	to_lower(tar);
	int init=0;
	while(art[init]){
		int end=init;
		while(art[end]>='a'&&art[end]<='z') end++;
		for(int i=init;i<end;i++){
			word[i-init]=art[i]; //取出单词 
		}
		word[end-init]='\0';
		if(str_equal(word,tar)){
			cout<<"True"<<endl;
			return 0;
		}
		init=end+1;
	}
	cout<<"False"<<endl;
	return 0;
} 
