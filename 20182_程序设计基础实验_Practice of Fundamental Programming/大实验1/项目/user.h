#ifndef USER_H
#define USER_H

#include "song.h"
using namespace std;

//驱动
void user_run(); 
//显示主界面 
void enter_userMenu(SongList *pList);
//显示全部歌曲界面 
void enter_userShowAll(SongList *pList);
//歌曲详细信息界面
void enter_userDetail(SongList *pList,int id); 
//显示已点歌曲界面 
void enter_showPicked(SongList *pList);
//显示切歌界面
void enter_switch(SongList *pList,int id); 
//显示歌星点歌界面 
void enter_pickBySinger(SongList *pList);
//显示歌曲名点歌界面 
void enter_pickByName(SongList *pList);
//显示拼音点歌界面 
void enter_pickByAbbr(SongList *pList);
//显示反馈界面
void enter_feedback(SongList *pList); 

bool showList(vector<SongInfo> List);
bool hasSong(vector<SongInfo> List,int id);
#endif //USER_H

/*
	1.所有歌曲（完成） 
	2.点歌 
	3.已点歌曲（完成） 
	4.快速切歌
	0.退出 （完成） 
*/

