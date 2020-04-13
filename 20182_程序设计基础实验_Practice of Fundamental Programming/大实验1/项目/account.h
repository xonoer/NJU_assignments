#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
using namespace std;
struct AdminLogin{   //�˺����� 
	string username;
	string password; 
	int try_again;
}; 
class Account{
	private:
		AdminLogin account;
	public:
		Account(FILE* pfile);//���ļ������˺����� 
		int login(string name,string pass);//�жϵ�¼�ɹ� ��0�ɹ���1�˺�������2�������3�˺Ŷ��ᣩ 
		bool change_oldConfirm(string pass);//�޸�����ʱ���жϾ��������� 
		int change_newLegal(string pass);	//�ж��������Ƿ�Ϲ� (0�Ϲ棬1���ȴ���12��2δͬʱ�����������Сд��ĸ �� 
		bool change_newConsist(string pass1,string pass2);//�޸�����ʱ���ж����������������Ƿ�һ�� 
		void changePassword(string pass);
		string getUsername();
		int getTrynum();
		void unfreeze();
		void saveToFile(FILE* pfile);		//�����˺��������ļ� 
		~Account(); 
};

bool has_num(string ch);
bool has_cap(string ch);
bool has_low(string ch);

#endif //ACCOUNT_H
