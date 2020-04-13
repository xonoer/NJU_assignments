#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "admin.h"

using namespace std;
struct DATA{
	int id;
	vector <string> values;
	DATA():id(-1){}
};
class TABLE{
	private:
		string tableName;
		int dataNum;
		string fileName;//检查文件名重复问题
		string ownerName;
		vector <DATA> content;
		int columnNum;
	public:
		TABLE(string name, DATA column, string file, string owner);//创建表
		TABLE(string name, string file, string owner); //读取表
		void INSERTtable(DATA target);//将目标插入表
		bool DELETE(DATA target);//删除满足目标的的数据
		void DELETEall();//删除所有数据
		vector <DATA> SELECT_BY_COLUMN(DATA target);//搜索满足target中包含列的所有信息
		vector <DATA> SELECT_BY_COLUMN_ALL();//展示整个表
		vector <DATA> SELECT_BY_COLUMN_DISTINCT(DATA target);//搜索满足目标包含列的不同信息
		vector <DATA> SELECT_BY_ORDER(DATA order, const string method);//按target中顺序排列表
		vector <DATA> SELECT_BY_KEY(DATA target, DATA key);//按照key要求搜索target包含列的信息
		vector <DATA> SELECT_BY_KEY_G(DATA target, DATA key);//����
		vector <DATA> SELECT_BY_KEY_GE(DATA target, DATA key);//���ڵ���
		vector <DATA> SELECT_BY_KEY_L(DATA target, DATA key);//С��
		vector <DATA> SELECT_BY_KEY_LE(DATA target, DATA key);//С�ڵ���
		void SELECT_BY_KEY_INTOFILE(DATA target, DATA key, const char* filename);//同上搜索写入文件
		void saveToFile();
		string getName();
		int getDataNum();
		DATA getColumn();
		int getColumnNum();
		string getFileName();
		string getOwner();
		void showTable(vector <DATA> target);
		void showTableWithoutId(vector <DATA> target);
		bool hasColumn(string column);
		~TABLE();
};
class DATABASE{
	private:
		int tableNum;
		string filename;
		vector <TABLE> detail;
	public:
		DATABASE(string file);//导入数据库列表，创建数据库类
		//触发TABLE构造函数
		bool CREATE_NEW(string name, DATA column, string file, string ownerName);
		bool CREATE_NEW_FROMFILE(string name, string file, string ownerName);
		//显式调用TABLE析构函数，删除文件
		bool DROP(string name);
		void saveToFile();
		//辅助函数
		int getTableNum();
		bool findTablename(string name);
		bool findFilename(string name);
		TABLE* getTable(string tableName);
		TABLE* getTableByFile(string fileName);
		~DATABASE();
		
};

struct PerInfo{
	string owner;
	string user;
	string tablename;
	string type;
};

class PER{
	private:
		int InfoNum;
		vector <PerInfo> request;
	public:
		PER();
		void per_denied(DATABASE* Base,ADMINLIST* Alist,string username, string tablename, string type);
		void check_per(DATABASE* Base,ADMINLIST* Alist,ADMIN* loged);
		bool delete_per(int num);
		void saveToFile();
		~PER();
};

#endif  //DATA_H

