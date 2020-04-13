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
		cout<<"           ��Ŷ��������(101)��"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *ϵͳ�����ļ������⵽�𻵡�"<<endl;
		cout<<"      *��¼�쳣���볢���޸��ļ���"<<endl;
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
		cout<<"           ��Ŷ��������(102)��"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *ϵͳ�����ļ������⵽�𻵡�"<<endl;
		cout<<"      *��¼�쳣���볢���޸��ļ���"<<endl;
		cout<<"      ==========================="<<endl;
		cout<<"      *";
		system("pause");
		return; 
	}
	fclose(sfile);
	system("cls");
	cout<<endl<<endl<<endl;
	cout<<"             ======================="<<endl;
	cout<<"             *��ӭ��ʹ��KTV���ϵͳ��"<<endl;
	cout<<"             *���̿�ʼ����K��֮�ã�" <<endl;
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
			now=next="������裡";
			hint4="(�޲�����)"; 
		}
		if(pdnum==1){
			next="������裡";
			SongInfo* song1=pList->locatePickedSong(1);
			now+=song1->singerName;
			now+='-';
			now+=song1->songName; 
			hint4="4.�����и�";
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
			hint4="4.�����и�";
		}
		system("cls");
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺�û�ϵͳ"<<endl; 
		cout<<endl;
		if(option<'0'||option>'5'){
			cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"                 KTV���ϵͳ������ӭ�����װ����û�"<<endl;
		cout<<"             ========================================"<<endl;
		cout<<"             *                                      *"<<endl;
		cout<<"             *    1.���и���          3.�ѵ����    *    ���ڲ��ţ�"<<now<<endl;
		cout<<"             *                                      *"<<endl;
		cout<<"             *    2.��ʼ���          "<<hint4<<"    *"<<endl;
		cout<<"             *                                      *    ��һ�ף�"<<next<<endl;
		cout<<"             *              5.��    ��              *"<<endl;
		cout<<"             *                                      *"<<endl; 
		cout<<"             *              0.��    ��              *"<<endl;
		cout<<"             *                                      *"<<endl;
		cout<<"             ========================================"<<endl;
		cout<<"           ������ѡ����ţ�";
		printf("�� ��\b\b\b");
		cin>>option;
		if(option=='0'){
			do{
				system("cls");
				char ch='n';
				cout<<endl;
				if(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N'){
				cout<<"         ����������������롣"; 
				}
		
				cout<<endl<<endl<<endl;
				if(pdnum>=1) cout<<"      ��ʾ������ǰ����Ϊ������ɵĸ������˳�������ѵ��б�"; 
				cout<<endl;
				cout<<"                    �����Ҫ�˳���"<<endl;
				cout<<"                   �ǣ�Y��    ��N��"<<endl<<endl;
				cout<<"               ��ѡ��";
				printf("�� ��\b\b\b");
				cin>>ch;
				if(ch=='y'||ch=='Y'){
					system("cls");
					cout<<endl<<endl<<endl<<endl;
					cout<<"                  =========================="<<endl;
					cout<<"                  *�װ����û��������˳��ɹ���"<<endl;
					cout<<"                  *��л��ʹ��KTV���ϵͳ��" <<endl;
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
				cout<<"    ��ǰ�汾��V1.1"<<endl;
				cout<<"    ��ǰ���棺�û�ϵͳ"<<"�������"<<endl; 
				cout<<endl;
				if(m_option<'0'||m_option>'3'){
					cout<<"         ����������������롣"; 
				}
				cout<<endl<<endl;
				cout<<"                            �� ʼ �� ��"<<endl;
				cout<<"                     ========================"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    1.����������      *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    2.����������      *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    3.ƴ��ģ������    *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     *    0.����������      *"<<endl;
				cout<<"                     *                      *"<<endl;
				cout<<"                     ========================"<<endl;
				cout<<"                 ������ѡ����ţ�";
				printf("�� ��\b\b\b");
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺�û�ϵͳ"<<"�������и���"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_user(begin,finish);
		cout<<"    ȫ��"<<songnum<<"�׸裬��"<<nowpage<<"ҳ����"<<pagenum<<"ҳ����һҳ������ ��һҳ������ �˵����س������أ�ESC��"<<endl; 
		ch=getch(); 
		if(ch=='H'&&nowpage!=1) nowpage--;
		if(ch=='P'&&nowpage!=pagenum) nowpage++;
		if(ch=='\r'){
			do{
				cout<<"    �����������ţ��Բ鿴������ϸ��Ϣ������0���أ���";
				cin>>id;
				if(id==0) break;
				if(id<begin+1||id>finish+1){
					cout<<"    ��Ŷ�������û��������ȷ�ı��Ŷ��"<<endl;
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
			hint1="*1.��    ��";
			hint2="*2.�ö����"; 
		}
		if(status==1){
			hint1="�����ڲ��ţ�";
			hint2="�����ڲ��ţ�"; 
		}
		if(status==2){
			hint1="�������ѵ㣩";
			hint2="���������ö���"; 
		}
		if(status>2){
			hint1="�������ѵ㣩";
			hint2="*2.�ö�����";
		}
		system("cls"); 
		cout<<status; 
		cout<<endl<<endl;
		if(choice<'0'||choice>'2'){
			cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"            ������ϸ��Ϣ                             ��ѡ��"<<endl;
		cout<<"       ======================                   =============="<<endl;
		cout<<"       *��    �ţ�"<<left<<setw(20)<<p->songId<<"\t\t"<<hint1<<endl;
		cout<<"       *��    ����"<<left<<setw(20)<<p->songName<<endl; 
		cout<<"       *ƴ����д��"<<left<<setw(20)<<p->songAbbr<<"\t\t"<<hint2<<endl;
		cout<<"       *��    �֣�"<<left<<setw(20)<<p->singerName<<endl; 
		cout<<"       *�� �� ����"<<left<<setw(20)<<p->playedNum<<"\t\t"<<"*0.��    ��"<<endl; 
		cout<<"       *�������֣�"<<left<<setw(20)<<p->songStar<<"\t\t"<<"==============="<<endl;
		cout<<"       *����������"<<left<<setw(20)<<p->scoreNum<<endl;
		cout<<"       ======================="<<endl;
		cout<<"     �������Ӧ������ţ�"; 
		printf("�� ��\b\b\b");
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
			cout<<"          *���ѳɹ���裡" <<endl;
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
			cout<<"          *���ѳɹ��ö�������" <<endl;
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
			cout<<"    ��ǰ�汾��V1.1"<<endl;
			cout<<"    ��ǰ���棺�û�ϵͳ"<<"�������и���"<<endl; 
			cout<<endl;
			cout<<endl<<endl;
			cout<<"      *��Ŷ������û�е��Ŷ����ȥ�����б���ɣ�"<<endl;
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺�û�ϵͳ"<<"�����ѵ����"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_picked(begin,finish);
		cout<<"    ȫ��"<<songnum<<"�׸裬��"<<nowpage<<"ҳ����"<<pagenum<<"ҳ����һҳ������ ��һҳ������ �˵����س��� ���أ�ESC��"<<endl; 
		ch=getch(); 
		if(ch=='H'&&nowpage!=1) nowpage--;
		if(ch=='P'&&nowpage!=pagenum) nowpage++;
		if(ch=='\r'){
			do{
				cout<<endl;
				cout<<"          ��������"<<endl;
				cout<<"     ================"<<endl;
				cout<<"     *1.�и�  *3.�Ƴ�"<<endl;
				cout<<"     *2.�ö�  *0.����"<<endl;
				cout<<"     ================"<<endl; 
				cout<<"        ��ѡ��";
				cin>>m_option;
				if(m_option=='0') break;
				if(m_option=='1'){
					id=pList->getId(1);
					enter_switch(pList,id);
					break;
				}
				if(m_option=='2'){
					cout<<"        �������ö�������ţ�����0���أ���";
					cin>>id;
					if(id==0)break; 
					while(id<2||id>pList->getPickednum()){
						cout<<"  �����������ö�������ţ�����0���أ���";
						cin>>id; 
						if(id==0)break;
					}
					pList->topSong(pList->getId(id));
					cout<<"        *�ö��ɹ���"<<endl;
					Sleep(1000);
					break; 
				}
				if(m_option=='3'){
					cout<<"        �������Ƴ�������ţ�����0���أ���"; 
					cin>>id;
					if(id==0)break;
					while(id<2||id>pList->getPickednum()){
						cout<<"  �����������Ƴ�������ţ�����0���أ���";
						cin>>id; 
						if(id==0)break;
					}
					pList->removeSong(pList->getId(id));
					cout<<"        *�Ƴ��ɹ���"<<endl;
					Sleep(1000);
					break;
				}
				cout<<"      ѡ�����"<<endl;
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
		cout<<"                   �и�ɹ���"<<endl;
		cout<<"        =============================="<<endl;
		cout<<"        *��ӭ���Ը�����"<<p->singerName<<'-'<<p->songName<<"���������֣�"<<endl;
		cout<<"             ";
		for(int i=1;i<=star;i++)cout<<"��";
		for(int i=1;i<=5-star;i++)cout<<"��";
		cout<<"��"<<star<<"�֣�"<<endl;
		cout<<"        =============================="<<endl;
		cout<<"     �����󡾡����ҡ����������ķ����������س���ȷ�ϣ�����ESC��ȡ�����֡�" <<endl;
		ch=getch();
		if(ch=='K'&&star!=0) star--;
		if(ch=='M'&&star!=5) star++;
		if(ch==27) return;
		if(ch=='\r'){
			pList->scoreSong(p,star);
			FILE* sfile=fopen("files\\songlist.txt","w");
			pList->saveToFile(sfile);
			fclose(sfile);
			cout<<"        *���ֳɹ���"<<endl;
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
		cout<<"      ���¡��س�����ʼ�������������¡�ESC�����ء�"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"     *������Ҫ�����ĸ�������";
			cin>>singer;
			vector<SongInfo> List=pList->searchBySinger(singer);
			bool flag=showList(List);
			if(!flag){
				cout<<"     *";
				system("pause");
			}
			if(flag){
				do{
					cout<<"     *������Ҫ��ĸ�����ţ�����0��������"; 
					cin>>id;
					if(id==0) break;
					if(!hasSong(List,id)) cout<<"     *�������"<<endl;
					else{
						SongInfo* p=pList->locateSong(id);
						if(p->songStatus>0){
							cout<<"     *���󣡸����ѵ㡣"<<endl;
							continue;
						}
						pList->pickSong(p);
						cout<<"     *��衰"<<p->singerName<<'-'<<p->songName<<"���ɹ���"<<endl; 
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
		cout<<"      ���¡��س�����ʼ�������������¡�ESC�����ء�"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"     *������Ҫ�����ĸ�������";
			cin>>name;
			vector<SongInfo> List=pList->searchByName(name);
			bool flag=showList(List);
			if(!flag){
				cout<<"     *";
				system("pause");
			}
			if(flag){
				do{
					cout<<"     *������Ҫ��ĸ�����ţ�����0��������"; 
					cin>>id;
					if(id==0) break;
					if(!hasSong(List,id)) cout<<"     *�������"<<endl;
					else{
						SongInfo* p=pList->locateSong(id);
						if(p->songStatus>0){
							cout<<"     *���󣡸����ѵ㡣"<<endl;
							continue;
						}
						pList->pickSong(p);
						cout<<"     *��衰"<<p->singerName<<'-'<<p->songName<<"���ɹ���"<<endl; 
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
		cout<<"      ���¡��س�����ʼ�������������¡�ESC�����ء�"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"     *������Ҫ������ƴ����";
			cin>>abbr;
			vector<SongInfo> List=pList->searchByAbbr(abbr);
			bool flag=showList(List);
			if(!flag){
				cout<<"     *";
				system("pause");
			}
			if(flag){
				do{
					cout<<"     *������Ҫ��ĸ�����ţ�����0��������"; 
					cin>>id;
					if(id==0) break;
					if(!hasSong(List,id)) cout<<"     *�������"<<endl;
					else{
						SongInfo* p=pList->locateSong(id);
						if(p->songStatus>0){
							cout<<"     *���󣡸����ѵ㡣"<<endl;
							continue;
						}
						pList->pickSong(p);
						cout<<"     *��衰"<<p->singerName<<'-'<<p->songName<<"���ɹ���"<<endl; 
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺�û�ϵͳ"<<"���������ύ"<<endl; 
		cout<<endl<<endl;
		cout<<"                 �û���������ָ��"<<endl;
		cout<<"    =========================================="<<endl;
		cout<<"    *û����Ҫ��ĸ������������ǣ����ǰ������ϣ�"<<endl; 
		cout<<"    *�����·�����������Լ����֣���л���������"<<endl;
		cout<<"    =========================================="<<endl;
		cout<<"    ���¡��س�����ʼ�����¡�ESC������"<<endl;
		ch=getch();
		if(ch==27) {
			suggestList.saveToFile_suggest(ffile);
			fclose(ffile);
			return;
		}
		if(ch=='\r'){
			cout<<"    *��������";
			cin>>name;
			cout<<"    *��������"; 
			cin>>singer;
			SongInfo thesong;
			thesong.songName=name;
			thesong.singerName=singer;
			thesong.songId=suggestList.getSongnum()+1;
			suggestList.addToList(thesong);
			cout<<"    *�ɹ�����л���������"<<endl;
			Sleep(1800);
		}
	}while(true);
}

bool showList(vector<SongInfo> List){
	int num=List.size();
	if(num==0){
		cout<<"     *�ܱ�Ǹ��δ��ϵͳ��ƥ�䵽���������ĸ�����"<<endl;
		cout<<"     *����ƴд�����Ի����ؼ��ʡ�"<<endl;
		return false; 
	}
	else{
		cout<<"     *����ϵͳ��ƥ�䵽����"<<num<<"�׸�����"<<endl;
		cout<<"\t"<<setw(5)<<"���"<<setw(20)<<"������"<<setw(20)<<"����"<<"\t"<<"����״̬"<<endl; 
		cout<<"     ============================================================"<<endl;
		for(int i=0;i<num;i++){
			SongInfo p=List[i];
			cout<<"\t"<<setw(5)<<p.songId<<setw(20)<<p.songName<<setw(20)<<p.singerName<<"\t";
			if(p.songStatus==1) cout<<"���ڲ���";
			if(p.songStatus>=2)  cout<<"  �ѵ�"; 
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
