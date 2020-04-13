#ifndef USER_H
#define USER_H

#include "song.h"
using namespace std;

//����
void user_run(); 
//��ʾ������ 
void enter_userMenu(SongList *pList);
//��ʾȫ���������� 
void enter_userShowAll(SongList *pList);
//������ϸ��Ϣ����
void enter_userDetail(SongList *pList,int id); 
//��ʾ�ѵ�������� 
void enter_showPicked(SongList *pList);
//��ʾ�и����
void enter_switch(SongList *pList,int id); 
//��ʾ���ǵ����� 
void enter_pickBySinger(SongList *pList);
//��ʾ������������ 
void enter_pickByName(SongList *pList);
//��ʾƴ�������� 
void enter_pickByAbbr(SongList *pList);
//��ʾ��������
void enter_feedback(SongList *pList); 

bool showList(vector<SongInfo> List);
bool hasSong(vector<SongInfo> List,int id);
#endif //USER_H

/*
	1.���и�������ɣ� 
	2.��� 
	3.�ѵ��������ɣ� 
	4.�����и�
	0.�˳� ����ɣ� 
*/

