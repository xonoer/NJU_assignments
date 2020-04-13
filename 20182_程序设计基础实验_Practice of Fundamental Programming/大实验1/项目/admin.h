#ifndef ADMIN_H
#define ADMIN_H

#include "song.h"
#include "account.h"
using namespace std;

//驱动 
void admin_run();
//显示登录窗口 
void enter_login(SongList *pList,Account *pData,SongList *sList);
//显示主界面 
void enter_adminMenu(SongList *pList,Account *pData,SongList *sList);
//显示全部歌曲界面 
void enter_adminShowAll(SongList *pList,Account *pData);
//显示修改歌曲信息界面
void enter_adminEdit(SongList *pList,Account *pData) ;
//显示歌曲详细信息
void enter_adminDetail(SongList *pList,Account *pData,int id); 
//显示修改歌曲界面
void enter_editSong(SongList *pList,Account *pData,SongInfo* p); 
//显示删除歌曲界面 
bool enter_deleteConfirm(SongList *pList,Account *pData,int id);
//显示排名界面 
void enter_ranking(SongList *pList,Account* pData);
//显示添加歌曲界面 
void enter_add(SongList *pList,Account* pData);
//显示批量添加界面 
void enter_volumnAdd(SongList *pList,Account *pData);
//显示修改密码界面 
bool enter_changePass(SongList *pList,Account *pData);
//显示处理反馈界面
void enter_suggestAdd(SongList *pList,Account *pData,SongList* sList); 

#endif //ADMIN_H

/*
	1.歌单管理（已完成） 
	2.歌曲添加（已完成） 
	3.账号管理（已完成）
	
	1-1.查看全部歌曲（已完成） 
	1-2.修改删除歌曲（已完成） 
	1-3.歌单排序设置 （已完成） 
	
	2-1.添加单个歌曲（已完成） 
	2-2.批量导入歌曲（已完成） 
	
	3-1.修改密码（已完成）
	3-2.退出系统 （已完成）
*/ 
