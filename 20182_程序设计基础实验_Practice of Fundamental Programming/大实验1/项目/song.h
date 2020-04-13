#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
using namespace std;
struct SongInfo{
	int songId; //����ID��Ψһ�ģ� 
	string songName; 	//�������� 
	string singerName;	//������ 
	string songAbbr;	//������д 
	double songStar;	//�������� 
	int scoreNum;
	int playedNum;		//���������� 
	int songStatus;	//����״̬ ��0���ȴ���1�����ڲ��š����ڵ���2���ѵ㣩 
	SongInfo(): songId(-1),songAbbr("NULL"),songStar(0),scoreNum(0),playedNum(0),songStatus(0){}
};
class SongList{  //�赥������˶Ը赥�����в��� 
	private:
		vector<SongInfo> List;
		vector<SongInfo> PickedList;
		int songnum;
		int pickednum;
	public:
		SongList();		//����һ���ո赥 
		SongList(FILE* pfile);	//��ȡ�ļ��еĸ赥 
		void createList_suggest(FILE* pfile); 
		int getSongnum();//��ȡ���и�����  
		int getPickednum(); 
		void showList_user(int begin,int finish); //չʾ�涨��Χ�ڵĸ��� 
		void showList_admin(int begin,int finish);//չʾ�涨��Χ�ڵĸ��� 
		void showList_picked(int begin,int finish);//չʾ�ѵ���Ŀ 
		bool addToList(SongInfo thesong);	//�ж��Ƿ�����赥����Ӹ���ͬʱ���   
		void volumnAddToList(FILE* pfile);	//��赥��������Ӹ��� 
		bool deleteSongFromList(int id);	//�Ӹ赥��ɾ������ 
		SongInfo* locateSong(int id);	//��λ���� 
		SongInfo* locatePickedSong(int status);//��λ�ѵ���� ����picked���棩 
		void correctInfo(SongInfo* p,string name,string singer,string abbr);//�޸ĸ�����Ϣ 
		void pickSong(SongInfo *p);	 //��裨Ӱ�첥������  
		void arrangeByStar();				//����������  
		void arrangeByPnum();				//�Բ���������  
		void saveToFile(FILE* pfile);		//����赥 
		void saveToFile_suggest(FILE* pfile);
		vector<SongInfo> searchBySinger(string singer);	//�������������� 
		vector<SongInfo> searchByName(string name);		//���������������� 
		vector<SongInfo> searchByAbbr(string abbr);		//ģ���������� 
		void scoreSong(SongInfo *p,int score); 	//���������� 
		bool switchSong();			//�и� 
		bool topSong(int id);		//�ö� 
		void removeSong(int id);    //�Ƴ� 
		int getId(int status);		//�����������ѵ�����е�id�� 
		~SongList(); 
};
#endif  //SONG_H 
