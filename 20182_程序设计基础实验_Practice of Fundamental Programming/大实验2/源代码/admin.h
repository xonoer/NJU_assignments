#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;
struct AUTH{
	string tableName;
	bool owner;
	vector <string> DROP;
	vector <string> INSERT;
	vector <string> DELETE;
	vector <string> SELECT;
	AUTH(){DROP.clear();INSERT.clear();DELETE.clear();SELECT.clear();}
};

struct ADMIN{
	string username;
	string password;
	vector <AUTH> authInfo;
};

class ADMINLIST{
	private:
		int adminNum;
		vector <ADMIN> users;
		ADMIN* loged;
	public:
		ADMINLIST(string adfile);
		bool GRANT(ADMIN* from, ADMIN* to,string table,string type);
		bool REVOKE(ADMIN* from, ADMIN* to,string table,string type);
		void AddTable(string table,string owner);
		void DropTable(string table);
		bool LOGIN(string username, string pass);
		void LOGOUT();
		void saveToFile();
		//辅助函数
		ADMIN* getAdmin(string username);
		ADMIN* getLogedAdmin();
		AUTH* getAT(string username, string table);
		vector <AUTH*> getAuthedTable(string username);
		bool hasRight(string username,string table,const string type);
		bool isOwner(string username,string table);	
		//测试
		void test();
};
#endif //ADMIN_H
