#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "user.h"
using namespace std;

void user_run(){
	FILE* sfile=fopen("files\\songlist.txt","r");
	if(sfile==NULL){
		system("cls");
		cout<<endl<<endl<<endl;
		cout<<"           啊哦！出错了(101)！"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *系统本地文件可能遭到损坏。"<<endl;
		cout<<"      *登录异常，请尝试修复文件。"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *";
		system("pause");
		return; 
	}
	SongList allList(sfile);
	SongList* pList=&allList;
	if(pList->getSongnum()==0){
		system("cls");
		cout<<endl<<endl<<endl;
		cout<<"           啊哦！出错了(102)！"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *系统本地文件可能遭到损坏。"<<endl;
		cout<<"      *登录异常，请尝试修复文件。"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *";
		system("pause");
		return; 
	}
	fclose(sfile);
	system("cls");
	cout<<endl<<endl<<endl;
	cout<<"             ======================="<<endl;
	cout<<"             *欢迎您使用KTV点歌系统！"<<endl;
	cout<<"             *即刻开始您的K歌之旅！" <<endl;
	cout<<"             ======================="<<endl;
	Sleep(2000); 
	enter_userMenu(pList);
}

void enter_userMenu(SongList *pList){
	char option='0';
	do{
		int pdnum=pList->getPickednum();
		string now;
		string next;
		string hint4;
		if(pdnum==0) {
			now=next="请您点歌！";
			hint4="(无播放曲)"; 
		}
		if(pdnum==1){
			next="请您点歌！";
			SongInfo* song1=pList->locatePickedSong(1);
			now+=song1->singerName;
			now+='-';
			now+=song1->songName; 
			hint4="4.快速切歌";
		}
		if(pdnum>=2){
			SongInfo *song1=pList->locatePickedSong(1);
			SongInfo *song2=pList->locatePickedSong(2);
			now+=song1->singerName;
			now+='-';
			now+=song1->songName; 
			next+=song2->singerName;
			next+='-';
			next+=song2->songName;
			hint4="4.快速切歌";
		}
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：用户系统"<<endl; 
		cout<<endl;
		if(option<'0'||option>'5'){
			cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"                 KTV点歌系统——欢迎您！亲爱的用户"<<endl;
		cout<<"             ========================================"<<endl;
		cout<<"             *                                      *"<<endl;
		cout<<"             *    1.所有歌曲          3.已点歌曲    *    正在播放："<<now<<endl;
		cout<<"             *                                      *"<<endl;
		cout<<"             *    2.开始点歌          "<<hint4<<"    *"<<endl;
		cout<<"             *                                      *    下一首："<<next<<endl;
		cout<<"             *              5.反    馈              *"<<endl;
		cout<<"             *                                      *"<<endl; 
		cout<<"             *              0.退    出              *"<<endl;
		cout<<"             *                                      *"<<endl;
		cout<<"             ========================================"<<endl;
		cout<<"           请输入选项序号：";
		printf("【 】\b\b\b");
		cin>>option;
		if(option=='0'){
			do{
				system("cls");
				char ch='n';
				cout<<endl;
				if(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N'){
				cout<<"         输入错误！请重新输入。"; 
				}
		
				cout<<endl<<endl<<endl;
				if(pdnum>=1) cout<<"      提示：您当前还有为播放完成的歌曲，退出将清空已点列表。"; 
				cout<<endl;
				cout<<"                    您真的要退出吗？"<<endl;
				cout<<"                   是（Y）    否（N）"<<endl<<endl;
				cout<<"               请选择：";
				printf("【 】\b\b\b");
				cin>>ch;
				if(ch=='y'||ch=='Y'){
					system("cls");
					cout<<endl<<endl<<endl<<endl;
					cout<<"                  =========================="<<endl;
					cout<<"                  *亲爱的用户，您已退出成功！"<<endl;
					cout<<"                  *感谢您使用KTV点歌系统！" <<endl;
					cout<<"                  =========================="<<endl;
					Sleep(2000); 
					return;
				}
				if(ch=='n'||ch=='N') break;
			}while(true);
		}
		if(option=='1')  enter_userShowAll(pList);
		if(option=='3')  enter_showPicked(pList);
		if(option=='5')  enter_feedback(pList);
		if(option=='4'&&pdnum!=0) {
			int id=pList->getId(1);
			enter_switch(pList,id);
		} 
		if(option=='2'){
			do{
				char m_option='0';
				system("cls");
				cout<<"    当前版本：V1.1"<<endl;
				cout<<"    当前界面：用户系统"<<"——点歌"<<endl; 
				cout<<endl;
				if(m_option<'0'||m_option>'3'){
					cout<<"         输入错误！请重新输入。"; 
				}
				cout<<endl<<endl;
				cout<<"                            开 始 点 歌"<<endl;
				cout<<"                     ========================"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    1.歌曲名搜索      *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    2.歌手名搜索      *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    3.拼音模糊搜索    *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    0.返回主界面      *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     ========================"<<endl;
				cout<<"                 请输入选项序号：";
				printf("【 】\b\b\b");
				cin>>m_option;
				if(m_option=='0') break; 
				if(m_option=='2') enter_pickBySinger(pList);
				if(m_option=='1') enter_pickByName(pList);
				if(m_option=='3') enter_pickByAbbr(pList);
			}while(true);
		}
	}while(true);
}

void enter_userShowAll(SongList *pList){
	int songnum=pList->getSongnum();

	int pagenum=(songnum%10==0)?(songnum/10):(songnum/10+1);
	int nowpage=1;
	int begin,finish;
	do{
		char ch;
		int id; 
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：用户系统"<<"——所有歌曲"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_user(begin,finish);
		cout<<"    全部"<<songnum<<"首歌，第"<<nowpage<<"页，共"<<pagenum<<"页。上一页（↑） 下一页（↓） 菜单（回车）返回（ESC）"<<endl; 
		ch=getch(); 
		if(ch=='H'&&nowpage!=1) nowpage--;
		if(ch=='P'&&nowpage!=pagenum) nowpage++;
		if(ch=='\r'){
			do{
				cout<<"    请输入歌曲编号，以查看歌曲详细信息（输入0返回）：";
				cin>>id;
				if(id==0) break;
				if(id<begin+1||id>finish+1){
					cout<<"    啊哦！你好像没有输入正确的编号哦！"<<endl;
					continue;
				}
				enter_userDetail(pList,id);
				break;
			}while(true);
		}
		if(ch==27)  break;
	}while(true);
} 

void enter_userDetail(SongList *pList,int id){
	SongInfo* p=pList->locateSong(id);
	char choice='0';
	do{
		int status=p->songStatus;
		string hint1,hint2;
		
		if(status==0){
			hint1="*1.点    歌";
			hint2="*2.置顶点歌"; 
		}
		if(status==1){
			hint1="（正在播放）";
			hint2="（正在播放）"; 
		}
		if(status==2){
			hint1="（歌曲已点）";
			hint2="（歌曲已置顶）"; 
		}
		if(status>2){
			hint1="（歌曲已点）";
			hint2="*2.置顶歌曲";
		}
		system("cls"); 
		cout<<status; 
		cout<<endl<<endl;
		if(choice<'0'||choice>'2'){
			cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"            歌曲详细信息                             请选择"<<endl;
		cout<<"       ======================                   =============="<<endl;
		cout<<"       *编    号："<<left<<setw(20)<<p->songId<<"\t\t"<<hint1<<endl;
		cout<<"       *歌    名："<<left<<setw(20)<<p->songName<<endl; 
		cout<<"       *拼音缩写："<<left<<setw(20)<<p->songAbbr<<"\t\t"<<hint2<<endl;
		cout<<"       *歌    手："<<left<<setw(20)<<p->singerName<<endl; 
		cout<<"       *播 放 量："<<left<<setw(20)<<p->playedNum<<"\t\t"<<"*0.返    回"<<endl; 
		cout<<"       *歌曲评分："<<left<<setw(20)<<p->songStar<<"\t\t"<<"==============="<<endl;
		cout<<"       *评分人数："<<left<<setw(20)<<p->scoreNum<<endl;
		cout<<"       ======================="<<endl;
		cout<<"     请输入对应操作序号："; 
		printf("【 】\b\b\b");
		cin>>choice;
		if(choice=='0') return;
		if(choice=='1'&&status==0){
			pList->pickSong(p);
			FILE* sfile=fopen("files\\songlist.txt","w");
			pList->saveToFile(sfile);
			fclose(sfile);
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"          ======================="<<endl;
			cout<<"          *您已成功点歌！" <<endl;
			cout<<"          *"<<p->singerName<<"-"<<p->songName<<endl;
			cout<<"          ======================="<<endl;
			Sleep(1500);
		}
		if(choice=='2'&&status!=1&&status!=2){
			if(status==0) {
				pList->pickSong(p);
				FILE* sfile=fopen("files\\songlist.txt","w");
				pList->saveToFile(sfile);
				fclose(sfile);
			}
			pList->topSong(id);
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"          ======================="<<endl;
			cout<<"          *您已成功置顶歌曲！" <<endl;
			cout<<"          *"<<p->singerName<<"-"<<p->songName<<endl;
			cout<<"          ======================="<<endl;
			Sleep(1500);
			
		}
	}while(true);
}

void enter_showPicked(SongList *pList){
	int songnum=pList->getPickednum();
		
	
	int pagenum=(songnum%10==0)?(songnum/10):(songnum/10+1);
	int nowpage=1;
	int begin,finish;
	do{
		
		songnum=pList->getPickednum();
		if(songnum==0){
			system("cls");
			cout<<"    当前版本：V1.1"<<endl;
			cout<<"    当前界面：用户系统"<<"——所有歌曲"<<endl; 
			cout<<endl;
			cout<<endl<<endl;
			cout<<"      *啊哦！您还没有点歌哦！快去歌曲列表点歌吧！"<<endl;
			cout<<"      *";
			system("pause");
			return;
		}
		pagenum=(songnum%10==0)?(songnum/10):(songnum/10+1);
		if(nowpage>pagenum) nowpage=pagenum;
		char ch;
		char m_option='\0';
		int id; 
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：用户系统"<<"——已点歌曲"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_picked(begin,finish);
		cout<<"    全部"<<songnum<<"首歌，第"<<nowpage<<"页，共"<<pagenum<<"页。上一页（↑） 下一页（↓） 菜单（回车） 返回（ESC）"<<endl; 
		ch=getch(); 
		if(ch=='H'&&nowpage!=1) nowpage--;
		if(ch=='P'&&nowpage!=pagenum) nowpage++;
		if(ch=='\r'){
			do{
				cout<<endl;
				cout<<"          歌曲操作"<<endl;
				cout<<"     ================"<<endl;
				cout<<"     *1.切歌  *3.移除"<<endl;
				cout<<"     *2.置顶  *0.返回"<<endl;
				cout<<"     ================"<<endl; 
				cout<<"        请选择：";
				cin>>m_option;
				if(m_option=='0') break;
				if(m_option=='1'){
					id=pList->getId(1);
					enter_switch(pList,id);
					break;
				}
				if(m_option=='2'){
					cout<<"        请输入置顶歌曲编号（输入0返回）：";
					cin>>id;
					if(id==0)break; 
					while(id<2||id>pList->getPickednum()){
						cout<<"  错误！请输入置顶歌曲编号（输入0返回）：";
						cin>>id; 
						if(id==0)break;
					}
					pList->topSong(pList->getId(id));
					cout<<"        *置顶成功！"<<endl;
					Sleep(1000);
					break; 
				}
				if(m_option=='3'){
					cout<<"        请输入移除歌曲编号（输入0返回）："; 
					cin>>id;
					if(id==0)break;
					while(id<2||id>pList->getPickednum()){
						cout<<"  错误！请输入移除歌曲编号（输入0返回）：";
						cin>>id; 
						if(id==0)break;
					}
					pList->removeSong(pList->getId(id));
					cout<<"        *移除成功！"<<endl;
					Sleep(1000);
					break;
				}
				cout<<"      选择错误！"<<endl;
				Sleep(1000);
				break; 
			}while(true);
		}
		if(ch==27)  break;
	}while(true);
}

void enter_switch(SongList *pList,int id){
	SongInfo *p=pList->locateSong(id);
	pList->switchSong();
	char ch;
	int star=5;
	do{
		system("cls");
		
		cout<<endl<<endl<<endl;
		cout<<"                   切歌成功！"<<endl;
		cout<<"        =============================="<<endl;
		cout<<"        *欢迎您对歌曲“"<<p->singerName<<'-'<<p->songName<<"”进行评分！"<<endl;
		cout<<"             ";
		for(int i=1;i<=star;i++)cout<<"★";
		for(int i=1;i<=5-star;i++)cout<<"☆";
		cout<<"（"<<star<<"分）"<<endl;
		cout<<"        =============================="<<endl;
		cout<<"     按下左【←】右【→】键更改分数，按【回车】确认，按【ESC】取消评分。" <<endl;
		ch=getch();
		if(ch=='K'&&star!=0) star--;
		if(ch=='M'&&star!=5) star++;
		if(ch==27) return;
		if(ch=='\r'){
			pList->scoreSong(p,star);
			FILE* sfile=fopen("files\\songlist.txt","w");
			pList->saveToFile(sfile);
			fclose(sfile);
			cout<<"        *评分成功！"<<endl;
			Sleep(1000);
			return;
		}
	}while(true);
}

void enter_pickBySinger(SongList *pList){
	char choice;
	string singer;
	int id;
	do{
		system("cls");
		cout<<endl<<endl;
		cout<<"      按下【回车】开始搜索歌曲，按下【ESC】返回。"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"     *请输入要搜索的歌手名：";
			cin>>singer;
			vector<SongInfo> List=pList->searchBySinger(singer);
			bool flag=showList(List);
			if(!flag){
				cout<<"     *";
				system("pause");
			}
			if(flag){
				do{
					cout<<"     *请输入要点的歌曲编号（输入0结束）："; 
					cin>>id;
					if(id==0) break;
					if(!hasSong(List,id)) cout<<"     *输入错误！"<<endl;
					else{
						SongInfo* p=pList->locateSong(id);
						if(p->songStatus>0){
							cout<<"     *错误！歌曲已点。"<<endl;
							continue;
						}
						pList->pickSong(p);
						cout<<"     *点歌“"<<p->singerName<<'-'<<p->songName<<"”成功！"<<endl; 
					}
				}while(true);
			}
		}
		
	}while(true);
}

void enter_pickByName(SongList *pList){
	char choice;
	string name;
	int id;
	do{
		system("cls");
		cout<<endl<<endl;
		cout<<"      按下【回车】开始搜索歌曲，按下【ESC】返回。"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"     *请输入要搜索的歌曲名：";
			cin>>name;
			vector<SongInfo> List=pList->searchByName(name);
			bool flag=showList(List);
			if(!flag){
				cout<<"     *";
				system("pause");
			}
			if(flag){
				do{
					cout<<"     *请输入要点的歌曲编号（输入0结束）："; 
					cin>>id;
					if(id==0) break;
					if(!hasSong(List,id)) cout<<"     *输入错误！"<<endl;
					else{
						SongInfo* p=pList->locateSong(id);
						if(p->songStatus>0){
							cout<<"     *错误！歌曲已点。"<<endl;
							continue;
						}
						pList->pickSong(p);
						cout<<"     *点歌“"<<p->singerName<<'-'<<p->songName<<"”成功！"<<endl; 
					}
				}while(true);
			}
		}
		
	}while(true);
}

void enter_pickByAbbr(SongList *pList){
	char choice;
	string abbr;
	int id;
	do{
		system("cls");
		cout<<endl<<endl;
		cout<<"      按下【回车】开始搜索歌曲，按下【ESC】返回。"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"     *请输入要搜索的拼音：";
			cin>>abbr;
			vector<SongInfo> List=pList->searchByAbbr(abbr);
			bool flag=showList(List);
			if(!flag){
				cout<<"     *";
				system("pause");
			}
			if(flag){
				do{
					cout<<"     *请输入要点的歌曲编号（输入0结束）："; 
					cin>>id;
					if(id==0) break;
					if(!hasSong(List,id)) cout<<"     *输入错误！"<<endl;
					else{
						SongInfo* p=pList->locateSong(id);
						if(p->songStatus>0){
							cout<<"     *错误！歌曲已点。"<<endl;
							continue;
						}
						pList->pickSong(p);
						cout<<"     *点歌“"<<p->singerName<<'-'<<p->songName<<"”成功！"<<endl; 
					}
				}while(true);
			}
		}
		
	}while(true);
}

void enter_feedback(SongList *pList){
	FILE* rfile=fopen("files\\suggestions.txt","r");
	SongList suggestList;
	if(rfile!=NULL) suggestList.createList_suggest(rfile);
	fclose(rfile);
	FILE* ffile=fopen("files\\suggestions.txt","w");
	char ch;
	string name;
	string singer;
	do{
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：用户系统"<<"——反馈提交"<<endl; 
		cout<<endl<<endl;
		cout<<"                 用户反馈操作指南"<<endl;
		cout<<"    =========================================="<<endl;
		cout<<"    *没有想要点的歌曲？告诉我们，我们帮您添上！"<<endl; 
		cout<<"    *请在下方输入歌曲名以及歌手，感谢您的意见！"<<endl;
		cout<<"    =========================================="<<endl;
		cout<<"    按下【回车】开始；按下【ESC】返回"<<endl;
		ch=getch();
		if(ch==27) {
			suggestList.saveToFile_suggest(ffile);
			fclose(ffile);
			return;
		}
		if(ch=='\r'){
			cout<<"    *歌曲名：";
			cin>>name;
			cout<<"    *歌手名："; 
			cin>>singer;
			SongInfo thesong;
			thesong.songName=name;
			thesong.singerName=singer;
			thesong.songId=suggestList.getSongnum()+1;
			suggestList.addToList(thesong);
			cout<<"    *成功！感谢您的意见！"<<endl;
			Sleep(1800);
		}
	}while(true);
}

bool showList(vector<SongInfo> List){
	int num=List.size();
	if(num==0){
		cout<<"     *很抱歉！未在系统中匹配到符合条件的歌曲！"<<endl;
		cout<<"     *请检查拼写，或尝试换个关键词。"<<endl;
		return false; 
	}
	else{
		cout<<"     *已在系统中匹配到以下"<<num<<"首歌曲："<<endl;
		cout<<"\t"<<setw(5)<<"编号"<<setw(20)<<"歌曲名"<<setw(20)<<"歌手"<<"\t"<<"歌曲状态"<<endl; 
		cout<<"     ============================================================"<<endl;
		for(int i=0;i<num;i++){
			SongInfo p=List[i];
			cout<<"\t"<<setw(5)<<p.songId<<setw(20)<<p.songName<<setw(20)<<p.singerName<<"\t";
			if(p.songStatus==1) cout<<"正在播放";
			if(p.songStatus>=2)  cout<<"  已点"; 
			cout<<endl;
		}
		return true;
	}
}

bool hasSong(vector<SongInfo> List,int id){
	int num=List.size();
	if(num==0) return false;
	for(int i=0;i<num;i++){
		if(List[i].songId==id) return true;
	}
	return false;
} 
