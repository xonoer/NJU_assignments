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
void enter_main();//主界面 
void confirm_exit();//确认退出 
int main(int argc, char *argv[]) {
	enter_main();
	return 0;
}
void enter_main(){
	string n="0";
	do{
		system("cls");
		cout<<"当前版本：V1.1"<<endl;
		cout<<endl;
		if(n<"0"||n>"2"){
		cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;;
		cout<<"                  欢迎使用KTV点歌系统"<<endl; 
		cout<<"              =========================="<<endl;
		cout<<"              *      1. 用户直达       *"<<endl;
		cout<<"              *      2. 后台管理       *"<<endl;
		cout<<"              *      0. 退出系统       *"<<endl;
		cout<<"              =========================="<<endl<<endl;
		cout<<"              请输入选项序号：";
		printf("【 】\b\b\b");
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
		cout<<"         输入错误！请重新输入。"; 
		}
		
		cout<<endl<<endl<<endl<<endl;
		cout<<"                    您真的要退出吗？"<<endl;
		cout<<"                   是（Y）    否（N）"<<endl<<endl;
		cout<<"               请选择：";
		printf("【 】\b\b\b");
		cin>>ch;
	}while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N');
	if(ch=='y'||ch=='Y'){
		system("cls");
		cout<<endl<<endl<<endl<<endl;
		cout<<"                 =========================="<<endl;
		cout<<"                 * 感谢您使用KTV点歌系统！*"<<endl;
		cout<<"                 *      欢迎下次使用！    *"<<endl;
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
	cout<<"共有"<<a.getSongnum()<<"首歌"<<endl; 
	cout<<"已点"<<a.getPickednum()<<"首歌"<<endl; 
	if(pfile) fclose(pfile);
	vector <SongInfo> find=a.searchByAbbr("cc");
	for(vector<SongInfo>::iterator it=find.begin();it!=find.end();it++)
    cout<<(*it).songName<<" ";
    a.scoreSong(a.locateSong(1),0);
    a.showList_admin(0,5);
	cout<<"共有"<<a.getSongnum()<<"首歌"<<endl; 
	cout<<"已点"<<a.getPickednum()<<"首歌"<<endl; 
	a.pickSong(a.locateSong(1));
	a.pickSong(a.locateSong(2));
	a.pickSong(a.locateSong(3));
	a.pickSong(a.locateSong(4));
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"共有"<<a.getSongnum()<<"首歌"<<endl; 
	cout<<"已点"<<a.getPickednum()<<"首歌"<<endl; 
	a.switchSong();
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"共有"<<a.getSongnum()<<"首歌"<<endl; 
	cout<<"已点"<<a.getPickednum()<<"首歌"<<endl; 
	a.topSong(4);
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"共有"<<a.getSongnum()<<"首歌"<<endl; 
	cout<<"已点"<<a.getPickednum()<<"首歌"<<endl; 
	a.switchSong();
	a.showList_user(0,5);
	a.showList_picked(0,a.getPickednum()-1);
	cout<<"共有"<<a.getSongnum()<<"首歌"<<endl; 
	cout<<"已点"<<a.getPickednum()<<"首歌"<<endl; 
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

