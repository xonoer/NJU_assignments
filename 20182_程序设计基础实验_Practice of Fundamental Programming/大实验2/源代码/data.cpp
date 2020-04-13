#include "data.h"
#include <iomanip>
using namespace std;

TABLE::TABLE(string name, DATA column,  string file, string owner){//调试通过（创建新表）
	FILE* nfile=fopen(file.c_str(),"w");
	content.clear();
	tableName = name;
	dataNum = 0;
	fileName = file;
	ownerName = owner;
	column.id=0;
	columnNum = column.values.size();
	content.push_back(column);
	string title;
	for (int i = 0; i < columnNum; i++){
		title += column.values[i];
		title += '\t';
	}
	title += '\n';
	const char* s = title.c_str();
	fputs(s, nfile);
	fclose(nfile);

}

TABLE::TABLE(string name, string file, string owner){//调试通过（读取原表）
	FILE* ofile=fopen(file.c_str(),"r");
	content.clear();
	bool calculated = false;
	columnNum = 0;
	tableName = name;
	fileName = file;
	ownerName = owner;
	dataNum = -1;
	char ch[100];
	DATA t;
	while(fgets(ch, 100, ofile)){
		if(ch[0]=='\n') continue;
		t.values.clear();
		string s(ch);
		string ls;
		ls.clear();
		for(int i=0; i< s.length(); i++){
			if(s[i] != '\t' && s[i] != '\n'){
				char add = s[i];
				ls += add;
			}
			else{
				t.values.push_back(ls);
				ls.clear();
				if(!calculated) columnNum++;
			}
		}
		t.id = dataNum+1;
		content.push_back(t);
		dataNum++;
		calculated = true;

	}
	fclose(ofile);

}



void TABLE::INSERTtable(DATA target){//调试通过（新增信息）
	target.id = dataNum+1;
	content.push_back(target);
	dataNum++;
	saveToFile();
}

bool TABLE::DELETE(DATA target){//调试通过（删除满足目标的数据）
//PS：LINUX你真tm让我难受！
	  bool found=false;
 	 for(int i=1;i<=dataNum;){
		 bool found_thisround=false;
 	  	 for(int j=0;j<columnNum;j++){
 			if(j!=columnNum-1){
				if(target.values[j]=="\0"||target.values[j]==content[i].values[j]) continue;
				if(target.values[j]!="\0"&&target.values[j]!=content[i].values[j]) break;
			}
			else{
				if(target.values[j]!="\0"&&target.values[j]!=content[i].values[j]) break;
				else{
		 			 for(int k=i+1;k<=dataNum;k++){
						 content[k].id--;
					}
					content.erase(content.begin()+i,content.begin()+i+1);
					found=true;
					found_thisround=true;
					dataNum--;
					break;
				}
			}
		 }
		 if(!found_thisround) i++;
	 }
      saveToFile();
      return found;
}

void TABLE::DELETEall(){//（调试通过）删除所有数据
	content.erase(content.begin()+1,content.begin()+dataNum+1);
	dataNum=0;
	saveToFile();
}	

vector <DATA> TABLE::SELECT_BY_COLUMN(DATA target){
	vector <DATA> result;
	result.clear();
	bool init=true;
	for(int j=0;j<target.values.size();j++){
		for(int i=0;i<columnNum;i++){
			if(content[0].values[i]==target.values[j]){//第i列确定
				if(init){
					for(int k=0;k<=dataNum;k++){
						DATA add;
						add.id=content[k].id;
						add.values.clear();
						add.values.push_back(content[k].values[i]);
						result.push_back(add);
					}
					init=false;
				}
				else{
					for(int k=0;k<=dataNum;k++){
						result[k].values.push_back(content[k].values[i]);
					}
				}
				break;
			}
		}
	}
	return result;
}



vector <DATA> TABLE::SELECT_BY_COLUMN_ALL(){//调试通过（展示整个表）
	return content;
}

vector <DATA> TABLE::SELECT_BY_COLUMN_DISTINCT(DATA target){//调试通过（DISTINCT关键字）
	vector <DATA> result=SELECT_BY_COLUMN(target);
	for(int i=0;i<result.size();){
		bool deleted=false;
		for(int j=0;j<i;j++){
			if(result[i].values==result[j].values){
				result.erase(result.begin()+i,result.begin()+i+1);
				deleted=true;
				break;
			}
		}
		if(!deleted) i++;
	}
	return result;
}

vector <DATA> TABLE::SELECT_BY_ORDER(DATA order, const string method){//调试通过 order
	vector <DATA> result = content;
	for(int i=1;i<dataNum;i++){
		for (int j=i;j<=dataNum;j++){
			bool disorder=false;
			for(int k=0;k<order.values.size();k++){
				int co = 0;
				while(result[0].values[co]!=order.values[k]) co++;
				if(method=="ASC"? (result[i].values[co]>result[j].values[co]):(result[i].values[co]<result[j].values[co])) {
					disorder = true;
					break;
				}
				if(method=="ASC"? (result[i].values[co]<result[j].values[co]):(result[i].values[co]>result[j].values[co])){
					disorder = false;
					break;
				}
			}
			if (disorder){
				DATA temp=result[i];
				result[i]=result[j];
				result[j]=temp;
			}
		}
	}
	return result;
				
}

vector <DATA> TABLE::SELECT_BY_KEY(DATA target,DATA key){
	vector <DATA> result = SELECT_BY_COLUMN(target);
	int oi=1;
	for(int i=1;i<result.size();oi++){
		bool deleted=false;
		for(int j=0;j<key.values.size();j++){
			if(key.values[j]!=content[oi].values[j]&&key.values[j]!="\0"){
				result.erase(result.begin()+i,result.begin()+i+1);
				deleted=true;
				break;
			}
		}
		if(!deleted) i++;
	}
	return result;
}

vector <DATA> TABLE::SELECT_BY_KEY_G(DATA target,DATA key){
	vector <DATA> result = SELECT_BY_COLUMN(target);
	int oi=1;
	for(int i=1;i<result.size();oi++){
		bool deleted=false;
		for(int j=0;j<key.values.size();j++){
			if(key.values[j]>=content[oi].values[j]&&key.values[j]!="\0"){
				result.erase(result.begin()+i,result.begin()+i+1);
				deleted=true;
				break;
			}
		}
		if(!deleted) i++;
	}
	return result;
} 

vector <DATA> TABLE::SELECT_BY_KEY_GE(DATA target,DATA key){
	vector <DATA> result = SELECT_BY_COLUMN(target);
	int oi=1;
	for(int i=1;i<result.size();oi++){
		bool deleted=false;
		for(int j=0;j<key.values.size();j++){
			if(key.values[j]>content[oi].values[j]&&key.values[j]!="\0"){
				result.erase(result.begin()+i,result.begin()+i+1);
				deleted=true;
				break;
			}
		}
		if(!deleted) i++;
	}
	return result;
} 

vector <DATA> TABLE::SELECT_BY_KEY_L(DATA target,DATA key){
	vector <DATA> result = SELECT_BY_COLUMN(target);
	int oi=1;
	for(int i=1;i<result.size();oi++){
		bool deleted=false;
		for(int j=0;j<key.values.size();j++){
			if(key.values[j]<=content[oi].values[j]&&key.values[j]!="\0"){
				result.erase(result.begin()+i,result.begin()+i+1);
				deleted=true;
				break;
			}
		}
		if(!deleted) i++;
	}
	return result;
} 

vector <DATA> TABLE::SELECT_BY_KEY_LE(DATA target,DATA key){
	vector <DATA> result = SELECT_BY_COLUMN(target);
	int oi=1;
	for(int i=1;i<result.size();oi++){
		bool deleted=false;
		for(int j=0;j<key.values.size();j++){
			if(key.values[j]<content[oi].values[j]&&key.values[j]!="\0"){
				result.erase(result.begin()+i,result.begin()+i+1);
				deleted=true;
				break;
			}
		}
		if(!deleted) i++;
	}
	return result;
} 

void TABLE::SELECT_BY_KEY_INTOFILE(DATA target, DATA key, const char* filename){
	vector <DATA> result = SELECT_BY_KEY(target, key);
	FILE* pfile=fopen(filename,"w");
	for(int i=0;i<result.size();i++){
		string target;
		target.clear();
		for(int j=0;j<result[i].values.size();j++){
			target+=result[i].values[j];
			if(j!=result[i].values.size()-1) target+='\t';
		}
		target+='\n';
		fputs(target.c_str(),pfile);
	}
	fclose(pfile);

}

void TABLE::saveToFile(){//调试通过（保存文件）
	FILE* pfile=fopen(fileName.c_str(),"w");
	for(int i=0;i<=dataNum;i++){
		string target;
		target.clear();
		for(int j=0;j<columnNum;j++){
			target+=content[i].values[j];
			if(j!=columnNum-1) target+='\t';
		}
		target+='\n';
		fputs(target.c_str(),pfile);
	}
	fclose(pfile);
}


//辅助函数
string TABLE::getName(){
	return tableName;
}

int TABLE::getDataNum(){
	return dataNum;
}

DATA TABLE::getColumn(){
	return content[0];
}

int TABLE::getColumnNum(){
	return columnNum;
}

string TABLE::getFileName(){
	return fileName;
}

string TABLE::getOwner(){
	return ownerName;
}

void TABLE::showTable(vector <DATA> target){//（调试通过）展示表格（cat）
	for(int i=0;i<target.size();i++){
		if(target[i].id==0) cout<<left<<setw(4)<<"ID";
		else cout<<left<<setw(4)<<target[i].id;
		for(int j=0;j<target[i].values.size();j++){
			cout<<left<<setw(20)<<target[i].values[j];
		}
		cout<<endl;
	}
}

void TABLE::showTableWithoutId(vector <DATA> target){
	for(int i=0;i<target.size();i++){
		for(int j=0;j<target[i].values.size();j++){
			cout<<left<<setw(20)<<target[i].values[j];
		}
		cout<<endl;
	}
}

bool TABLE::hasColumn(string column){
	for(int i=0;i<columnNum;i++){
		if(content[0].values[i]==column) return true;
	}
	return false;
}

TABLE::~TABLE(){//删除表时显式调用一下析构函数
	content.clear();
	dataNum=0;
	columnNum=0;
}

DATABASE::DATABASE(string file){
	FILE* pfile=fopen(file.c_str(),"r");
	filename = file;
	tableNum = 0;
	detail.clear();
	char target[100];
	while(fgets(target,100,pfile)){
		if(target[0]=='\n') continue;
		string t(target);
		string tablename;
		string filename;
		string ownername;
		int num=0;
		for(int i=0;i<t.length();i++){
			if(t[i]!='\t'&&t[i]!='\n'){
				char ch=t[i];
				if(num==0) tablename+=ch;
				if(num==1) filename+=ch;
				if(num==2) ownername+=ch;
			}
			else{
				while(t[i+1]=='\t') i++;
				num++;
			}

		}
		TABLE thetable(tablename, filename, ownername);
		detail.push_back(thetable);
		tableNum++;
	}
}

bool DATABASE::CREATE_NEW(string name, DATA column, string file, string ownerName){
	if(findTablename(name)||findFilename(file)) return false;
	TABLE newtable(name,column,file,ownerName);
	detail.push_back(newtable);
	tableNum++;
	saveToFile();
	return true;
}

bool DATABASE::CREATE_NEW_FROMFILE(string name,string file, string ownerName){
	if(findTablename(name)||findFilename(file)) return false;
	TABLE newtable(name,file,ownerName);
	detail.push_back(newtable);
	tableNum++;
	saveToFile();
	return true;
}

bool DATABASE::DROP(string name){
	if(!findTablename(name)) return false;
	for(int i=0;i<tableNum;i++){
		if(detail[i].getName()==name){
			string file=detail[i].getFileName();
			detail[i].~TABLE();
			detail.erase(detail.begin()+i,detail.begin()+i+1);
			tableNum--;
			remove(file.c_str());
			break;
		}
	}
	saveToFile();
	return true;
}



void DATABASE::saveToFile(){
	FILE* pfile=fopen(filename.c_str(),"w");
	for(int i=0;i<tableNum;i++){
		string ch;
		ch+=detail[i].getName();
		ch+='\t';
		ch+=detail[i].getFileName();
		ch+='\t';
		ch+=detail[i].getOwner();
		ch+='\n';
		fputs(ch.c_str(),pfile);
	}
	fclose(pfile);
}


//辅助函数
int DATABASE::getTableNum(){
	return tableNum;
}

bool DATABASE::findTablename(string name){
	bool found=false;
	for(int i=0;i<tableNum;i++){
		if(detail[i].getName()==name) found=true;
	}
	return found;
}

bool DATABASE::findFilename(string name){
	bool found=false;
	for(int i=0;i<tableNum;i++){
		if(detail[i].getFileName()==name) found =true;
	}
	return found;
}


TABLE* DATABASE::getTable(string tableName){
	TABLE* target=NULL;
	for(int i=0;i<tableNum;i++){
		if(detail[i].getName()==tableName){
			target = &(detail[i]);
		}
	}
	return target;
}

TABLE* DATABASE::getTableByFile(string fileName){
	TABLE* target=NULL;
	for(int i=0;i<tableNum;i++){
		if(detail[i].getFileName()==fileName){
			target = &(detail[i]);
		}
	}
	return target;
}


DATABASE::~DATABASE(){
	detail.clear();
	tableNum=0;
}

PER::PER(){
	FILE* pfile=fopen("PERDENIED.txt","r");
	InfoNum=0;
	char ch[100];
	while(fgets(ch, 100, pfile)){
		PerInfo info; 
		if(ch[0]=='\n') continue;
		string s(ch);
		string ls;
		ls.clear();
		int num=0;
		string g;
		for(int i=0;i<s.length();i++){
			if(s[i]!='\t'&&s[i]!='\n'){
				ls+=s[i];
			}
			else{
				if(num==0) info.owner=ls;
				if(num==1) info.user=ls;
				if(num==2) info.tablename=ls;
				if(num==3) info.type=ls;
				ls.clear();
				num++;
			}
		}
		request.push_back(info);
		InfoNum++;
	} 
} 

void PER::per_denied(DATABASE* Base,ADMINLIST* Alist,string username, string tablename, string type){
	FILE* pfile=fopen("PERDENIED.txt","a");
	string target;
	string owner=Base->getTable(tablename)->getOwner();
	target+=owner;
	target+='\t';
	target+=username;
	target+='\t';
	target+=tablename;
	target+='\t';
	target+=type;
	target+='\n';
	fputs(target.c_str(),pfile);
	fclose(pfile);
}

void PER::check_per(DATABASE* Base,ADMINLIST* Alist,ADMIN* loged){
	for(int i=0;i<InfoNum;i++){
		if(request[i].owner!=loged->username) continue;
		else{
			cout<<"(mysql)==>[Permission request] \""<<request[i].user<<"\" requested "<<request[i].type<<" permission on table \""<<request[i].tablename<<"\". Grant or not?(Y/N)";
			do{
				string g;
				cin>>g;
				if(g=="Y"||g=="y"){
					Alist->GRANT(loged,Alist->getAdmin(request[i].user),request[i].tablename,request[i].type);
					cout<<"(mysql)==> Successfully granted "<<request[i].type<<" on \""<<request[i].tablename<<"\" to "<<request[i].user<<endl;
					delete_per(i);
					i--; 
					break;
				}
				else if(g=="N"||g=="n"){
					cout<<"(mysql)==> Request denied."<<endl;
					break;
				}
				else{
					cout<<"(mysql)==> Illegal input."<<endl;
					cout<<"(mysql)==>";
				}
			}while(true);
		}
	}
}

bool PER::delete_per(int num){
	if (num>=InfoNum) return false;
	request.erase(request.begin()+num,request.begin()+num+1);
	InfoNum--;
	saveToFile();
	return true;
}

void PER::saveToFile(){
	FILE* pfile=fopen("PERDENIED.txt","w");
	for(int i=0;i<InfoNum;i++){
		string target;
		target+=request[i].owner;
		target+='\t';
		target+=request[i].user;
		target+='\t';
		target+=request[i].tablename;
		target+='\t';
		target+=request[i].type;
		target+='\n';
		fputs(target.c_str(),pfile);
	}
}

PER::~PER(){
	request.clear();
	return;
}
