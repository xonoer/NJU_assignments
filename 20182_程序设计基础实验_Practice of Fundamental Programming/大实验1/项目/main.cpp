#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include "song.h"
#include "account.h"
#include "admin.h"
#include "user.h"
using namespace std;
void enter_main();//������ 
void confirm_exit();//ȷ���˳� 
int main(int argc, char *argv[]) {
	enter_main();
	return 0;
}
void enter_main(){
	string n="0";
	do{
		system("cls");
		cout<<"��ǰ�汾��V1.1"<<endl;
		cout<<endl;
		if(n<"0"||n>"2"){
		cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;;
		cout<<"                  ��ӭʹ��KTV���ϵͳ"<<endl; 
		cout<<"              =========================="<<endl;
		cout<<"              *      1. �û�ֱ��       *"<<endl;
		cout<<"              *      2. ��̨����       *"<<endl;
		cout<<"              *      0. �˳�ϵͳ       *"<<endl;
		cout<<"              =========================="<<endl<<endl;
		cout<<"              ������ѡ����ţ�";
		printf("�� ��\b\b\b");
		cin>>n;
		if(n=="0"){
			confirm_exit();
			return;
		}
		if(n=="2"){
			admin_run();
		}
		if(n=="1"){
			user_run();
		}
	}while(true) ;
}
void confirm_exit(){
	char ch='y';
	do{
		system("cls");
		cout<<endl;
		if(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N'){
		cout<<"         ����������������롣"; 
		}
		
		cout<<endl<<endl<<endl<<endl;
		cout<<"                    �����Ҫ�˳���"<<endl;
		cout<<"                   �ǣ�Y��    ��N��"<<endl<<endl;
		cout<<"               ��ѡ��";
		printf("�� ��\b\b\b");
		cin>>ch;
	}while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N');
	if(ch=='y'||ch=='Y'){
		system("cls");
		cout<<endl<<endl<<endl<<endl;
		cout<<"                 =========================="<<endl;
		cout<<"                 * ��л��ʹ��KTV���ϵͳ��*"<<endl;
		cout<<"                 *      ��ӭ�´�ʹ�ã�    *"<<endl;
		cout<<"                 =========================="<<endl;
		Sleep(2000);
		return;
	}
	if(ch=='n'||ch=='N'){
		enter_main();
		return;
	}
}
	/*test for SONG_H
	FILE* pfile=fopen("testfiles\\songlist2.txt","r");
	SongList a(pfile);
	a.showList_admin(0,5);
	cout<<"����"<<a.getSongnum()<<"�׸�"<<endl; 
	cout<<"�ѵ�"<<a.getPickednum()<<"�׸�"<<endl; 
	if(pfile) fclose(pfile);
	vector <SongInfo> find=a.searchByAbbr("cc");
	for(vector<SongInfo>::iterator it=find.begin();it!=find.end();it++)
    cout<<(*it).songName<<" ";
    a.scoreSong(a.locateSong(1),0);
    a.showList_admin(0,5);
	cout<<"����"<<a.getSongnum()<<"�׸�"<<endl; 
	cout<<"�ѵ�"<<a.getPickednum()<<"�׸�"<<endl; 
	a.pickSong(a.locateSong(1));
	a.pickSong(a.locateSong(2));
	a.pickSong(a.locateSong(3));
	a.pickSong(a.locateSong(4));
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"����"<<a.getSongnum()<<"�׸�"<<endl; 
	cout<<"�ѵ�"<<a.getPickednum()<<"�׸�"<<endl; 
	a.switchSong();
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"����"<<a.getSongnum()<<"�׸�"<<endl; 
	cout<<"�ѵ�"<<a.getPickednum()<<"�׸�"<<endl; 
	a.topSong(4);
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"����"<<a.getSongnum()<<"�׸�"<<endl; 
	cout<<"�ѵ�"<<a.getPickednum()<<"�׸�"<<endl; 
	a.switchSong();
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"����"<<a.getSongnum()<<"�׸�"<<endl; 
	cout<<"�ѵ�"<<a.getPickednum()<<"�׸�"<<endl; 
	*/
	/* test of ACCOUNT_H
	FILE* pfile=fopen("testfiles\\adminaccount.txt","r");
	FILE* qfile=fopen("testfiles\\adminaccount2.txt","w");
	Account b(pfile);
	if(pfile) fclose(pfile);
	string user,pass,newpass1,newpass2;
	cin>>user>>pass;
	cout<<b.login(user,pass)<<endl;
	cin>>newpass1>>newpass2;
	cout<<b.change_newLegal(newpass1)<<endl;
	cout<<b.change_newConsist(newpass1,newpass2)<<endl;
	b.changePassword(newpass1);
	b.saveToFile(qfile);
	if(qfile) fclose(qfile);
	*/ 

