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
		cout<<"                   ������ʾ"<<endl;
		cout<<"       ================================="<<endl;
		cout<<"       *��̨����ϵͳ�����ļ�ȱʧ���쳣��"<<endl;
		cout<<"       *��Ǹ����ʱ�޷����ú�̨����ϵͳ��"<<endl;
		cout<<"       *���޸������ļ�����������ϵͳ��"<<endl;
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
		cout<<"     ��ǰ��ݣ�������Ա"<<endl;
		cout<<endl;
		cout<<endl<<endl; 
		cout<<"                 ��̨������Աͳһ�����֤"<<endl;
		cout<<"             ================================"<<endl;
		cout<<"               *�û�����";
		cin>>name;
		cout<<"               *��  �룺";
		cin>>pass;
		result=pData->login(name,pass);
		pData->saveToFile(afile);
		if(afile) fclose(afile);
		if(result==0){
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *�װ���"<<pData->getUsername()<<endl;
			cout<<"                  *��ӭ��¼��ϵͳ��" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(2000); 
			enter_adminMenu(pList,pData,sList); 
			return;
		} 
		if(result==1){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                      ������ʾ��201��"<<endl;
			cout<<"                  ====================="<<endl;
			cout<<"                  *��������û�������"<<endl;
			cout<<"                  *�������Ա��ϵ��" <<endl;
			cout<<"                  ====================="<<endl;
			cout<<"                  *";
			system("pause"); 
			return; 
		}
		if(result==2){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                             ������ʾ��202��"<<endl;
			cout<<"                  =================================="<<endl;
			if(pData->getTrynum()>0) 
			{	cout<<"                  *�������������"<<pData->getTrynum()<<"�γ��Ի��ᡣ"<<endl;
				cout<<"                  *������������룬�������Ա��ϵ��" <<endl;
			}
			else
			{
				cout<<"                  *����������ĳ��Ի����Ѿ��ù⡣"<<endl;
				cout<<"                  *�����˺��Ѷ��ᣬ�������Ա��ϵ��"<<endl; 
			}
			cout<<"                  =================================="<<endl;
			cout<<"                  *";
			system("pause"); 
			return; 
		}
		if(result==3){
			system("cls");
			cout<<endl<<endl<<endl;
			cout<<"                             ������ʾ��203��"<<endl;
			cout<<"                  =================================="<<endl;
			cout<<"                  *�ǳ���Ǹ�������˺��ѱ����ᡣ"<<endl;
			cout<<"                  *Ϊ�˽ⶳ�����˺ţ��������Ա��ϵ��" <<endl;
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<endl; 
		cout<<endl;
		if(option<'1'||option>'3'){
			cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"                       KTV����̨����ϵͳ"<<endl;
		cout<<"                     ======================="<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     *    1.�� �� �� ��    *"<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     *    2.�� �� �� ��    *"<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     *    3.�� �� �� ��    *"<<endl;
		cout<<"                     *                     *"<<endl;
		cout<<"                     ======================="<<endl;
		cout<<"                 ������ѡ����ţ�";
		printf("�� ��\b\b\b");
		cin>>option;
		while(option=='1'){
			system("cls");
			cout<<"    ��ǰ�汾��V1.1"<<endl;
			cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����赥����"<<endl; 
			cout<<endl;
			if(m_option<'0'||m_option>'3'){
				cout<<"         ����������������롣"; 
			}
			cout<<endl<<endl;
			cout<<"                            �� �� �� ��"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    1.�鿴ȫ������    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    2.�޸�ɾ������    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    3.�赥��������    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    0.  ��    ��      *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                 ������ѡ����ţ�";
			printf("�� ��\b\b\b");
			cin>>m_option;
			if(m_option=='1') enter_adminShowAll(pList,pData);
			if(m_option=='2') enter_adminEdit(pList,pData);
			if(m_option=='3') enter_ranking(pList,pData);
			if(m_option=='0') break; 
		}
		while(option=='2'){
			int sugnum=sList->getSongnum();
			system("cls");
			cout<<"    ��ǰ�汾��V1.1"<<endl;
			cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����������"<<endl; 
			cout<<endl;
			if(m_option<'0'||m_option>'3'){
				cout<<"         ����������������롣"; 
			}
			cout<<endl<<endl;
			cout<<"                            �� �� �� ��"<<endl;
			if(sugnum!=0){
				cout<<"                   ���յ��û���"<<sugnum<<"��������Ϣ���뼰ʱ����"<<endl;
			}
			else{
				cout<<"                   ��δ���յ��û��ķ�����Ϣ��"<<endl;
			}
			cout<<"                     ========================"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    1.��ӵ�������    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    2.�����������    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    3.�鿴�û�����    *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    0.  ��    ��      *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                 ������ѡ����ţ�";
			printf("�� ��\b\b\b");
			cin>>m_option;
			if(m_option=='1') enter_add(pList,pData);
			if(m_option=='2') enter_volumnAdd(pList,pData);
			if(m_option=='3'&&sugnum!=0) enter_suggestAdd(pList,pData,sList);
			if(m_option=='0') break; 
		}
		while(option=='3'){
			system("cls");
			cout<<"    ��ǰ�汾��V1.1"<<endl;
			cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����˺Ź���"<<endl; 
			cout<<endl;
			if(m_option<'0'||m_option>'2'){
				cout<<"         ����������������롣"; 
			}
			cout<<endl<<endl;
			cout<<"                            �� �� �� ��"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    1.�� �� �� ��     *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    2.�� �� �� ¼     *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     *    0.�� �� �� ҳ     *"<<endl;
			cout<<"                     *                      *"<<endl;
			cout<<"                     ========================"<<endl;
			cout<<"                 ������ѡ����ţ�";
			printf("�� ��\b\b\b");
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
					cout<<"         ����������������롣"; 
					}
					cout<<endl<<endl<<endl<<endl;
					cout<<"                    �����Ҫ�˳���̨����ϵͳ��"<<endl;
					cout<<"                        �ǣ�Y��    ��N��"<<endl<<endl;
					cout<<"               ��ѡ��";
					printf("�� ��\b\b\b");
					cin>>ch;
					if(ch=='y'||ch=='Y'){
						system("cls");
						cout<<endl<<endl<<endl<<endl;
						cout<<"                  =================="<<endl;
						cout<<"                  *�װ���"<<pData->getUsername()<<endl;
						cout<<"                  *���ѳɹ��˳���¼��" <<endl;
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
		cout<<"                    ������ʾ��301��"<<endl;
		cout<<"        ========================================"<<endl;
		cout<<"        *��⵽�赥�в����ڸ�����Ϣ��"<<endl;
		cout<<"        *�����Ǹ赥�ļ����ܵ��𻵡�"<<endl;
		cout<<"        *�����ȷ������Ϊ��Ϊ�������¸赥�������"<<endl;
		cout<<"        *����롰��Ӹ������˵���Ӹ�����"<<endl;
		cout<<"        *����ļ��𻵣�����ϵ����Ա����"<<endl; 
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����赥������ȫ������"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_admin(begin,finish);
		cout<<"    ȫ��"<<songnum<<"�׸裬��"<<nowpage<<"ҳ����"<<pagenum<<"ҳ����һҳ������ ��һҳ������ ���أ�ESC��"<<endl; 
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
		cout<<"                      ������ʾ��302��"<<endl;
		cout<<"        ========================================"<<endl;
		cout<<"        *��⵽�赥�в����ڸ�����Ϣ��"<<endl;
		cout<<"        *�����Ǹ赥�ļ����ܵ��𻵡�"<<endl;
		cout<<"        *�����ȷ������Ϊ��Ϊ�������¸赥�������"<<endl;
		cout<<"        *����롰��Ӹ������˵���Ӹ�����"<<endl;
		cout<<"        *����ļ��𻵣�����ϵ����Ա����"<<endl; 
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
			cout<<"                      ������ʾ��303��"<<endl;
			cout<<"     =============================================="<<endl;
			cout<<"     *�������ĸ��ֲ������赥��Ŀǰû���κθ�����Ϣ��"<<endl;
			cout<<"     *ɾ�������޷��ָ�����������Ӹ������˵���Ӹ�����"<<endl;
			cout<<"     *��������ļ������⣬����ϵ����Ա����"<<endl;
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����赥�������޸�ɾ������"<<endl; 
		cout<<endl;
		cout<<endl<<endl;
		begin=(nowpage-1)*10;
		finish=((nowpage*10-1)<(songnum-1))? (nowpage*10-1):(songnum-1);
		pList->showList_admin(begin,finish);
		cout<<"    ȫ��"<<songnum<<"�׸裬��"<<nowpage<<"ҳ����"<<pagenum<<"ҳ����һҳ������ ��һҳ������ �˵����س��� ���أ�ESC��"<<endl; 
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
			cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"            ������ϸ��Ϣ                             ��ѡ��"<<endl;
		cout<<"       ======================                   ================"<<endl;
		cout<<"       *��    �ţ�"<<left<<setw(20)<<p->songId<<"\t\t"<<"*1.�޸ĸ�����Ϣ"<<endl;
		cout<<"       *��    ����"<<left<<setw(20)<<p->songName<<endl; 
		cout<<"       *ƴ����д��"<<left<<setw(20)<<p->songAbbr<<"\t\t"<<"*2.�Ӹ赥��ɾ��"<<endl;
		cout<<"       *��    �֣�"<<left<<setw(20)<<p->singerName<<endl; 
		cout<<"       *�� �� ����"<<left<<setw(20)<<p->playedNum<<"\t\t"<<"*0.  ��    ��"<<endl; 
		cout<<"       *�������֣�"<<left<<setw(20)<<p->songStar<<"\t\t"<<"================="<<endl;
		cout<<"       *����������"<<left<<setw(20)<<p->scoreNum<<endl;
		cout<<"       ======================="<<endl;
		cout<<"     �������Ӧ������ţ�"; 
		printf("�� ��\b\b\b");
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
			cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"       *�������޸ĸ���"<<left<<setw(11)<<p->songId<<"\t\t"<<"��ѡ��"<<endl;
		cout<<"       ======================                   ============"<<endl;
		cout<<"       *��ǰ������"<<left<<setw(15)<<p->songName<<"\t\t"<<"*1.�޸ĸ���"<<endl; 
		cout<<"       *��ǰƴ����"<<left<<setw(15)<<p->songAbbr<<"\t\t"<<"*2.�޸�ƴ��"<<endl;
		cout<<"       *��ǰ���֣�"<<left<<setw(15)<<p->singerName<<"\t\t"<<"*3.�޸ĸ���"<<endl; 
		cout<<"       ======================"<<left<<setw(5)<<" "<<"\t\t"<<"*0.��    ��"<<endl; 
		cout<<"                  "<<left<<setw(15)<<" "<<"\t\t"<<"============"<<endl;
		cout<<"     �������Ӧ������ţ�"; 
		printf("�� ��\b\b\b");
		cin>>choice;
		if(choice=='0') {
			pList->saveToFile(sfile);
			fclose(sfile);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *���ڱ��汾���ļ���"<<endl;
			cout<<"                  *���Ժ�..........." <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
			return;
			
		}
		if(choice=='1'){
			cout<<endl<<"     �������޸ĺ�ĸ������ƣ�";
			cin>>name;
			singer=p->singerName;
			abbr=p->songAbbr;
			pList->correctInfo(p,name,singer,abbr);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *������Ϣ�޸ĳɹ���"<<endl;
			cout<<"                  *���ڷ�����һ���档" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
		}
		if(choice=='2'){
			cout<<endl<<"     �������޸ĺ�ĸ���ƴ����";
			cin>>abbr;
			FILE* sfile=fopen("files:\\songlist.txt","w");
			singer=p->singerName;
			name=p->songName;
			pList->correctInfo(p,name,singer,abbr);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *������Ϣ�޸ĳɹ���"<<endl;
			cout<<"                  *���ڷ�����һ���档" <<endl;
			cout<<"                  =================="<<endl;
			Sleep(1200); 
		} 
		if(choice=='3'){
			cout<<endl<<"     �������޸ĺ�ĸ������ƣ�";
			cin>>singer;
			FILE* sfile=fopen("files:\\songlist.txt","w");
			abbr=p->songAbbr;
			name=p->songName;
			pList->correctInfo(p,name,singer,abbr);
			pList->saveToFile(sfile);
			system("cls");
			cout<<endl<<endl<<endl<<endl;
			cout<<"                  =================="<<endl;
			cout<<"                  *������Ϣ�޸ĳɹ���"<<endl;
			cout<<"                  *���ڷ�����һ���档" <<endl;
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
		cout<<"     ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"                *WARNING!"<<endl;
		cout<<"      *����׼��ɾ������"<<p->songId<<":";
		cout<<p->singerName<<"-"<<p->songName<<","<<endl;
		cout<<"      *ɾ����ĸ������޷��һء������Ҫ������?"<<endl;
		cout<<"      *�ǣ�Y��        ��N��"<<endl; 
		cout<<"     �������������Ե�ѡ��";
		printf("�� ��\b\b\b");
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
			cout<<"                  *����ɾ���ɹ���"<<endl;
			cout<<"                  *���ڱ��汾���ļ�......" <<endl;
			cout<<"                  *���޷��ָ���ɾ���ĸ�����"<<endl;
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����赥�������赥��������"<<endl; 
		cout<<endl;
		if(option<'0'||option>'2'){
			cout<<"         ����������������롣"; 
		}
		cout<<endl<<endl;
		cout<<"                            �� �� �� �� �� ��"<<endl;
		cout<<"                     =============================="<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     *    1.�����û����ָߵ�����  *"<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     *    2.���ղ��������ߵ�����  *"<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     *    0. �� �� �� һ �� ��    *"<<endl;
		cout<<"                     *                            *"<<endl;
		cout<<"                     =============================="<<endl;
		cout<<"                 ������ѡ����ţ�";
		printf("�� ��\b\b\b");
		cin>>option;
		if(option=='0') return;
		if(option=='1'){
			system("cls");
			cout<<endl<<endl;
			if(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N'){
			cout<<"     ����������������롣"; 
			}
			cout<<endl<<endl;
			cout<<"      *����׼���������֡��ߵ�����"<<endl;
			cout<<"      *ȷ���������������"<<endl;
			cout<<"      *�ǣ�Y��        ��N��"<<endl; 
			cout<<"     ��ѡ��";
			printf("�� ��\b\b\b");
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
				cout<<"                  *       �赥����ɹ���"<<endl;
				cout<<"                  *     ���ڱ��汾���ļ���" <<endl;
				cout<<"                  *���������˳���鿴�赥�����"<<endl;
				cout<<"                  ============================"<<endl;
				Sleep(2400); 
				return;
			}
		}
		if(option=='2'){
			system("cls");
			cout<<endl<<endl;
			if(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N'){
			cout<<"     ����������������롣"; 
			}
			cout<<endl<<endl;
			cout<<"      *����׼���������������ߵ�����"<<endl;
			cout<<"      *ȷ���������������"<<endl;
			cout<<"      *�ǣ�Y��        ��N��"<<endl; 
			cout<<"     ��ѡ��";
			printf("�� ��\b\b\b");
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
				cout<<"                  *       �赥����ɹ���"<<endl;
				cout<<"                  *     ���ڱ��汾���ļ���" <<endl;
				cout<<"                  *���������˳���鿴�赥�����"<<endl;
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
		cout<<"      ���¡��س�����ʼ��Ӹ��������¡�ESC�����ء�"<<endl<<endl;
		choice=getch();
		if(choice==27) return;
		if(choice=='\r'){
			cout<<"           ��Ӹ���"<<endl;
			cout<<"      ===================="<<endl;
			cout<<"      *�������ƣ�";
			cin>>name;
			thesong.songName=name;
			cout<<"      *����ƴ����";
			cin>>abbr;
			thesong.songAbbr=abbr;
			cout<<"      *�������ƣ�";
			cin>>singer;
			thesong.singerName=singer;
			thesong.songId=pList->getSongnum()+1; 
			bool flag=pList->addToList(thesong);
			if(!flag){
				cout<<endl<<"      *�������ʧ�ܣ�ԭ�򣺸����Ѵ��ڡ�"<<endl;
			}
			if(flag){
				cout<<endl<<"      *�ѳɹ���Ӹ���"<<pList->getSongnum()<<":"<<singer<<"-"<<name<<endl; 
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"������Ӹ������������������"<<endl; 
		cout<<endl<<endl;
		cout<<"                        �����������������֪"<<endl;
		cout<<"     =============================================================="<<endl;
		cout<<"     *�뽫�������ո����������֡�����ƴ����˳��д��һ��txt�ļ��С�"<<endl;
		cout<<"     *��ͬ����֮���뻻�и�����ͬһ�����Ĳ�ͬ��Ϣ֮�������Ʊ��������"<<endl;
		cout<<"     *�ļ�������ɺ��뽫�ļ�����·�����������涨�����ڣ����ɵ��롣"<<endl;
		cout<<"     *�����չ涨��ʽ���и���������ļ�����·�������ܻᵼ�µ����쳣��"<<endl;
		cout<<"     *������ɺ����������赥����-�޸ĸ�����Ϣ���Ը�����Ϣ�����޸ġ�"<<endl;
		cout<<"     ==============================================================="<<endl;
		cout<<"   �������Ķ������������������֪�������س�����ȷ�ϣ�����ESC����ȡ����"<<endl;
		ch=getch();
		if(ch==27) return;
		if(ch=='\r'){
			while(true){
				system("cls");
				char Filename[100];
				int first=pList->getSongnum()+1;
				cout<<endl<<endl<<endl;
				cout<<"                       ��������"<<endl;
				cout<<"   =================================================="<<endl; 
				cout<<"   *�������ļ�����·������"; 
				cin>>Filename;
				const char* filename=Filename;
				FILE* afile=fopen(filename,"r");
				if(afile==NULL){
					cout<<endl<<"    *δ�ҵ�Ŀ���ļ���"<<endl<<"    *����ʧ�ܣ�"<<endl;
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
				cout<<endl<<"    *����ɹ��������£�"<<endl;
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"�����˺Ź������޸�����"<<endl; 
		cout<<endl<<endl;
		cout<<"             �޸����������֪"<<endl;
		cout<<"     ========================================="<<endl;
		cout<<"     *�޸�����ǰ������ȷ��ԭ���롣"<<endl;
		cout<<"     *�������б��������Сд��ĸ�����֡�"<<endl; 
		cout<<"     *�����볤�Ȳ��ó���12���ַ������ð����ո�"<<endl;
		cout<<"     *�����޸���ɺ������µ�¼����֤�˺š�"<<endl;
		cout<<"     ========================================="<<endl;
		cout<<"   �������Ķ��޸����������֪�������س�����ȷ�ϣ�����ESC����ȡ����" <<endl<<endl;
		ch=getch();
		if(ch==27) return false;
		if(ch=='\r'){
			system("cls");
			cout<<endl<<endl;
			cout<<"        *�޸�����"<<endl;
			cout<<"        ==================="<<endl;
			cout<<"        ԭ����:";
			cin>>opass;
			if(!pData->change_oldConfirm(opass)){
				system("cls");
				cout<<endl<<endl;
				cout<<"               ������ʾ"<<endl; 
				cout<<"          ================="<<endl;
				cout<<"          *ԭ������֤����"<<endl;
				cout<<"          *�����޸�ʧ�ܡ�"<<endl; 
				cout<<"          ================="<<endl;
				Sleep(1200);
				return false; 
			}
			cout<<"        ������:";
			cin>>npass;
			if(pData->change_newLegal(npass)==1) {
				system("cls");
				cout<<endl<<endl;
				cout<<"                   ������ʾ"<<endl; 
				cout<<"          =========================="<<endl;
				cout<<"          *���볤�Ȳ��ó���12���ַ���"<<endl;
				cout<<"          *�����޸�ʧ�ܡ�"<<endl; 
				cout<<"          =========================="<<endl;
				Sleep(2400);
				return false; 
			} 
			if(pData->change_newLegal(npass)==2){
				system("cls");
				cout<<endl<<endl;
				cout<<"                        ������ʾ"<<endl; 
				cout<<"          ===================================="<<endl;
				cout<<"          *�������ͬʱ������Сд��ĸ�����֡�"<<endl;
				cout<<"          *�����޸�ʧ�ܡ�"<<endl; 
				cout<<"          ===================================="<<endl;
				Sleep(2400);
				return false; 
			}
			cout<<"        ȷ��������:";
			cin>>npass2;
			if(!pData->change_newConsist(npass,npass2)){
				system("cls");
				cout<<endl<<endl;
				cout<<"                  ������ʾ"<<endl; 
				cout<<"          ======================="<<endl;
				cout<<"          *�����������벻һ�¡�"<<endl;
				cout<<"          *�����޸�ʧ�ܡ�"<<endl; 
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
				cout<<"                  �޸ĳɹ���"<<endl; 
				cout<<"          ===================="<<endl;
				cout<<"          *�����޸ĳɹ���"<<endl;
				cout<<"          *�����ǳ����µ�¼��"<<endl; 
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
		cout<<"    ��ǰ�汾��V1.1"<<endl;
		cout<<"    ��ǰ���棺��̨����"<<pData->getUsername()<<"������Ӹ�������������Ϣ"<<endl; 
		cout<<endl<<endl;;
		cout<<"          ������Ϣ������"<<now<<"������"<<sugnum<<"����"<<endl;
		cout<<"    ========================================="<<endl;
		cout<<"    *��������"<<p->songName<<endl;
		cout<<"    *��������"<<p->singerName<<endl;
		cout<<"    ========================================="<<endl;
		cout<<"    ���ϡ������¡���������ҳ�������س�����������Ϣ������ESC�����ء�"<<endl;
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
			cout<<"    *���������ƴ����д������0ɾ���÷�����Ϣ����";
			cin>>abbr;
			if(abbr=="0"){
				FILE* sfile=fopen("files\\songlist.txt","w");
				cout<<"    *��������ɹ���"<<endl;
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
				cout<<"    *��ӳɹ���"<<endl;
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
				cout<<"    *ʧ�ܣ�ԭ�򣺸����Ѵ��ڡ�����Ϊ��ɾ���˷�����Ϣ��"<<endl; 
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

