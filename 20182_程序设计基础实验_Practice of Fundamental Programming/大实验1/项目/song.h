#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
using namespace std;
struct SongInfo{
	int songId; //歌曲ID（唯一的） 
	string songName; 	//歌曲名称 
	string singerName;	//歌手名 
	string songAbbr;	//歌曲缩写 
	double songStar;	//歌曲评分 
	int scoreNum;
	int playedNum;		//歌曲播放数 
	int songStatus;	//歌曲状态 （0：等待、1：正在播放、大于等于2：已点） 
	SongInfo(): songId(-1),songAbbr("NULL"),songStar(0),scoreNum(0),playedNum(0),songStatus(0){}
};
class SongList{  //歌单类包含了对歌单的所有操作 
	private:
		vector<SongInfo> List;
		vector<SongInfo> PickedList;
		int songnum;
		int pickednum;
	public:
		SongList();		//建立一个空歌单 
		SongList(FILE* pfile);	//读取文件中的歌单 
		void createList_suggest(FILE* pfile); 
		int getSongnum();//获取所有歌曲数  
		int getPickednum(); 
		void showList_user(int begin,int finish); //展示规定范围内的歌曲 
		void showList_admin(int begin,int finish);//展示规定范围内的歌曲 
		void showList_picked(int begin,int finish);//展示已点曲目 
		bool addToList(SongInfo thesong);	//判断是否能向歌单内添加歌曲同时添加   
		void volumnAddToList(FILE* pfile);	//向歌单内批量添加歌曲 
		bool deleteSongFromList(int id);	//从歌单中删除歌曲 
		SongInfo* locateSong(int id);	//定位歌曲 
		SongInfo* locatePickedSong(int status);//定位已点歌曲 （在picked里面） 
		void correctInfo(SongInfo* p,string name,string singer,string abbr);//修改歌曲信息 
		void pickSong(SongInfo *p);	 //点歌（影响播放量）  
		void arrangeByStar();				//以评分排序  
		void arrangeByPnum();				//以播放量排序  
		void saveToFile(FILE* pfile);		//保存歌单 
		void saveToFile_suggest(FILE* pfile);
		vector<SongInfo> searchBySinger(string singer);	//按歌手搜索歌曲 
		vector<SongInfo> searchByName(string name);		//按歌曲名搜索歌曲 
		vector<SongInfo> searchByAbbr(string abbr);		//模糊搜索歌曲 
		void scoreSong(SongInfo *p,int score); 	//给歌曲评分 
		bool switchSong();			//切歌 
		bool topSong(int id);		//置顶 
		void removeSong(int id);    //移除 
		int getId(int status);		//（用于搜索已点歌曲中的id） 
		~SongList(); 
};
#endif  //SONG_H 
