#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include "account.h"

using namespace std;

Account::Account(FILE* pfile){	//（调试通过）构造函数，读取账号密码与剩余次数。 
	char Username[21];
	char Password[13];
	char Tryagain[3];
	fgets(Username,21,pfile);
	fgets(Password,13,pfile);
	fgets(Tryagain,3,pfile);
	for(int i=0;Username[i];i++){
		if(Username[i]=='\n') {
			Username[i]='\0';
			break;
		}
	}
	for(int i=0;Password[i];i++){
		if(Password[i]=='\n') {
			Password[i]='\0';
			break;
		}
	}
	account.username=Username;
	account.password=Password;
	string t=Tryagain;
	account.try_again=atoi(t.c_str());
} 

int Account::login(string name,string pass){//（调试通过）登录判断 
	if(name!=account.username) return 1;
	if(account.try_again==0) return 3;
	if(name==account.username&&pass==account.password) {
		
		account.try_again=3;	
		return 0;
	}
	if(pass!=account.password) {
		account.try_again--;
		return 2;
	} 
} 

bool Account::change_oldConfirm(string pass){
	return(pass==account.password);
}

 

int Account::change_newLegal(string pass){	
	if(pass.size()>12) return 1;
	if(!has_num(pass)) return 2;
	if(!has_cap(pass)) return 2;
	if(!has_low(pass)) return 2;
	return 0;
}

bool Account::change_newConsist(string pass1,string pass2){
	return(pass1==pass2);
} 

void Account::changePassword(string pass){
	account.password=pass;
}

string Account::getUsername(){
	return account.username;
}

int Account::getTrynum(){
	return account.try_again;
} 

void Account::unfreeze(){
	account.try_again=3;
}

void Account::saveToFile(FILE* pfile){
	string Name(account.username);
	Name+='\n';
	fputs(Name.c_str(),pfile);
	string Pass(account.password);
	Pass+='\n';
	fputs(Pass.c_str(),pfile);
	string Num=to_string(account.try_again);
	fputs(Num.c_str(),pfile);
}

Account::~Account(){//析构函数 
	return;
}

bool has_num(string ch){
	for (string::iterator it=ch.begin();it!=ch.end();it++){
		if((*it)>='0'&&(*it)<='9') return true;
	}
	return false;
}

bool has_cap(string ch){
	for (string::iterator it=ch.begin();it!=ch.end();it++){
		if((*it)>='A'&&(*it)<='Z') return true;
	}
	return false;
}

bool has_low(string ch){
	for (string::iterator it=ch.begin();it!=ch.end();it++){
		if((*it)>='a'&&(*it)<='z') return true;
	}
	return false;
}
