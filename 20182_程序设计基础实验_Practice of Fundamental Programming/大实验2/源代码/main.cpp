#include "data.h"
#include "admin.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>

using namespace std;
/*string passInput(){
	char ch;
	string pass;
	initscr();
	ch=getch();
	while(ch!='\r'){
		pass+=ch;
	}
	endwin();
	return pass;
}
*/
void enter_login(DATABASE* Base,ADMINLIST* Alist);
void enter_user(DATABASE*Base,ADMINLIST* Alist,PER* Per);
void enter_login(DATABASE* Base,ADMINLIST* Alist){
	string user;
	string pass;
	cout<<"(mysql)==>login:";
	cin>>user;
	ADMIN* admin=Alist->getAdmin(user);
	if(admin==NULL){
	      cout<<"(mysql)==>Error: Username \""<<user<<"\" is not found."<<endl;
	      return;
	}
	pass=getpass("(mysql)==>password:");
	if(Alist->LOGIN(user,pass)){
		cout<<"(mysql)==>Welcome! "<<user<<endl;
		PER per;
		PER* Per=&per;
		enter_user(Base,Alist,Per);
		return;
	}
	else{
		cout<<"(mysql)==>Error: Wrong password."<<endl;
		return;
	}
}
void enter_user(DATABASE* Base,ADMINLIST* Alist,PER* Per){
	ADMIN* loged=Alist->getLogedAdmin();
	Per->check_per(Base,Alist,loged);
	string cmd;
	do{
		cout<<"(mysql)==>";
		getline(cin,cmd);
		int len=cmd.length();
		if(cmd=="quit") return;
		else if(cmd[0]=='C'){
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){ //init CREATE 
				init+=cmd[i];
				i++;
			}
			if(init!="CREATE"){
				cout<<"(mysql)==>Error! Cannot find the command \""<<init<<"\""<<endl;
				continue;
			}
			else{
				while(cmd[i]==' '&&i<len) i++;
				string obj;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){ //obj TABLE
					obj+=cmd[i];
					i++;
				}
				if(obj!="TABLE"){
					cout<<"(mysql)==>Error! Cannot find the object \""<<obj<<"\""<<endl;
					continue;
				}
				else{
					while(cmd[i]==' '&&i<len)i++;
					string tablename;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){ //tablename
						tablename+=cmd[i];
						i++;
					}
					if(Base->findTablename(tablename)){
						cout<<"(mysql)==>Error! Table \""<<tablename<<"\" already exists"<<endl;
						continue;
					}
					else{
						while(cmd[i]==' '&&i<len) i++;
						if(cmd[i]=='F'){
							string word;
							
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){ //word FROM
								word+=cmd[i];
								i++;
							}
							if(word!="FROM"){
								cout<<"(mysql)==>Error! Cannot find the command \""<<word<<"\""<<endl;
								continue;
							}
							else{
								while(cmd[i]==' '&&i<len) i++;
								string filename;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){ //filename
									filename+=cmd[i];
									i++;
								}
								FILE* thefile=fopen(filename.c_str(),"r");
								if(thefile==NULL){
								cout<<"(mysql)==>Error! Cannot find the file \""<<filename<<"\""<<endl;
									continue;
								}
								else{
									if(Base->CREATE_NEW_FROMFILE(tablename, filename, loged->username)){
										Alist->AddTable(tablename,loged->username);
										continue;
									}
									else{
										cout<<"(mysql)==>Error! Cannot create the table"<<endl;
									}
								}
							}
						}
						else if(cmd[i]=='('){
							DATA column;
							column.id=0;
							column.values.clear();
							i++;
							while(cmd[i]!=')'&&i<len){
								string t;
								t.clear();
				
								while(cmd[i]!=','&&cmd[i]!=')'&&i<len){
									t+=cmd[i];
									
									i++;
								}
								
								column.values.push_back(t);
								if(cmd[i]==',') {
									i++;
									while(cmd[i]==' ') i++;
								}

							}
							if(cmd[i]!=')'){
								cout<<"(mysql)==>Error! Invalid command for creating table"<<endl;
								continue;
							}
							i++;
							while(cmd[i]==' '&&i<len)i++;
							string word;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								word+=cmd[i];
								i++;
							}
							if(word!="TO"){
								cout<<"(mysql)==>Error! Cannot find the key word \""<<word<<"\""<<endl;
								continue;
							}
							else{
								while(cmd[i]==' '&&i<len) i++;
								string file;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									file+=cmd[i];
									i++;
								}
								if(Base->findFilename(file)){
									cout<<"(mysql)==>Error! File \""<<file<<"\" already exist"<<endl;
									continue;
								}
								else{
									if(Base->CREATE_NEW(tablename,column,file,loged->username)){ 
										Alist->AddTable(tablename,loged->username);
									
										continue;
									}
									else{
										cout<<"(mysql)==>Error! Cannot create table"<<endl;
										continue;
									}
								}
							}
						}
						else{
							cout<<"(mysql)==>Error! Invalid command"<<endl;
							continue;
						}
					}
				}
			}
		}
		else if(cmd[0]=='D'){
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
				init+=cmd[i];
				i++;
			}
			if(init!="DROP"&&init!="DELETE"){
				cout<<"(mysql)==>Error! Cannot find the command \""<<init<<"\""<<endl;
				continue;
			}
			else if(init=="DROP"){
				while(cmd[i]==' '&&i<len) i++;
				string obj;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					obj+=cmd[i];
					i++;
				}
				if(obj!="TABLE"){
					cout<<"(mysql)==>Error! Cannot find the object \""<<obj<<"\""<<endl;
					continue;
				}
				else{
					while(cmd[i]==' '&&i<len)i++;
					string tablename;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						tablename+=cmd[i];
						i++;
					}
					if(!Base->findTablename(tablename)){
						cout<<"(mysql)==>Error! Table \""<<tablename<<"\" not exist"<<endl;
						continue;
					}
					AUTH* au=Alist->getAT(loged->username,tablename);
					if(au==NULL){
						cout<<"(mysql)==>Error! Cannot drop the table."<<endl;
						continue;
					}
					if(au->DROP.empty()){
						cout<<"(mysql)==>Error! Permission Denied!"<<endl;
						Per->per_denied(Base,Alist,loged->username,tablename,"DROP");
						continue;
					}
					if(!Base->DROP(tablename)){
						cout<<"(mysql)==>Error! Cannot drop the table."<<endl;
						continue;
					}
					else{
						Alist->DropTable(tablename);
					}
				} 
			}
			else if(init=="DELETE"){
				while(cmd[i]==' '&&i<len) i++;
				string input;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					input+=cmd[i];
					i++;
				}
				if(input!="FROM"&&input!="*"){
					cout<<"(mysql)==>Error! Cannot recognize the input."<<endl;
					continue;
				}
				else if(input=="*"){
					while(cmd[i]==' '&&i<len) i++;
					string obj;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						obj+=cmd[i];
						i++;
					}
					if(obj!="FROM"){
						cout<<"(mysql)==>Error! Cannot find the command \""<<obj<<"\""<<endl;
						continue;
					}
					else{
						while(cmd[i]==' '&&i<len) i++;
						string tablename;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							tablename+=cmd[i];
							i++;
						}
						if(!Base->findTablename(tablename)){
							cout<<"(mysql)==>Error! Table \""<<tablename<<"\" not exist"<<endl;
							continue;
						}
						AUTH* au=Alist->getAT(loged->username,tablename);
						if(au==NULL){
							cout<<"(mysql)==>Error! Cannot delete the data."<<endl;
							continue;
						}
						if(au->DELETE.empty()){
							cout<<"(mysql)==>Error! Permission Denied!"<<endl;
							Per->per_denied(Base,Alist,loged->username,tablename,"DELETE");
							continue;
						}
						Base->getTable(tablename)->DELETEall();
					}
				}
				else if(input=="FROM"){
					while(cmd[i]==' '&&i<len) i++;
					string tablename;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						tablename+=cmd[i];
						i++;
					}
					if(!Base->findTablename(tablename)){
						cout<<"(mysql)==>Error! Table \""<<tablename<<"\" not exist"<<endl;
						continue;
					}
					else{
						AUTH* au=Alist->getAT(loged->username,tablename);
						if(au==NULL){
							cout<<"(mysql)==>Error! Cannot delete the data."<<endl;
							continue;
						}
						if(au->DELETE.empty()){
							cout<<"(mysql)==>Error! Permission Denied!"<<endl;
							continue;
						}
						while(cmd[i]==' '&&i<len) i++;
						string key;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							key+=cmd[i];
							i++;
						}
						if(key!="WHERE"){
							cout<<"(mysql)==>Error! Cannot recgonize the key word \""<<key<<"\""<<endl;
							continue;
						}
						else{
							DATA column=Base->getTable(tablename)->getColumn();
							int columnNum=Base->getTable(tablename)->getColumnNum();
							while(cmd[i]==' '&&i<len) i++;
							string target;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								target+=cmd[i];
								i++;
							}
							int num=0;
							bool have=false;
							while(num<columnNum){
								if(column.values[num]==target){
									have=true;
									break;
								}
								num++; 
							}
							
							if(!have){
								cout<<"(mysql)==>Error! Column \""<<target<<"\" not included in table \""<<tablename<<"\""<<endl;
								continue;
							}
							else{
								while(cmd[i]==' '&&i<len) i++;
								string ccmd;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									ccmd+=cmd[i];
									i++;
								}
							
								if(ccmd!="="){
									cout<<"(mysql)==>Error! Invalid Input!"<<endl;
									continue;
								}
								
								
								while(cmd[i]==' '&&i<len) i++;
								string cont;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									cont+=cmd[i];
									i++;
								}
							
								if(cont=="\0"){
									cout<<"(mysql)==>Error! Cannot delete the data (Invalid Input)"<<endl;
									continue;
								}
								DATA del;
								for(int i=0;i<num;i++){
									del.values.push_back("\0");
								}
								del.values.push_back(cont);
								for(int i=num+1;i<columnNum;i++){
									del.values.push_back("\0");
								}
								if(!Base->getTable(tablename)->DELETE(del)){
									cout<<"(mysql)==>Error! Cannot delete the data (Data not exist)"<<endl;
									continue;
								}
								else{
									continue;
								}
							}
						}
					}
				}
			} 
		}
		else if(cmd[0]=='T') {
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
				init+=cmd[i];
				i++;
			}
			if(init!="TABLE"){
				cout<<"(mysql)==>Error! Cannot interprate the input \""<<init<<"\""<<endl;
				continue;
			}
			else{
				while(cmd[i]==' '&&i<len) i++;
				string obj;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					obj+=cmd[i];
					i++;
				}
				if(obj!="LIST"){
					cout<<"(mysql)==>Error! Cannot find the command \""<<obj<<"\""<<endl;
					continue;
				}
				else{
					vector <AUTH*> result = Alist->getAuthedTable(loged->username);
					int num=result.size();
					cout<<"   total:"<<num<<endl;
					for(int i=0;i<num;i++){
						AUTH show = *(result[i]);
						string tablename = show.tableName;
						int dataNum = Base->getTable(tablename)->getDataNum();
						int columnNum = Base->getTable(tablename)->getColumnNum();
						DATA column = Base->getTable(tablename)->getColumn();
						cout<<"      "<<tablename<<": ("<<columnNum<<","<<dataNum<<") {";
						for(int j=0;j<columnNum;j++){
							cout<<column.values[j];
							if(j!=columnNum-1) cout<<",";
						}
						cout<<"} ";
						if(!show.DROP.empty())cout<<"DROP ";
						if(!show.INSERT.empty()) cout<<"INSERT ";
						if(!show.DELETE.empty()) cout<<"DELETE ";
						if(!show.SELECT.empty()) cout<<"SELECT ";
						if(show.owner) cout<<"[OWNER]";
						cout<<endl;
 					}
				}
			}
		}
		else if (cmd[0]=='I'){
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
				init+=cmd[i];
				i++;
			}
			if(init!="INSERT"){
				cout<<"(mysql)==>Error! Cannot interprate the command \""<<init<<"\""<<endl;
				continue;
			}
			else{
				while(cmd[i]==' '&&i<len) i++;
				string obj;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					obj+=cmd[i];
					i++;
				}
				if(obj!="INTO"){
					cout<<"(mysql)==>Error! Cannot interprate the input \""<<obj<<"\""<<endl;
					continue;
				}
				else{
					while(cmd[i]==' '&&i<len)i++;
					string tablename;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						tablename+=cmd[i];
						i++;
					}
					if(!Base->findTablename(tablename)){
						cout<<"(mysql)==>Error! Table \""<<tablename<<"\" not exist"<<endl;
						continue;
					}
					AUTH* au = Alist->getAT(loged->username,tablename);
					if(au->INSERT.empty()){
						cout<<"(mysql)==>Error! Permission Denied!"<<endl;
						Per->per_denied(Base,Alist,loged->username,tablename,"INSERT");
						continue;
					}
					while(cmd[i]==' '&&i<len)i++;
					if(cmd[i]!='('&&cmd[i]!='V'){
						cout<<"(mysql)==>Error! Invalid Input!"<<endl;
						continue;
					}
					else if(cmd[i]=='V'){
						string word;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							word+=cmd[i];
							i++;
						}
						if(word!="VALUES"){
							cout<<"(mysql)==>Error! Invalid Input!"<<endl;
							continue;
						}
						else{
							while(cmd[i]==' '&&i<len)i++;
							if(cmd[i]!='('){
								cout<<"(mysql)==>Error! Invalid Input!"<<endl;
								continue;
							}
							else{
								DATA data;
								data.values.clear();
								i++;
								while(cmd[i]!=')'&&i<len){
									string t;
									t.clear();
									while(cmd[i]!=','&&cmd[i]!=')'&&i<len){
										t+=cmd[i];
										i++;
									}
									data.values.push_back(t);
									if(cmd[i]==','){
										i++;
										while(cmd[i]==' ') i++;
									}
								}
								if(cmd[i]!=')'){
									cout<<"(mysql)==>Error! Invalid command for inserting data"<<endl;
									continue;
								}
								if(data.values.size()!=Base->getTable(tablename)->getColumnNum()){
									cout<<"(mysql)==>Error! Data not consistent with the column"<<endl;
									continue;
								}
								i++;
								Base->getTable(tablename)->INSERTtable(data);
							}
						}
					}
					else if(cmd[i]=='('){
						DATA column;
						column.values.clear();
						i++;
						bool valid=true;
						while(cmd[i]!=')'&&i<len){
							string t;
							t.clear();
							while(cmd[i]!=','&&cmd[i]!=')'&&i<len){
								t+=cmd[i];
								i++;
							}
							if(!Base->getTable(tablename)->hasColumn(t)) valid = false;
							column.values.push_back(t);
							if(cmd[i]==',') {
								i++;
								while(cmd[i]==' ')i++;
							}
						}
						if(cmd[i]!=')'){
							cout<<"(mysql)==>Error! Invalid command for inserting data"<<endl;
							continue;
						}
						if(!valid){
							cout<<"(mysql)==>Error! Invalid column input!"<<endl;
						}
						i++;
						while(cmd[i]==' '&&i<len)i++;
						string word;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							word+=cmd[i];
							i++;
						}
						if(word!="VALUES"){
							cout<<"(mysql)==>Error! Cannot find the object \""<<word<<"\""<<endl;
							continue;
						}
						else{
							while(cmd[i]==' '&&i<len)i++;
							if(cmd[i]!='('){
								cout<<"(mysql)==>Error! Invalid Input!"<<endl;
								continue;
							}
							else{
								DATA data;
								data.values.clear();
								i++;
								while(cmd[i]!=')'&&i<len){
									string t;
									t.clear();
									while(cmd[i]!=','&&cmd[i]!=')'&&i<len){
										t+=cmd[i];
										i++;
									}
									data.values.push_back(t);
									if(cmd[i]==',') {
										i++;
										while(cmd[i]==' ') i++;
									}
								}
								if(cmd[i]!=')'){
									cout<<"(mysql)==>Error! Invalid command for inserting data"<<endl;
									continue;
								}
								if(data.values.size()!=column.values.size()){
									cout<<"(mysql)==>Error! Data not consistent with the column"<<endl;
									continue;
								}
								i++;
								DATA ins;
								DATA tcolumn=Base->getTable(tablename)->getColumn();
								int columnNum=Base->getTable(tablename)->getColumnNum(); 
								for(int i=0;i<columnNum;i++){
									bool have=false;
									for(int j=0;j<column.values.size();j++){
										if(tcolumn.values[i]==column.values[j]){
											ins.values.push_back(data.values[j]);
											have=true;
										}	
									}
									if(!have) ins.values.push_back("\0");
								}
								Base->getTable(tablename)->INSERTtable(ins);
							}
						}
					}
				}
			}
		}
		else if (cmd[0]=='S'){
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
				init+=cmd[i];
				i++;
			}
			if(init!="SELECT"){
				cout<<"(mysql)==>Error! Cannot interprate the command \""<<init<<"\""<<endl;
				continue;
			}
			else{
				while(cmd[i]==' '&&i<len)i++;
				string word;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					word+=cmd[i];
					i++;
				}
				if(word=="*"){
					while(cmd[i]==' '&&i<len)i++;
					string key;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						key+=cmd[i];
						i++;
					}
					if(key!="FROM"){
						cout<<"(mysql)==>Error! Cannot interprate the command \""<<key<<"\""<<endl;
						continue;
					}
					else{
						while(cmd[i]==' '&&i<len)i++;
						string tablename;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							tablename+=cmd[i];
							i++;
						}
						if(!Base->getTable(tablename)){
							cout<<"(mysql)==>Error! Cannot find the table \""<<tablename<<"\""<<endl;
							continue;
						}
						AUTH* au=Alist->getAT(loged->username,tablename);
						if(au->SELECT.empty()){
							cout<<"(mysql)==>Error! Permission Denied!"<<endl;
							Per->per_denied(Base,Alist,loged->username,tablename,"SELECT");
							continue;
						}
						while(cmd[i]==' '&&i<len)i++;
						if(i==len){
							vector <DATA> result= Base->getTable(tablename)->SELECT_BY_COLUMN_ALL();
							Base->getTable(tablename)->showTable(result);
							continue;
						}
						string key1;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							key1+=cmd[i];
							i++;
						}
						if(key1!="ORDER"&&key1!="WHERE"&&key1!="TO"){
							cout<<"(mysql)==>Error! Cannot interprate the command \""<<key1<<"\""<<endl;
							continue;
						}
						else if(key1=="ORDER"){
						
							while(cmd[i]==' '&&i<len)i++;
							string key2;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								key2+=cmd[i];
								i++;
							}
							if(key2!="BY"){
								cout<<"(mysql)==>Error! Cannot interprate the command \""<<key2<<"\""<<endl;
								continue;
							}
						//解析带空格 
							DATA column;
							column.values.clear();
							bool valid=true;
							do{
								i++;
								while(cmd[i]==' '&&i<len)i++;
								string add;
								add.clear();
								while((cmd[i]!=','&&cmd[i]!=' ')&&i<len) {
									add+=cmd[i];
									i++;
								}
								column.values.push_back(add);
								if((!Base->getTable(tablename)->hasColumn(add))) valid=false;
							}while(cmd[i]==',');
						//
							if(!valid){
								cout<<"(mysql)==>Error! Invalid column input."<<endl;
								continue;
							}
							while(cmd[i]==' '&&i<len)i++;
							string order;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								order+=cmd[i];
								i++;
							}
							if(order!="ASC"&&order!="DESC"){
								cout<<"(mysql)==>Error! Invalid order input."<<endl;
								continue;
							}
							else{
								Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_ORDER(column,order));
								continue;
							}
						}
						else if (key1=="TO"){
							while(cmd[i]==' '&&i<len)i++;
							string filename;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								filename+=cmd[i];
								i++;
							}
							if(Base->getTableByFile(filename)){
								cout<<"(mysql)==>Error! File \""<<filename<<"\" already exist"<<endl;
								continue;
							}
							DATA key;
							key.values.clear();
							Base->getTable(tablename)->SELECT_BY_KEY_INTOFILE(Base->getTable(tablename)->getColumn(),key,filename.c_str());
							continue;
						}
						else if(key1=="WHERE"){
							while(cmd[i]==' '&&i<len)i++;
							string tar;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								tar+=cmd[i];
								i++;
							}
							if(!Base->getTable(tablename)->hasColumn(tar)){
								cout<<"(mysql)==>Error! Invalid column input!"<<endl;
								continue;
							}
							while(cmd[i]==' '&&i<len)i++;
							string key2;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								key2+=cmd[i];
								i++;
							}
							if(key2!="="&&key2!=">"&&key2!="<"&&key2!=">="&&key2!="<="){
								cout<<"(mysql)==>Error! Cannot interprate key word \""<<key2<<"\""<<endl;
								continue;
							}
							while(cmd[i]==' '&&i<len)i++;
							string data;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								data+=cmd[i];
								i++;
							}
							DATA key;
							key.values.clear();
							DATA tcolumn=Base->getTable(tablename)->getColumn();
							int cnum=Base->getTable(tablename)->getColumnNum();
							for(int j=0;j<cnum;j++){
								if(tcolumn.values[j]==tar){
									key.values.push_back(data);
								}
								else{
									key.values.push_back("\0");
								}
							}
							while(cmd[i]==' '&&i<len)i++;
							if(i==len){
								if(key2=="=")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY(Base->getTable(tablename)->getColumn(),key));
								if(key2==">")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_G(Base->getTable(tablename)->getColumn(),key));
								if(key2=="<")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_L(Base->getTable(tablename)->getColumn(),key));
								if(key2==">=")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_GE(Base->getTable(tablename)->getColumn(),key));
								if(key2=="<=")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_LE(Base->getTable(tablename)->getColumn(),key));
								continue;
							}
							else{
								string key3;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									key3+=cmd[i];
									i++;
								}
								if(key3!="TO"){
									cout<<"(mysql)==>Error! Cannot find the keyword \""<<key1<<"\""<<endl;
									continue;
								}
								else {
									while(cmd[i]==' '&&i<len)i++;
									string filename;
									while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
										filename+=cmd[i];
										i++;
									}
									if(Base->getTableByFile(filename)){
										cout<<"(mysql)==>Error! File \""<<filename<<"\" already exist"<<endl;
										continue;
									}
									Base->getTable(tablename)->SELECT_BY_KEY_INTOFILE(Base->getTable(tablename)->getColumn(),key,filename.c_str());
									continue;
								}
							}
						}
					}
				}
				if(word=="DISTINCT"){
					DATA column;
					column.values.clear();
					//
					do{
						i++;
						while(cmd[i]==' '&&i<len)i++;
						string add;
						add.clear();
						while((cmd[i]!=','&&cmd[i]!=' ')&&i<len) {
							add+=cmd[i];
							i++;
						}
						column.values.push_back(add);
					}while(cmd[i]==',');
					//
					while(cmd[i]==' '&&i<len)i++;
					string key;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						key+=cmd[i];
						i++;
					}
					if(key!="FROM"){
						cout<<"(mysql)Error! Cannot interprate the command \""<<key<<"\""<<endl;
						continue;
					}
					else{
						while(cmd[i]==' '&&i<len)i++;
						string tablename;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							tablename+=cmd[i];
							i++;
						}
						if(!Base->getTable(tablename)){
							cout<<"(mysql)Error! Cannot find the table \""<<tablename<<"\""<<endl;
							continue;
						}
						AUTH* au=Alist->getAT(loged->username,tablename);
						if(au->SELECT.empty()){
							cout<<"(mysql)Error! Permission denied!"<<endl;
							Per->per_denied(Base,Alist,loged->username,tablename,"SELECT");
							continue;
						}
						for(int j=0;j<column.values.size();j++){
							if(!Base->getTable(tablename)->hasColumn(column.values[j])){
								cout<<"(mysql)Error! Invalid column input."<<endl;
								continue;
							}
						}
						Base->getTable(tablename)->showTableWithoutId(Base->getTable(tablename)->SELECT_BY_COLUMN_DISTINCT(column));
						continue;
					}
				}
				else{
					DATA column;
					column.values.clear();
				/*	string add;
					for(int j=0;j<=word.length();j++){
						if(word[j]!=','&&j!=word.length()){
							add+=word[j];
						}
						else{
							column.values.push_back(add);
							add.clear();
							if(j+1<word.length()&&word[j+1]==' ') j++;
						}
					}*/
					if(cmd[i-1]!=','){
						column.values.push_back(word);
					}
					else{
						word.pop_back();
						column.values.push_back(word);
						//
						do{
							i++;
							while(cmd[i]==' '&&i<len)i++;
							string add;
							add.clear();
							while((cmd[i]!=','&&cmd[i]!=' ')&&i<len) {
								add+=cmd[i];
								i++;
							}
							column.values.push_back(add);
						}while(cmd[i]==',');
						//
					}
					while(cmd[i]==' '&&i<len)i++;
					string key;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						key+=cmd[i];
						i++;
					}
					if(key!="FROM"){
						cout<<"(mysql)Error! Cannot interprate the command \""<<key<<"\""<<endl;
						continue;
					}
					else{
						while(cmd[i]==' '&&i<len)i++;
						string tablename;
						while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
							tablename+=cmd[i];
							i++;
						}
						if(!Base->getTable(tablename)){
							cout<<"(mysql)Error! Cannot find the table \""<<tablename<<"\""<<endl;
							continue;
						}
						AUTH* au=Alist->getAT(loged->username,tablename);
						if(au->SELECT.empty()){
							cout<<"(mysql)Error! Permission denied!"<<endl;
							Per->per_denied(Base,Alist,loged->username,tablename,"SELECT");
							continue;
						}
						for(int j=0;j<column.values.size();j++){
							if(!Base->getTable(tablename)->hasColumn(column.values[j])){
								cout<<"(mysql)Error! Invalid column input."<<endl;
								continue;
							}
						}
						while(cmd[i]==' '&&i<len)i++;
						if(i==len){
							Base->getTable(tablename)->showTableWithoutId(Base->getTable(tablename)->SELECT_BY_COLUMN(column));
							continue;
						}
						else{
							string key1;
							while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
								key1+=cmd[i];
								i++;
							}
							if(key1!="WHERE"&&key1!="TO"){
								cout<<"(mysql)==>Error! Cannot find the keyword \""<<key1<<"\""<<endl;
								continue;
							}
							else if(key1=="TO"){
								while(cmd[i]==' '&&i<len)i++;
								string filename;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									filename+=cmd[i];
									i++;
								}
								if(Base->getTableByFile(filename)){
									cout<<"(mysql)==>Error! File \""<<filename<<"\" already exist"<<endl;
									continue;
								}
								DATA key;
								key.values.clear();
								Base->getTable(tablename)->SELECT_BY_KEY_INTOFILE(column,key,filename.c_str());
								continue;
							}
							else if(key1=="WHERE"){
								while(cmd[i]==' '&&i<len)i++;
								string tar;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									tar+=cmd[i];
									i++;
								}
								if(!Base->getTable(tablename)->hasColumn(tar)){
									cout<<"(mysql)==>Error! Invalid column input!"<<endl;
									continue;
								}
								while(cmd[i]==' '&&i<len)i++;
								string key2;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									key2+=cmd[i];
									i++;
								}
								if(key2!="="&&key2!=">"&&key2!="<"&&key2!=">="&&key2!="<="){
									cout<<"(mysql)==>Error! Cannot interprate key word \""<<key2<<"\""<<endl;
									continue;
								}
								while(cmd[i]==' '&&i<len)i++;
								string data;
								while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
									data+=cmd[i];
									i++;
								}
								DATA key;
								key.values.clear();
								DATA tcolumn=Base->getTable(tablename)->getColumn();
								int cnum=Base->getTable(tablename)->getColumnNum();
								for(int j=0;j<cnum;j++){
									if(tcolumn.values[j]==tar){
										key.values.push_back(data);
									}
									else{
										key.values.push_back("\0");
									}
								}
								while(cmd[i]==' '&&i<len)i++;
								if(i==len){
									if(key2=="=")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY(column,key));
									if(key2==">")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_G(column,key));
									if(key2=="<")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_L(column,key));
									if(key2==">=")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_GE(column,key));
									if(key2=="<=")Base->getTable(tablename)->showTable(Base->getTable(tablename)->SELECT_BY_KEY_LE(column,key));
									continue;
								}
								else{
									string key3;
									while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
										key3+=cmd[i];
										i++;
									}
									if(key3!="TO"){
										cout<<"(mysql)==>Error! Cannot find the keyword \""<<key1<<"\""<<endl;
										continue;
									}
									else {
										while(cmd[i]==' '&&i<len)i++;
										string filename;
										while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
											filename+=cmd[i];
											i++;
										}
										if(Base->getTableByFile(filename)){
											cout<<"(mysql)==>Error! File \""<<filename<<"\" already exist"<<endl;
											continue;
										}
										Base->getTable(tablename)->SELECT_BY_KEY_INTOFILE(column,key,filename.c_str());
										continue;
									}
								}
							}
						}
					}
				}
			}
		}
		else if(cmd[0]=='G'){
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
				init+=cmd[i];
				i++;
			}
			if(init!="GRANT"){
				cout<<"(mysql)==>Error! Cannot interprate the command \""<<init<<"\""<<endl;
				continue;
			}
			else{
				string list;
				do{
				
					while(cmd[i]==' ') i++;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						list+=cmd[i];
						i++;
					}
				}while(cmd[i-1]==',');
				while(cmd[i]==' ') i++;
				string key1;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					key1+=cmd[i];
					i++;
				}
				if(key1!="on"){
					cout<<"(mysql)Error! Cannot interprate the key word \""<<key1<<"\""<<endl;
					continue;
				}
				while(cmd[i]==' ') i++;
				string tablename;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					tablename+=cmd[i];
					i++;
				}
				if(!Base->getTable(tablename)){
					cout<<"(mysql)==>Error! Table \""<<tablename<<"\" not exist"<<endl;
					continue;
				}
				while(cmd[i]==' ') i++;
				string key2;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					key2+=cmd[i];
					i++;
				}
				if(key2!="to"){
					cout<<"(mysql)Error! Cannot interprate the key word \""<<key2<<"\""<<endl;
					continue;
				}
				string users;
				do{
				
					while(cmd[i]==' ') i++;
				
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						users+=cmd[i];
						i++;
					}
				}while(cmd[i-1]==',') ;
				vector <string> userlist;
				string name;
				bool uservalid=true;
				for(int j=0;j<=users.length();j++){
					if(users[j]!=','&&j!=users.length()) name+=users[j];
					else{
						userlist.push_back(name);
						if(!Alist->getAdmin(name)) uservalid=false;
						name.clear();
						while(j+1<users.length()&&users[j+1]==' ') j++;
					}
				} 
				if(!uservalid){
					cout<<"(mysql)==>Error! Invalid username input!"<<endl;
					continue;
				}
				AUTH* au=Alist->getAT(loged->username,tablename);
				//处理权限数据	
				if(list=="all"){
					if(!au->DROP.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->GRANT(loged,Alist->getAdmin(userlist[j]),tablename,"DROP")){
								cout<<"(mysql)==> Successfully granted DROP on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to grant DROP on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
						}
					}
					if(!au->INSERT.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->GRANT(loged,Alist->getAdmin(userlist[j]),tablename,"INSERT")){
								cout<<"(mysql)==> Successfully granted INSERT on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to grant INSERT on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
						}
					}
					if(!au->DELETE.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->GRANT(loged,Alist->getAdmin(userlist[j]),tablename,"DELETE")){
								cout<<"(mysql)==> Successfully granted DELETE on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to grant DELETE on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
						}
					}
					if(!au->SELECT.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->GRANT(loged,Alist->getAdmin(userlist[j]),tablename,"SELECT")){
								cout<<"(mysql)==> Successfully granted SELECT on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to grant SELECT on \""<<tablename<<"\" to "<<userlist[j]<<endl;
							}
						}
					}
				}
				
				string right;
				bool valid=true;
				int nn=list.length();
				for(int j=0;j<=nn;j++){
					if(list[j]!=','&&list[j]!=' '&&j!=list.length()) right+=list[j];
					else{
						if(right!="DROP"&&right!="INSERT"&&right!="DELETE"&&right!="SELECT"){
							cout<<"(mysql)==>Error! Wrong input of "<<right<<endl;
						}
						else{
							for(int k=0;k<userlist.size();k++){
								if(Alist->GRANT(loged,Alist->getAdmin(userlist[k]),tablename,right)){
									cout<<"(mysql)==> Successfully granted "<<right<<" on \""<<tablename<<"\" to "<<userlist[k]<<endl;
								}
								else{
									cout<<"(mysql)==> Fail to grant "<<right<<" on \""<<tablename<<"\" to "<<userlist[k]<<endl;
								}
							}
							right.clear();
						}
					}
				} 
			} 
		} 
		else if(cmd[0]=='R'){
			string init;
			int i=0;
			while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
				init+=cmd[i];
				i++;
			}
			if(init!="REVOKE"){
				cout<<"(mysql)==>Error! Cannot interprate the command \""<<init<<"\""<<endl;
				continue;
			}
			else{
				string list;
				do{
				
					while(cmd[i]==' ') i++;
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						list+=cmd[i];
						i++;
					}
				}while(cmd[i-1]==',');
				while(cmd[i]==' ') i++;
				string key1;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					key1+=cmd[i];
					i++;
				}
				if(key1!="on"){
					cout<<"(mysql)Error! Cannot interprate the key word \""<<key1<<"\""<<endl;
					continue;
				}
				while(cmd[i]==' ') i++;
				string tablename;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					tablename+=cmd[i];
					i++;
				}
				if(!Base->getTable(tablename)){
					cout<<"(mysql)==>Error! Table \""<<tablename<<"\" not exist"<<endl;
					continue;
				}
				while(cmd[i]==' ') i++;
				string key2;
				while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
					key2+=cmd[i];
					i++;
				}
				if(key2!="to"){
					cout<<"(mysql)Error! Cannot interprate the key word \""<<key2<<"\""<<endl;
					continue;
				}
				string users;
				do{
				
					while(cmd[i]==' ') i++;
				
					while(cmd[i]!=' '&&cmd[i]!='\n'&&cmd[i]!='\r'&&cmd[i]!='\0'&&i<len){
						users+=cmd[i];
						i++;
					}
				}while(cmd[i-1]==',') ;
				vector <string> userlist;
				string name;
				bool uservalid=true;
				for(int j=0;j<=users.length();j++){
					if(users[j]!=','&&j!=users.length()) name+=users[j];
					else{
						userlist.push_back(name);
						if(!Alist->getAdmin(name)) uservalid=false;
						name.clear();
						while(j+1<users.length()&&users[j+1]==' ') j++;
					}
				} 
				if(!uservalid){
					cout<<"(mysql)==>Error! Invalid username input!"<<endl;
					continue;
				}
				AUTH* au=Alist->getAT(loged->username,tablename);
				//处理权限数据	
				if(list=="all"){
					if(!au->DROP.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->REVOKE(loged,Alist->getAdmin(userlist[j]),tablename,"DROP")){
								cout<<"(mysql)==> Successfully revoked DROP on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to revoke DROP on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
						}
					}
					if(!au->INSERT.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->REVOKE(loged,Alist->getAdmin(userlist[j]),tablename,"INSERT")){
								cout<<"(mysql)==> Successfully revoked INSERT on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to revoke INSERT on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
						}
					}
					if(!au->DELETE.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->REVOKE(loged,Alist->getAdmin(userlist[j]),tablename,"DELETE")){
								cout<<"(mysql)==> Successfully revoked DELETE on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to revoke DELETE on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
						}
					}
					if(!au->SELECT.empty()){
						for(int j=0;j<userlist.size();j++){
							if(Alist->REVOKE(loged,Alist->getAdmin(userlist[j]),tablename,"SELECT")){
								cout<<"(mysql)==> Successfully revoked SELECT on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
							else{
								cout<<"(mysql)==> Fail to revoke SELECT on \""<<tablename<<"\" from "<<userlist[j]<<endl;
							}
						}
					}
					continue;
				}
				
				string right;
				bool valid=true;
				int nn=list.length();
				for(int j=0;j<=nn;j++){
					if(list[j]!=','&&list[j]!=' '&&j!=list.length()) right+=list[j];
					else{
						if(right!="DROP"&&right!="INSERT"&&right!="DELETE"&&right!="SELECT"){
							cout<<"(mysql)==>Error! Wrong input of "<<right<<endl;
						}
						else{
							for(int k=0;k<userlist.size();k++){
								if(Alist->REVOKE(loged,Alist->getAdmin(userlist[k]),tablename,right)){
									cout<<"(mysql)==> Successfully revoked "<<right<<" on \""<<tablename<<"\" from "<<userlist[k]<<endl;
								}
								else{
									cout<<"(mysql)==> Fail to revoke "<<right<<" on \""<<tablename<<"\" from "<<userlist[k]<<endl;
								}
							}
							right.clear();
						}
					}
				} 
			}
		}
		else{
			cout<<"Please input valid database command."<<endl;
			continue;
		}
	}while(true);

}


int main(){
	DATABASE base("ALLDATABASE.txt");
	ADMINLIST adlist("ALLADMIN.txt");
	DATABASE* Base=&base;
	ADMINLIST* Alist=&adlist;
	string cmd;
	do{
		cout<<"~$ ";
		fflush(stdin);
		getline(cin,cmd);
		if(cmd=="mySQL"){ 
			enter_login(Base,Alist);
			continue;
		}
	
		else if(cmd=="exit") return 0;
		else if(cmd[0]=='c'&&cmd[1]=='a'&&cmd[2]=='t'){
			int i=3;
			string text;
			while(cmd[i]==' ') i++;
			while(cmd[i]!=' '&&i<cmd.length()){
				text+=cmd[i];
				i++;
			}
			if(!Base->findFilename(text)){
				cout<<"~$ Error: File \""<<text<<"\" is not found."<<endl;
				continue;
			}
			else{
				TABLE* table=Base->getTableByFile(text);
				table->showTable(table->SELECT_BY_COLUMN_ALL());
				continue;
			}

		}
		else{
			cout<<"~$ Error: \""<<cmd<<"\" is not a valid command."<<endl;
			continue;
		}
	}while(true);
	return 0;
}

