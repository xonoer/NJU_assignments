#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
using namespace std;
struct AdminLogin{   //账号密码 
	string username;
	string password; 
	int try_again;
}; 
class Account{
	private:
		AdminLogin account;
	public:
		Account(FILE* pfile);//从文件导入账号密码 
		int login(string name,string pass);//判断登录成功 （0成功，1账号名错误，2密码错误，3账号冻结） 
		bool change_oldConfirm(string pass);//修改密码时，判断旧密码正误 
		int change_newLegal(string pass);	//判断新密码是否合规 (0合规，1长度大于12，2未同时包含数字与大小写字母 ） 
		bool change_newConsist(string pass1,string pass2);//修改密码时，判断两次新密码输入是否一致 
		void changePassword(string pass);
		string getUsername();
		int getTrynum();
		void unfreeze();
		void saveToFile(FILE* pfile);		//保存账号密码至文件 
		~Account(); 
};

bool has_num(string ch);
bool has_cap(string ch);
bool has_low(string ch);

#endif //ACCOUNT_H
