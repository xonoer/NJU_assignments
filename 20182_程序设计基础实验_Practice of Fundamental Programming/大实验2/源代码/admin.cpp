#include <iomanip>
#include "admin.h"

using namespace std;

ADMINLIST::ADMINLIST(string adfile){//终于调试通过了。。。
	FILE* pfile = fopen(adfile.c_str(),"r");
	adminNum=0;
	users.clear();
	loged=NULL;
	char ch[500];
	while(fgets(ch,500,pfile)){
		string t(ch);
		if(t[0]=='\n') continue;
		ADMIN newadmin;
		string user;
		string pass;
		string table;
		int num=0;
		for(int i=0;i<t.length();i++){
			if(num<=1){
				if(t[i]!='\t'&&t[i]!='\n'){
					char target=t[i];
					if(num==0) user+=target;
					if(num==1) pass+=target;
				}
				else{
					while(t[i+1]=='\t') i++;
					num++;
				}
			}
			else{
				if(t[i]!='\t'&&t[i]!='\n'){
					char target=t[i];
					table+=target;
				}
				else{
					while(t[i+1]=='\t') i++;
					num++;
					AUTH newauth;
					string NAME;
					string OWNER;
					string DROP;
					string INSERT;
					string DELETE;
					string SELECT;
					int index=0;
					for(int j=0;j<=table.length();j++){
						if(j!=table.length()&&table[j]!='\\'){
							char target=table[j];
							if(index==0) NAME+=target;
							if(index==1) OWNER+=target;
							if(index==2) DROP+=target;
							if(index==3) INSERT+=target;
							if(index==4) DELETE+=target;
							if(index==5) SELECT+=target;
						}
						else{
							while(table[j+1]=='\\') j++;
							index++;
						}
					}
			
					newauth.tableName=NAME;
					if(OWNER=="1") newauth.owner=1;
					else newauth.owner=0;
					if(DROP!="0"){
					       	string from;	
						for(int j=0;j<=DROP.length();j++){
							if(j!=DROP.length()&&DROP[j]!='-'){
								char target=DROP[j];
					
								from+=target;
							}
							else{
								//test
							
								newauth.DROP.push_back(from);
								from.clear();
							}
						}
					}
					if(INSERT!="0"){
					       	string from;	
						for(int j=0;j<=INSERT.length();j++){
							if(j!=INSERT.length()&&INSERT[j]!='-'){
								char target=INSERT[j];
							
								from+=target;
							}
							else{
								//test
						
								newauth.INSERT.push_back(from);
								from.clear();
							}
						}
					}
					if(DELETE!="0"){
					       	string from;	
						for(int j=0;j<=DELETE.length();j++){
							if(j!=DELETE.length()&&DELETE[j]!='-'){
								char target=DELETE[j];
						
								from+=target;
							}
							else{	//test
			
								newauth.DELETE.push_back(from);
								from.clear();
							}
						}
					}
					if(SELECT!="0"){
					       	string from;	
						for(int j=0;j<=SELECT.length();j++){
							if(j!=SELECT.length()&&SELECT[j]!='-'){
								char target=SELECT[j];
							
								from+=target;
							}
							else{
								//test
					
								newauth.SELECT.push_back(from);
								from.clear();
							}
						}
					}
					newadmin.authInfo.push_back(newauth);
					table.clear();
				}
			}
		}
		newadmin.username=user;
		newadmin.password=pass;
		users.push_back(newadmin);
		adminNum++;
	}
}

bool ADMINLIST::GRANT(ADMIN* from, ADMIN* to, string table, string type){
	if(from->username==to->username) return false;
	AUTH* froma=NULL;
	AUTH* toa=NULL;
	for(int i=0;i<from->authInfo.size();i++){
		if(from->authInfo[i].tableName==table) froma=&(from->authInfo[i]);
	}
	for(int i=0;i<to->authInfo.size();i++){
		if(to->authInfo[i].tableName==table) toa=&(to->authInfo[i]);
	}
	if(froma==NULL||toa==NULL) return false;
	if(toa->owner) return false;
		
	vector <string>* fromau;
	vector <string>* toau;
	if(type=="DROP"){
			fromau=&(froma->DROP);
			toau=&(toa->DROP);

	}
	else if(type=="INSERT"){
			fromau=&(froma->INSERT);
			toau=&(toa->INSERT);
	}
	else if(type=="DELETE"){
			fromau=&(froma->DELETE);
			toau=&(toa->DELETE);
	}
	else if(type=="SELECT"){
			fromau=&(froma->SELECT);
			toau=&(toa->SELECT);
	}
	else	return false;
	
	if(fromau->empty()) return false;
	for(vector <string>::iterator it = toau->begin();it!=toau->end();it++){
		if(*it==from->username) return false;
	}
	toau->push_back(from->username);
	saveToFile();
	return true;
}

bool ADMINLIST::REVOKE(ADMIN* from,ADMIN* to, string table, string type){
	if(from->username==to->username) return false;
		
	AUTH* froma=NULL;
	AUTH* toa=NULL;
	for(int i=0;i<from->authInfo.size();i++){
		if(from->authInfo[i].tableName==table) froma=&(from->authInfo[i]);
	}
	for(int i=0;i<to->authInfo.size();i++){
		if(to->authInfo[i].tableName==table) toa=&(to->authInfo[i]);
	}
	if(froma==NULL||toa==NULL) return false;
	if(toa->owner) return false;
	
	vector <string>* fromau;
	vector <string>* toau;
	if(type=="DROP"){
			fromau=&(froma->DROP);
			toau=&(toa->DROP);

	}
	else if(type=="INSERT"){
			fromau=&(froma->INSERT);
			toau=&(toa->INSERT);
	}
	else if(type=="DELETE"){
			fromau=&(froma->DELETE);
			toau=&(toa->DELETE);
	}
	else if(type=="SELECT"){
			fromau=&(froma->SELECT);
			toau=&(toa->SELECT);
	}
	else	return false;
	
	if(fromau->empty()) return false;
	int index=0;
	for(vector<string>::iterator it = toau->begin();it!=toau->end();it++){
		if(*it==from->username){
			if(toau->size()==1){
				for(int num=0;num<adminNum;num++){
					REVOKE(to,&(users[num]),table,type);
				}
			}
			toau->erase(toau->begin()+index,toau->begin()+index+1);
			saveToFile();
			return true;
		}
		index++;
	}
	return false;						

}

void ADMINLIST::AddTable(string table,string owner){
	AUTH newtable;
	newtable.tableName=table;
	newtable.owner=false;
	AUTH newtable_o;
	newtable_o.tableName=table;
	newtable_o.owner=true;
	newtable_o.DROP.push_back(owner);
	newtable_o.INSERT.push_back(owner);
	newtable_o.DELETE.push_back(owner);
	newtable_o.SELECT.push_back(owner);
	for(int i=0;i<adminNum;i++){
		if(users[i].username==owner) users[i].authInfo.push_back(newtable_o);
		else users[i].authInfo.push_back(newtable);
	}
	saveToFile();
}

void ADMINLIST::DropTable(string table){
	for(int i=0;i<adminNum;i++){
		for(int j=0;j<users[i].authInfo.size();j++){
			if(users[i].authInfo[j].tableName==table){
				users[i].authInfo.erase(users[i].authInfo.begin()+j,users[i].authInfo.begin()+j+1);
			}
		}
	}
	saveToFile();
}

bool ADMINLIST::LOGIN(string username, string pass){
	ADMIN* user=getAdmin(username);
	if(user->password==pass){
		loged=user;
		return true;
	}
	else return false;
}

void ADMINLIST::LOGOUT(){
	loged=NULL;
}


void ADMINLIST::test(){
	cout<<"----------------------------------------------"<<endl;
	cout<<adminNum<<endl;
	for(int i=0;i<adminNum;i++){
		ADMIN target= users[i];
		cout<<target.username<<'\\'<<target.password<<endl;
		for(int j=0;j<target.authInfo.size();j++){
			AUTH au=target.authInfo[j];
			cout<<au.tableName<<'\\'<<au.owner<<'\\';
			if(au.DROP.empty()) cout<<"无权限"<<'\\';
			else{
				for(int k=0;k<au.DROP.size();k++) cout<<au.DROP[k]<<'-';
				cout<<'\\';
			}
			if(au.INSERT.empty()) cout<<"无权限"<<'\\';
			else{
				for(int k=0;k<au.INSERT.size();k++)cout<<au.INSERT[k]<<'-';
				cout<<'\\';
			}

			if(au.DELETE.empty()) cout<<"无权限"<<'\\';
			else{
				for(int k=0;k<au.DELETE.size();k++) cout<<au.DELETE[k]<<'-';
				cout<<'\\';
			}
			if(au.SELECT.empty()) cout<<"无权限"<<'\\';
			else{
				for(int k=0;k<au.SELECT.size();k++)cout<<au.SELECT[k]<<'-';
				cout<<'\\';
			}
			cout<<endl;
		}
		cout<<endl;
	}
}
void ADMINLIST::saveToFile(){
	FILE* pfile=fopen("ALLADMIN.txt","w");
	for(int i=0;i<adminNum;i++){
		string target;
		target.clear();
		target+=users[i].username;
		target+='\t';
		target+=users[i].password;
		target+='\t';
		for(int j=0;j<users[i].authInfo.size();j++){
			target+=users[i].authInfo[j].tableName;
			target+='\\';
			if(users[i].authInfo[j].owner) target+="1\\";
			else target+="0\\";
			if(users[i].authInfo[j].DROP.empty()) target+="0\\";
			else{
				for(int k=0;k<users[i].authInfo[j].DROP.size();k++){
					target+=users[i].authInfo[j].DROP[k];
					if(k!=users[i].authInfo[j].DROP.size()-1) target+='-';
				}
				target+='\\';
			}

			if(users[i].authInfo[j].INSERT.empty()) target+="0\\";
			else{
				for(int k=0;k<users[i].authInfo[j].INSERT.size();k++){
					target+=users[i].authInfo[j].INSERT[k];
					if(k!=users[i].authInfo[j].INSERT.size()-1) target+='-';
				}
				target+='\\';
			}

			if(users[i].authInfo[j].DELETE.empty()) target+="0\\";
			else{
				for(int k=0;k<users[i].authInfo[j].DELETE.size();k++){
					target+=users[i].authInfo[j].DELETE[k];
					if(k!=users[i].authInfo[j].DELETE.size()-1) target+='-';
				}
				target+='\\';
			}

			if(users[i].authInfo[j].SELECT.empty()) target+="0";
			else{
				for(int k=0;k<users[i].authInfo[j].SELECT.size();k++){
					target+=users[i].authInfo[j].SELECT[k];
					if(k!=users[i].authInfo[j].SELECT.size()-1) target+='-';
				}
			}
			if(j!=users[i].authInfo.size()-1) target+='\t';
		}
		target+='\n';
		fputs(target.c_str(),pfile);
	}
	fclose(pfile);
}


ADMIN* ADMINLIST::getAdmin(string username){
	ADMIN* target=NULL;
	for(int i=0;i<adminNum;i++){
		if(users[i].username==username) target=&(users[i]);
	}
	return target;
}

ADMIN* ADMINLIST::getLogedAdmin(){
	return loged;
}

AUTH* ADMINLIST::getAT(string username, string table){
	AUTH* target=NULL;
	ADMIN* user=getAdmin(username);
	if(user!=NULL){
		for(int i=0;i<user->authInfo.size();i++){
			if(user->authInfo[i].tableName==table) target=&(user->authInfo[i]);
		}
	}
	return target;
}

vector <AUTH*> ADMINLIST::getAuthedTable(string username){
	ADMIN* target=getAdmin(username);
	vector <AUTH*> result;
	result.clear();
	if(target==NULL) return result;
	for (int i=0;i<target->authInfo.size();i++){
		AUTH add=target->authInfo[i];
		if(add.DELETE.empty()&&add.DROP.empty()&&add.INSERT.empty()&&add.SELECT.empty()) continue;
		else result.push_back(&(target->authInfo[i]));
	}
	return result;
}

bool ADMINLIST::hasRight(string username, string table, const string type){
	AUTH* au=getAT(username, table);
	if(au==NULL) return false;
	if(type=="DROP"){
		if(!au->DROP.empty()) return true;
		else return false;
	}
	else if(type=="INSERT"){
		if(!au->INSERT.empty()) return true;
		else return false;
	}
	else if(type=="DELETE"){
		if(!au->DELETE.empty()) return true;
		else return false;
	}
	else if(type=="SELECT"){
		if(!au->SELECT.empty()) return true;
		else return false;
	}
	else return false;
}

bool ADMINLIST::isOwner(string username, string table){
	AUTH* au=getAT(username, table);
	if(au==NULL) return false;
	if (au->owner) return true;
	else return false;
}





