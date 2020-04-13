#ifndef ADMIN_H
#define ADMIN_H

#include "song.h"
#include "account.h"
using namespace std;

//���� 
void admin_run();
//��ʾ��¼���� 
void enter_login(SongList *pList,Account *pData,SongList *sList);
//��ʾ������ 
void enter_adminMenu(SongList *pList,Account *pData,SongList *sList);
//��ʾȫ���������� 
void enter_adminShowAll(SongList *pList,Account *pData);
//��ʾ�޸ĸ�����Ϣ����
void enter_adminEdit(SongList *pList,Account *pData) ;
//��ʾ������ϸ��Ϣ
void enter_adminDetail(SongList *pList,Account *pData,int id); 
//��ʾ�޸ĸ�������
void enter_editSong(SongList *pList,Account *pData,SongInfo* p); 
//��ʾɾ���������� 
bool enter_deleteConfirm(SongList *pList,Account *pData,int id);
//��ʾ�������� 
void enter_ranking(SongList *pList,Account* pData);
//��ʾ��Ӹ������� 
void enter_add(SongList *pList,Account* pData);
//��ʾ������ӽ��� 
void enter_volumnAdd(SongList *pList,Account *pData);
//��ʾ�޸�������� 
bool enter_changePass(SongList *pList,Account *pData);
//��ʾ����������
void enter_suggestAdd(SongList *pList,Account *pData,SongList* sList); 

#endif //ADMIN_H

/*
	1.�赥��������ɣ� 
	2.������ӣ�����ɣ� 
	3.�˺Ź�������ɣ�
	
	1-1.�鿴ȫ������������ɣ� 
	1-2.�޸�ɾ������������ɣ� 
	1-3.�赥�������� ������ɣ� 
	
	2-1.��ӵ�������������ɣ� 
	2-2.�����������������ɣ� 
	
	3-1.�޸����루����ɣ�
	3-2.�˳�ϵͳ ������ɣ�
*/ 
