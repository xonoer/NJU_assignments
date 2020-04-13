#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "admin.h"

using namespace std;

void admin_run(){
	FILE* sfile=fopen("files\\songlist.txt","r");
	FILE* afile=fopen("files\\account.txt","r");
	if (afile==NULL||sfile==NULL){
		system("cls");
		cout<<endl<<endl<<endl;
		cout<<"                   错误提示"<<endl;
		cout<<"       ================================="<<endl;
		cout<<"       *后台管理系统本地文件缺失或异常。"<<endl;
		cout<<"       *抱歉！暂时无法启用后台管理系统。"<<endl;
		cout<<"       *请修复本地文件后，重新启动系统。"<<endl;
		cout<<"       ================================="<<endl;
		cout<<"       *";
		system("pause"); 
		return;
	}
	SongList allList(sfile);
	Account adminData(afile);
	SongList* pList=&allList;
	Account* pData=&adminData;
	fclose(sfile);
	fclose(afile);
	FILE *ffile=fopen("files\\suggestions.txt","r");
	SongList sugList;
	if(ffile!=NULL) sugList.createList_suggest(ffile);
	fclose(ffile);
	SongList* sList=&sugList;
	enter_login(pList,pData,sList);
}

void enter_login(SongList *pList,Account *pData,SongList *sList){
	FILE* afile=fopen("files\\account.txt","w");
	string name,pass;
	int result=-1;
	do{
		system("cls");
		cout<<endl;
		cout<<"     当前身份：工作人员"<<endl;
		cout<<endl;
		cout<<endl<<endl; 
		cout<<"                 后台管理人员统一身份认证"<<endl;
		cout<<"             ================================"<<endl;
		cout<<"               *用户名：";
		cin>>name;
		cout<<"               *密  码：";
		cin>>pass;
		result=pData->login(name,pass);
		pData->saveToFile(afile);
		if(afile) fclose(afile);
		if(result==0){
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *亲爱的"<<pData->getUsername()<<endl;
			cout<<"                  *欢迎登录本系统！" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(2000); 
			enter_adminMenu(pList,pData,sList); 
			return;
		} 
		if(result==1){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                      错误提示（201）"<<endl;
			cout<<"                  ====================="<<endl;
			cout<<"                  *您输入的用户名有误！"<<endl;
			cout<<"                  *请与管理员联系。" <<endl;
			cout<<"                  ====================="<<endl;
			cout<<"                  *";
			system("pause"); 
			return; 
		}
		if(result==2){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                             错误提示（202）"<<endl;
			cout<<"                  =================================="<<endl;
			if(pData->getTrynum()>0) 
			{	cout<<"                  *密码错误！您还有"<<pData->getTrynum()<<"次尝试机会。"<<endl;
				cout<<"                  *如果您忘记密码，请与管理员联系。" <<endl;
			}
			else
			{
				cout<<"                  *密码错误！您的尝试机会已经用光。"<<endl;
				cout<<"                  *您的账号已冻结，请与管理员联系。"<<endl; 
			}
			cout<<"                  =================================="<<endl;
			cout<<"                  *";
			system("pause"); 
			return; 
		}
		if(result==3){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                             错误提示（203）"<<endl;
			cout<<"                  =================================="<<endl;
			cout<<"                  *非常抱歉，您的账号已被冻结。"<<endl;
			cout<<"                  *为了解冻您的账号，请与管理员联系。" <<endl;
			cout<<"                  =================================="<<endl;
			cout<<"                  *";
			system("pause");
			return; 
		}
	}while(true);
}

void enter_adminMenu(SongList *pList,Account *pData,SongList *sList){
	char option='1';
	char m_option='0';
	do{
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<endl; 
		cout<<endl;
		if(option<'1'||option>'3'){
			cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"                       KTV点歌后台管理系统"<<endl;
		cout<<"                     ======================="<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     *    1.歌 单 管 理    *"<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     *    2.歌 曲 添 加    *"<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     *    3.账 号 管 理    *"<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     ======================="<<endl;
		cout<<"                 请输入选项序号：";
		printf("【 】\b\b\b");
		cin>>option;
		while(option=='1'){
			system("cls");
			cout<<"    当前版本：V1.1"<<endl;
			cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——歌单管理"<<endl; 
			cout<<endl;
			if(m_option<'0'||m_option>'3'){
				cout<<"         输入错误！请重新输入。"; 
			}
			cout<<endl<<endl;
			cout<<"                            歌 单 管 理"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    1.查看全部歌曲    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    2.修改删除歌曲    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    3.歌单排序设置    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    0.  返    回      *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                 请输入选项序号：";
			printf("【 】\b\b\b");
			cin>>m_option;
			if(m_option=='1') enter_adminShowAll(pList,pData);
			if(m_option=='2') enter_adminEdit(pList,pData);
			if(m_option=='3') enter_ranking(pList,pData);
			if(m_option=='0') break; 
		}
		while(option=='2'){
			int sugnum=sList->getSongnum();
			system("cls");
			cout<<"    当前版本：V1.1"<<endl;
			cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——歌曲添加"<<endl; 
			cout<<endl;
			if(m_option<'0'||m_option>'3'){
				cout<<"         输入错误！请重新输入。"; 
			}
			cout<<endl<<endl;
			cout<<"                            歌 曲 添 加"<<endl;
			if(sugnum!=0){
				cout<<"                   接收到用户共"<<sugnum<<"条反馈信息，请及时处理。"<<endl;
			}
			else{
				cout<<"                   暂未接收到用户的反馈信息。"<<endl;
			}
			cout<<"                     ========================"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    1.添加单个歌曲    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    2.批量导入歌曲    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    3.查看用户反馈    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    0.  返    回      *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                 请输入选项序号：";
			printf("【 】\b\b\b");
			cin>>m_option;
			if(m_option=='1') enter_add(pList,pData);
			if(m_option=='2') enter_volumnAdd(pList,pData);
			if(m_option=='3'&&sugnum!=0) enter_suggestAdd(pList,pData,sList);
			if(m_option=='0') break; 
		}
		while(option=='3'){
			system("cls");
			cout<<"    当前版本：V1.1"<<endl;
			cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——账号管理"<<endl; 
			cout<<endl;
			if(m_option<'0'||m_option>'2'){
				cout<<"         输入错误！请重新输入。"; 
			}
			cout<<endl<<endl;
			cout<<"                            账 号 管 理"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    1.修 改 密 码     *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    2.退 出 登 录     *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    0.返 回 主 页     *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                 请输入选项序号：";
			printf("【 】\b\b\b");
			cin>>m_option;
			if(m_option=='1'){
				bool flag=enter_changePass(pList,pData);
				if(flag) return;
			}
			if(m_option=='2') {
				system("cls");
				char ch='y';
				do{
					system("cls");
					cout<<endl;
					if(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N'){
					cout<<"         输入错误！请重新输入。"; 
					}
					cout<<endl<<endl<<endl<<endl;
					cout<<"                    您真的要退出后台管理系统吗？"<<endl;
					cout<<"                        是（Y）    否（N）"<<endl<<endl;
					cout<<"               请选择：";
					printf("【 】\b\b\b");
					cin>>ch;
					if(ch=='y'||ch=='Y'){
						system("cls");
						cout<<endl<<endl<<endl<<endl;
						cout<<"                  =================="<<endl;
						cout<<"                  *亲爱的"<<pData->getUsername()<<endl;
						cout<<"                  *您已成功退出登录！" <<endl;
						cout<<"                  =================="<<endl;
						Sleep(2000); 
						return;
					}
					if(ch=='n'||ch=='N') break;
				}while(true);
			}
			if(m_option=='0') break; 
			
		} 
	}while(true);
	 
}

void enter_adminShowAll(SongList *pList,Account *pData){
	int songnum=pList->getSongnum();
	if(songnum==0){
		system("cls");
		cout<<endl<<endl<<endl;
		cout<<"                    错误提示（301）"<<endl;
		cout<<"        ========================================"<<endl;
		cout<<"        *检测到歌单中不存在歌曲信息。"<<endl;
		cout<<"        *可能是歌单文件遭受到损坏。"<<endl;
		cout<<"        *如果你确认是因为人为操作导致歌单被清除，"<<endl;
		cout<<"        *请进入“添加歌曲”菜单添加歌曲。"<<endl;
		cout<<"        *如果文件损坏，请联系管理员处理。"<<endl; 
		cout<<"        ========================================="<<endl;
		cout<<"        *";
		system("pause");
		return;
	}
	int pagenum=(songnum%10==0)?(songnum/10):(songnum/10+1);
	int nowpage=1;
	int begin,finish;
	do{
		char ch;
		int id; 
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——歌单管理——全部歌曲"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_admin(begin,finish);
		cout<<"    全部"<<songnum<<"首歌，第"<<nowpage<<"页，共"<<pagenum<<"页。上一页（↑） 下一页（↓） 返回（ESC）"<<endl; 
		ch=getch(); 
		if(ch=='H'&&nowpage!=1) nowpage--;
		if(ch=='P'&&nowpage!=pagenum) nowpage++;
		if(ch==27)  break;
	}while(true);
}

void enter_adminEdit(SongList *pList,Account *pData){
	int songnum=pList->getSongnum();
	if(songnum==0){
		system("cls");
		cout<<endl<<endl<<endl;
		cout<<"                      错误提示（302）"<<endl;
		cout<<"        ========================================"<<endl;
		cout<<"        *检测到歌单中不存在歌曲信息。"<<endl;
		cout<<"        *可能是歌单文件遭受到损坏。"<<endl;
		cout<<"        *如果你确认是因为人为操作导致歌单被清除，"<<endl;
		cout<<"        *请进入“添加歌曲”菜单添加歌曲。"<<endl;
		cout<<"        *如果文件损坏，请联系管理员处理。"<<endl; 
		cout<<"        ========================================="<<endl;
		cout<<"        *";
		system("pause");
		return;
	}
	int pagenum=(songnum%10==0)?(songnum/10):(songnum/10+1);
	int nowpage=1;
	int begin,finish;
	do{
		songnum=pList->getSongnum();
		if (songnum==0){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                      错误提示（303）"<<endl;
			cout<<"     =============================================="<<endl;
			cout<<"     *由于您的各种操作，歌单内目前没有任何歌曲信息。"<<endl;
			cout<<"     *删除歌曲无法恢复，请至“添加歌曲”菜单添加歌曲。"<<endl;
			cout<<"     *如果出现文件损坏问题，请联系管理员处理。"<<endl;
			cout<<"     =============================================="<<endl;
			cout<<"     *";
			system("pause");
			return; 
		}
		pagenum=(songnum%10==0)?(songnum/10):(songnum/10+1);
		if(nowpage>pagenum) nowpage=pagenum;
		char ch;
		int id; 
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——歌单管理——修改删除歌曲"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_admin(begin,finish);
		cout<<"    全部"<<songnum<<"首歌，第"<<nowpage<<"页，共"<<pagenum<<"页。上一页（↑） 下一页（↓） 菜单（回车） 返回（ESC）"<<endl; 
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
				enter_adminDetail(pList,pData,id);
				break;
			}while(true);
		}
		if(ch==27)  break;
	}while(true);
}

void enter_adminDetail(SongList *pList,Account *pData,int id){
	SongInfo* p=pList->locateSong(id);
	char choice='0';
	do{
		system("cls"); 
		cout<<endl<<endl;
		if(choice<'0'||choice>'2'){
			cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"            歌曲详细信息                             请选择"<<endl;
		cout<<"       ======================                   ================"<<endl;
		cout<<"       *编    号："<<left<<setw(20)<<p->songId<<"\t\t"<<"*1.修改歌曲信息"<<endl;
		cout<<"       *歌    名："<<left<<setw(20)<<p->songName<<endl; 
		cout<<"       *拼音缩写："<<left<<setw(20)<<p->songAbbr<<"\t\t"<<"*2.从歌单中删除"<<endl;
		cout<<"       *歌    手："<<left<<setw(20)<<p->singerName<<endl; 
		cout<<"       *播 放 量："<<left<<setw(20)<<p->playedNum<<"\t\t"<<"*0.  返    回"<<endl; 
		cout<<"       *歌曲评分："<<left<<setw(20)<<p->songStar<<"\t\t"<<"================="<<endl;
		cout<<"       *评分人数："<<left<<setw(20)<<p->scoreNum<<endl;
		cout<<"       ======================="<<endl;
		cout<<"     请输入对应操作序号："; 
		printf("【 】\b\b\b");
		cin>>choice;
		if(choice=='0') return;
		if(choice=='1'){
			enter_editSong(pList,pData,p); 
		}
		if(choice=='2'){
			bool flag=enter_deleteConfirm(pList,pData,id);
			if(flag) return; 
		}
	}while(true);
}

void enter_editSong(SongList *pList,Account *pData,SongInfo* p){
	string name,singer,abbr;
	FILE* sfile=fopen("files\\songlist.txt","w");
	char choice='0';
	do{
		system("cls");
		cout<<endl<<endl;
		if(choice<'0'||choice>'3'){
			cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"       *您正在修改歌曲"<<left<<setw(11)<<p->songId<<"\t\t"<<"请选择："<<endl;
		cout<<"       ======================                   ============"<<endl;
		cout<<"       *当前歌名："<<left<<setw(15)<<p->songName<<"\t\t"<<"*1.修改歌名"<<endl; 
		cout<<"       *当前拼音："<<left<<setw(15)<<p->songAbbr<<"\t\t"<<"*2.修改拼音"<<endl;
		cout<<"       *当前歌手："<<left<<setw(15)<<p->singerName<<"\t\t"<<"*3.修改歌手"<<endl; 
		cout<<"       ======================"<<left<<setw(5)<<" "<<"\t\t"<<"*0.保    存"<<endl; 
		cout<<"                  "<<left<<setw(15)<<" "<<"\t\t"<<"============"<<endl;
		cout<<"     请输入对应操作序号："; 
		printf("【 】\b\b\b");
		cin>>choice;
		if(choice=='0') {
			pList->saveToFile(sfile);
			fclose(sfile);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *正在保存本地文件。"<<endl;
			cout<<"                  *请稍后..........." <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
			return;
			
		}
		if(choice=='1'){
			cout<<endl<<"     请输入修改后的歌曲名称：";
			cin>>name;
			singer=p->singerName;
			abbr=p->songAbbr;
			pList->correctInfo(p,name,singer,abbr);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *歌曲信息修改成功！"<<endl;
			cout<<"                  *正在返回上一界面。" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
		}
		if(choice=='2'){
			cout<<endl<<"     请输入修改后的歌曲拼音：";
			cin>>abbr;
			FILE* sfile=fopen("files:\\songlist.txt","w");
			singer=p->singerName;
			name=p->songName;
			pList->correctInfo(p,name,singer,abbr);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *歌曲信息修改成功！"<<endl;
			cout<<"                  *正在返回上一界面。" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
		} 
		if(choice=='3'){
			cout<<endl<<"     请输入修改后的歌手名称：";
			cin>>singer;
			FILE* sfile=fopen("files:\\songlist.txt","w");
			abbr=p->songAbbr;
			name=p->songName;
			pList->correctInfo(p,name,singer,abbr);
			pList->saveToFile(sfile);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *歌曲信息修改成功！"<<endl;
			cout<<"                  *正在返回上一界面。" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
		}
	}while(true);
}

bool enter_deleteConfirm(SongList *pList,Account *pData,int id){
	SongInfo* p=pList->locateSong(id);
	char choice='n';
	do{
		system("cls");
		cout<<endl<<endl;
		if(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N'){
		cout<<"     输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"                *WARNING!"<<endl;
		cout<<"      *您正准备删除歌曲"<<p->songId<<":";
		cout<<p->singerName<<"-"<<p->songName<<","<<endl;
		cout<<"      *删除后的歌曲将无法找回。您真的要继续吗?"<<endl;
		cout<<"      *是（Y）        否（N）"<<endl; 
		cout<<"     请做出您决定性的选择：";
		printf("【 】\b\b\b");
		cin>>choice; 
		if(choice=='n'||choice=='N') return false;
		if(choice=='y'||choice=='Y'){
			pList->deleteSongFromList(id);
			FILE* sfile=fopen("files\\songlist.txt","w");
			pList->saveToFile(sfile);
			fclose(sfile);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  ========================"<<endl;
			cout<<"                  *歌曲删除成功！"<<endl;
			cout<<"                  *正在保存本地文件......" <<endl;
			cout<<"                  *您无法恢复已删除的歌曲！"<<endl;
			cout<<"                  ========================"<<endl;
			Sleep(1800); 
			return true;
		} 
	}while(true);	
}

void enter_ranking(SongList *pList,Account* pData){
	char option='0';
	char choice='n'; 
	do{
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——歌单管理——歌单排序设置"<<endl; 
		cout<<endl;
		if(option<'0'||option>'2'){
			cout<<"         输入错误！请重新输入。"; 
		}
		cout<<endl<<endl;
		cout<<"                            歌 单 排 序 设 置"<<endl;
		cout<<"                     =============================="<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     *    1.按照用户评分高低排序  *"<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     *    2.按照播放数量高低排序  *"<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     *    0. 返 回 上 一 界 面    *"<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     =============================="<<endl;
		cout<<"                 请输入选项序号：";
		printf("【 】\b\b\b");
		cin>>option;
		if(option=='0') return;
		if(option=='1'){
			system("cls");
			cout<<endl<<endl;
			if(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N'){
			cout<<"     输入错误！请重新输入。"; 
			}
			cout<<endl<<endl;
			cout<<"      *您正准备按【评分】高低排序。"<<endl;
			cout<<"      *确定进行排序操作吗？"<<endl;
			cout<<"      *是（Y）        否（N）"<<endl; 
			cout<<"     请选择：";
			printf("【 】\b\b\b");
			cin>>choice; 
			if(choice=='n'||choice=='N')  continue;
			if(choice=='y'||choice=='Y'){
				FILE* sfile=fopen("files\\songlist.txt","w");
				pList->arrangeByStar();
				pList->saveToFile(sfile);
				fclose(sfile); 
				system("cls");
				cout<<endl<<endl<<endl<<endl;
				cout<<"                  ============================"<<endl;
				cout<<"                  *       歌单排序成功！"<<endl;
				cout<<"                  *     正在保存本地文件。" <<endl;
				cout<<"                  *您可以在退出后查看歌单情况。"<<endl;
				cout<<"                  ============================"<<endl;
				Sleep(2400); 
				return;
			}
		}
		if(option=='2'){
			system("cls");
			cout<<endl<<endl;
			if(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N'){
			cout<<"     输入错误！请重新输入。"; 
			}
			cout<<endl<<endl;
			cout<<"      *您正准备按【播放量】高低排序。"<<endl;
			cout<<"      *确定进行排序操作吗？"<<endl;
			cout<<"      *是（Y）        否（N）"<<endl; 
			cout<<"     请选择：";
			printf("【 】\b\b\b");
			cin>>choice; 
			if(choice=='n'||choice=='N')  continue;
			if(choice=='y'||choice=='Y'){
				FILE* sfile=fopen("files\\songlist.txt","w");
				pList->arrangeByPnum();
				pList->saveToFile(sfile);
				fclose(sfile); 
				system("cls");
				cout<<endl<<endl<<endl<<endl;
				cout<<"                  ============================"<<endl;
				cout<<"                  *       歌单排序成功！"<<endl;
				cout<<"                  *     正在保存本地文件。" <<endl;
				cout<<"                  *您可以在退出后查看歌单情况。"<<endl;
				cout<<"                  ============================"<<endl;
				Sleep(2400); 
				return;
			}
		}
	}while(true);
}

void enter_add(SongList* pList,Account* pData){
	char choice;
	char option; 
	SongInfo thesong;
	string name,singer,abbr;
	do{
		system("cls");
		cout<<endl<<endl;
		cout<<"      按下【回车】开始添加歌曲，按下【ESC】返回。"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"           添加歌曲"<<endl;
			cout<<"      ===================="<<endl;
			cout<<"      *歌曲名称：";
			cin>>name;
			thesong.songName=name;
			cout<<"      *歌曲拼音：";
			cin>>abbr;
			thesong.songAbbr=abbr;
			cout<<"      *歌手名称：";
			cin>>singer;
			thesong.singerName=singer;
			thesong.songId=pList->getSongnum()+1; 
			bool flag=pList->addToList(thesong);
			if(!flag){
				cout<<endl<<"      *歌曲添加失败！原因：歌曲已存在。"<<endl;
			}
			if(flag){
				cout<<endl<<"      *已成功添加歌曲"<<pList->getSongnum()<<":"<<singer<<"-"<<name<<endl; 
			}
			cout<<"      *";
			system("pause");	
		}
	}while(true);
}

void enter_volumnAdd(SongList *pList,Account *pData){
	char ch;
	do{
	
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——添加歌曲——批量导入歌曲"<<endl; 
		cout<<endl<<endl;
		cout<<"                        批量导入歌曲操作须知"<<endl;
		cout<<"     =============================================================="<<endl;
		cout<<"     *请将歌曲按照歌曲名、歌手、歌曲拼音的顺序写入一个txt文件中。"<<endl;
		cout<<"     *不同歌曲之间请换行隔开，同一歌曲的不同信息之间请用制表符隔开。"<<endl;
		cout<<"     *文件设置完成后，请将文件名（路径）输入至规定区域内，即可导入。"<<endl;
		cout<<"     *不按照规定格式排列歌曲、输错文件名（路径）可能会导致导入异常。"<<endl;
		cout<<"     *导入完成后，您可以至歌单管理-修改歌曲信息处对歌曲信息进行修改。"<<endl;
		cout<<"     ==============================================================="<<endl;
		cout<<"   （我已阅读批量导入歌曲操作须知）按【回车】键确认，按【ESC】键取消。"<<endl;
		ch=getch();
		if(ch==27) return;
		if(ch=='\r'){
			while(true){
				system("cls");
				char Filename[100];
				int first=pList->getSongnum()+1;
				cout<<endl<<endl<<endl;
				cout<<"                       批量导入"<<endl;
				cout<<"   =================================================="<<endl; 
				cout<<"   *请输入文件名（路径）："; 
				cin>>Filename;
				const char* filename=Filename;
				FILE* afile=fopen(filename,"r");
				if(afile==NULL){
					cout<<endl<<"    *未找到目标文件。"<<endl<<"    *导入失败！"<<endl;
					cout<<"     *";
					system("pause");
					return;
				}
				cout<<endl;
				pList->volumnAddToList(afile);
				fclose(afile);
				FILE* sfile=fopen("files\\songlist.txt","w");
				pList->saveToFile(sfile);
				fclose(sfile);
				cout<<endl<<"    *导入成功歌曲如下："<<endl;
				int last=pList->getSongnum();
				for(int i=first;i<=last;i++){
					SongInfo* p=pList->locateSong(i);
					cout<<"    *"<<p->songId<<":"<<p->singerName<<"-"<<p->songName<<endl; 
				}
				cout<<endl<<"    *";
				system("pause");
				return;
			}
		}
	}while(true);
}

bool enter_changePass(SongList *pList,Account *pData){
	char ch;
	string opass,npass,npass2; 
	do{
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——账号管理——修改密码"<<endl; 
		cout<<endl<<endl;
		cout<<"             修改密码操作须知"<<endl;
		cout<<"     ========================================="<<endl;
		cout<<"     *修改密码前，请先确认原密码。"<<endl;
		cout<<"     *新密码中必须包含大、小写字母与数字。"<<endl; 
		cout<<"     *新密码长度不得超过12个字符，不得包含空格。"<<endl;
		cout<<"     *密码修改完成后，请重新登录，验证账号。"<<endl;
		cout<<"     ========================================="<<endl;
		cout<<"   （我已阅读修改密码操作须知）按【回车】键确认，按【ESC】键取消。" <<endl<<endl;
		ch=getch();
		if(ch==27) return false;
		if(ch=='\r'){
			system("cls");
			cout<<endl<<endl;
			cout<<"        *修改密码"<<endl;
			cout<<"        ==================="<<endl;
			cout<<"        原密码:";
			cin>>opass;
			if(!pData->change_oldConfirm(opass)){
				system("cls");
				cout<<endl<<endl;
				cout<<"               错误提示"<<endl; 
				cout<<"          ================="<<endl;
				cout<<"          *原密码验证错误。"<<endl;
				cout<<"          *密码修改失败。"<<endl; 
				cout<<"          ================="<<endl;
				Sleep(1200);
				return false; 
			}
			cout<<"        新密码:";
			cin>>npass;
			if(pData->change_newLegal(npass)==1) {
				system("cls");
				cout<<endl<<endl;
				cout<<"                   错误提示"<<endl; 
				cout<<"          =========================="<<endl;
				cout<<"          *密码长度不得超过12个字符。"<<endl;
				cout<<"          *密码修改失败。"<<endl; 
				cout<<"          =========================="<<endl;
				Sleep(2400);
				return false; 
			} 
			if(pData->change_newLegal(npass)==2){
				system("cls");
				cout<<endl<<endl;
				cout<<"                        错误提示"<<endl; 
				cout<<"          ===================================="<<endl;
				cout<<"          *密码必须同时包含大、小写字母与数字。"<<endl;
				cout<<"          *密码修改失败。"<<endl; 
				cout<<"          ===================================="<<endl;
				Sleep(2400);
				return false; 
			}
			cout<<"        确认新密码:";
			cin>>npass2;
			if(!pData->change_newConsist(npass,npass2)){
				system("cls");
				cout<<endl<<endl;
				cout<<"                  错误提示"<<endl; 
				cout<<"          ======================="<<endl;
				cout<<"          *两次输入密码不一致。"<<endl;
				cout<<"          *密码修改失败。"<<endl; 
				cout<<"          ======================="<<endl;
				Sleep(2400);
				return false; 
			}
			else{
				FILE* afile=fopen("files\\account.txt","w");
				pData->changePassword(npass);
				pData->saveToFile(afile);
				fclose(afile);
				system("cls");
				cout<<endl<<endl;
				cout<<"                  修改成功！"<<endl; 
				cout<<"          ===================="<<endl;
				cout<<"          *密码修改成功。"<<endl;
				cout<<"          *即将登出重新登录。"<<endl; 
				cout<<"          ===================="<<endl;
				Sleep(2400);
				return true; 
			} 
		} 
	}while(true);
}

void enter_suggestAdd(SongList *pList,Account *pData,SongList* sList){
	FILE* ffile=fopen("files\\suggestions.txt","w");
	int sugnum=sList->getSongnum();
	int now=1;
	char ch;
	string abbr; 
	do{
		SongInfo *p=sList->locateSong(now);
		system("cls");
		cout<<"    当前版本：V1.1"<<endl;
		cout<<"    当前界面：后台管理"<<pData->getUsername()<<"——添加歌曲——反馈信息"<<endl; 
		cout<<endl<<endl;;
		cout<<"          反馈信息处理（第"<<now<<"条，共"<<sugnum<<"条）"<<endl;
		cout<<"    ========================================="<<endl;
		cout<<"    *歌曲名："<<p->songName<<endl;
		cout<<"    *歌手名："<<p->singerName<<endl;
		cout<<"    ========================================="<<endl;
		cout<<"    按上【↑】下【↓】键翻页，按【回车】处理反馈信息，按【ESC】返回。"<<endl;
		ch=getch();
		if(ch==27) {
			
			FILE* sfile=fopen("files\\songlist.txt","w");
			pList->saveToFile(sfile); 
			sList->saveToFile_suggest(ffile);
			fclose(sfile);
			fclose(ffile);
			return;
		}
		if(ch=='\r'){
			cout<<"    *请输入歌曲拼音缩写（输入0删除该反馈信息）：";
			cin>>abbr;
			if(abbr=="0"){
				FILE* sfile=fopen("files\\songlist.txt","w");
				cout<<"    *反馈处理成功！"<<endl;
				sList->deleteSongFromList(now);
				Sleep(1000);
				if(sList->getSongnum()==0) {
					pList->saveToFile(sfile); 
					sList->saveToFile_suggest(ffile);
					fclose(sfile);
					fclose(ffile);
					return;
				}
				else continue;
			} 
			SongInfo thesong=(*p);
			thesong.songAbbr=abbr;
			thesong.songId=pList->getSongnum()+1;
			if(pList->addToList(thesong)){
				FILE* sfile=fopen("files\\songlist.txt","w");
				cout<<"    *添加成功！"<<endl;
				sList->deleteSongFromList(now);
				Sleep(1000);
				if(sList->getSongnum()==0) {
					pList->saveToFile(sfile); 
					sList->saveToFile_suggest(ffile);
					fclose(sfile);
					fclose(ffile);
					return;
				}
				else continue;
			}
			else{
				FILE* sfile=fopen("files\\songlist.txt","w");
				cout<<"    *失败！原因：歌曲已存在。正在为您删除此反馈消息。"<<endl; 
				sList->deleteSongFromList(now);
				Sleep(1000);
				if(sList->getSongnum()==0) {
					pList->saveToFile(sfile); 
					sList->saveToFile_suggest(ffile);
					fclose(sfile);
					fclose(ffile);
					return;
				}
				else continue;
			} 
		}
		if(ch=='H'&&now!=1) now--;
		if(ch=='P'&&now!=sugnum) now++;
	}while(true);
}

