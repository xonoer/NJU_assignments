#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include "song.h"
using namespace std;

SongList::SongList(){	//Ĭ�Ϲ��캯�����������б� 
	List.clear();
	PickedList.clear();
	songnum=0;
	pickednum=0;
}

SongList::SongList(FILE* pfile){ //������ͨ�������캯��������ϵͳ�赥  
	List.clear();
	PickedList.clear();
	char ch[99];
	songnum=0;
	pickednum=0;
	while (fgets(ch,99,pfile)){
		SongInfo p;
		string thesong(ch);
		if(thesong[0]=='\n') continue;
		
		string SName;
		string SSinger;
		string SAbbr;
		string SStar;
		string SSnum;
		string SPnum;
		int num=0;
		for(int i = 0; i < thesong.length(); i++){
			if(thesong[i]!='\t'&&thesong[i]!='\n'){
				char target=thesong[i];
				
				if(num==0) SName+=target;
				if(num==1) SSinger+=target;
				if(num==2) SAbbr+=target;
				if(num==3) SStar+=target;
				if(num==4) SSnum+=target;
				if(num==5) SPnum+=target;
			}
			else{
				while(thesong[i+1]=='\t') i++;
				num++;
			}
		}
		p.songName=SName;
		p.singerName=SSinger;
		p.songAbbr=SAbbr;
		p.songId=songnum+1;
		p.songStar=atof(SStar.c_str());
		p.scoreNum=atoi(SSnum.c_str());
		p.playedNum=atoi(SPnum.c_str());
		addToList(p);
	}
	 
}

void SongList::createList_suggest(FILE *pfile){
	List.clear();
	PickedList.clear();
	char ch[99];
	songnum=0;
	pickednum=0;
	while (fgets(ch,99,pfile)){
		SongInfo p;
		string thesong(ch);
		if(thesong[0]=='\n') continue;
		
		string SName;
		string SSinger;
		int num=0;
		for(int i = 0; i < thesong.length(); i++){
			if(thesong[i]!='\t'&&thesong[i]!='\n'){
				char target=thesong[i];
				
				if(num==0) SName+=target;
				if(num==1) SSinger+=target;
			}
			else{
				while(thesong[i+1]=='\t') i++;
				num++;
			}
		}
		p.songName=SName;
		p.singerName=SSinger;
		p.songId=songnum+1;
		addToList(p);
	}
}

int SongList::getSongnum(){//������ͨ������ø��������ѵ����� 
	return songnum;
} 

int SongList::getPickednum() {
	return pickednum;
}

 
void SongList::showList_user(int begin,int finish){	//������ͨ�����û�����ʾ��begin����finish�����и��� 
	//cout<<"       ���\t������\t\t����\t\t����״̬"<<endl; 
	cout<<"\t"<<setw(5)<<"���"<<setw(20)<<"������"<<setw(20)<<"����"<<"\t"<<"����״̬"<<endl; 
	cout<<"     ============================================================"<<endl;
	for(int i=begin;i<=finish;i++){
		SongInfo p=List[i];
		cout<<"\t"<<setw(5)<<p.songId<<setw(20)<<p.songName<<setw(20)<<p.singerName<<"\t";
		if(p.songStatus==1) cout<<"���ڲ���";
		if(p.songStatus>=2)  cout<<"  �ѵ�"; 
		cout<<endl;
	}
}

void SongList::showList_admin(int begin,int finish){	//������ͨ�����������ʾ��begin����finish�����и��� 
	//cout<<"       ���\t������\t\t����\t\tƴ����д\t����\t������"<<endl; 
	cout<<"\t"<<setw(5)<<"���"<<setw(20)<<"������"<<setw(20)<<"����"<<setw(15)<<"ƴ����д"<<"\t����\t������"<<endl; 
	cout<<"     ===================================================================================="<<endl;
	for(int i=begin;i<=finish;i++){
		SongInfo p=List[i];
		cout<<"\t"<<setw(5)<<p.songId<<setw(20)<<p.songName<<setw(20)<<p.singerName<<setw(15)
			<<p.songAbbr<<"\t"<<setprecision(2)<<p.songStar<<"\t "<<p.playedNum; 
		cout<<endl;
	} 
}

void SongList::showList_picked(int begin,int finish){
	//cout<<"       ���\t������\t\t����"<<endl; 
	cout<<"\t"<<setw(5)<<"���"<<setw(20)<<"������"<<setw(20)<<"����"<<endl; 
	cout<<"     =================================================="<<endl;
	 for(int i=begin;i<=finish;i++){
		SongInfo p=PickedList[i];
		cout<<"\t"<<setw(5)<<p.songStatus<<setw(20)<<p.songName<<setw(20)<<p.singerName; 
		if(p.songStatus==1) cout<<"------���ڲ���"; 
		cout<<endl;
	} 
}

bool SongList::addToList(SongInfo thesong){//������ͨ�����ж��Ƿ���赥�غϣ��粻�غ������ 
	for(vector<SongInfo>::iterator it=List.begin();it<List.end();it++){
		if((*it).songName==thesong.songName&&(*it).singerName==thesong.singerName) return false;
	}
	List.push_back(thesong);
	songnum++;
	return true;
	
} 

void SongList::volumnAddToList(FILE* pfile){// ������ͨ��������������� 
	char ch[50];
	int success=0;
	int fail=0;
	while (fgets(ch,50,pfile)){
		SongInfo p;
		string thesong(ch);
		if(thesong[0]=='\n') continue;
		
		string SName;
		string SSinger;
		string SAbbr;
		int num=0;
		for(int i = 0; i < thesong.length(); i++){
			if(thesong[i]!='\t'&&thesong[i]!='\n'){
				char target=thesong[i];
				
				if(num==0) SName+=target;
				if(num==1) SSinger+=target;
				if(num==2) SAbbr+=target;
			}
			else{
				while(thesong[i+1]=='\t') i++;
				num++;
			}
		}
		p.songName=SName;
		p.singerName=SSinger;
		p.songAbbr=SAbbr;
		p.songId=songnum+1;
		if(addToList(p)){
			success++;
		}
		else{
			fail++;
		}
		
	}
	cout<<"    *������ɣ�"<<endl;
	cout<<"    *�����Ե���"<<success+fail<<"�׸���������ɹ�"<<success<<"�ף�����ʧ��"<<fail<<"�ס�\n";
	if(fail) cout<<"    *ԭ�򣺸����Ѵ��ڡ�"<<endl; 
	 
} 

bool SongList::deleteSongFromList(int id){ //������ͨ����ɾ������ 
	for(int i=0;i<List.size();i++){
		if(List[i].songId==id){
			List.erase(List.begin()+i,List.begin()+i+1);
			for(int j=i;j<List.size();j++){
				List[j].songId=j+1;
			}
			songnum--;
			return true;
		}
		
	}
	return false;
} 

SongInfo* SongList::locateSong(int id){//������ͨ����������λ 
	for(int i=0;i<List.size();i++){
		if(List[i].songId==id){
			SongInfo* p=&List[i];
			return p;
		}	
	}
}

SongInfo* SongList::locatePickedSong(int status){
	for(int i=0;i<PickedList.size();i++){
		if(PickedList[i].songStatus==status){
			SongInfo* p=&PickedList[i];
			return p;
		}	
	}
} 

void SongList::correctInfo(SongInfo *p,string name,string singer,string abbr){//������ͨ�����޸ĸ�����Ϣ 
	p->songName=name;
	p->singerName=singer;
	p->songAbbr=abbr;
}

void SongList::pickSong(SongInfo *p){	//������ͨ������� 
	if(pickednum==0){
	  	p->songStatus=1;
	  	p->playedNum++;
	}
	else p->songStatus=pickednum+1;
	SongInfo thesong=(*p);
	PickedList.push_back(thesong);
	pickednum++;
} 

void SongList::arrangeByStar(){	//������ͨ���������������� 
	for(int i=0;i<songnum-1;i++){
		for (int j=i+1;j<songnum;j++){
			if(List[i].songStar<List[j].songStar){
				double temp=List[i].songId;
				List[i].songId=List[j].songId;
				List[j].songId=temp;
				SongInfo tpstruct=List[i];
				List[i]=List[j];
				List[j]=tpstruct;
			}
		}
	}
} 

void SongList::arrangeByPnum(){	//������ͨ�������ղ��������� 
	for(int i=0;i<songnum-1;i++){
		for (int j=i+1;j<songnum;j++){
			if(List[i].playedNum<List[j].playedNum){
				double temp=List[i].songId;
				List[i].songId=List[j].songId;
				List[j].songId=temp;
				SongInfo tpstruct=List[i];
				List[i]=List[j];
				List[j]=tpstruct;
			}
		}
	}
} 

void SongList::saveToFile(FILE* pfile){//������ͨ���������ļ� 
	for(int i=0;i<songnum;i++){
		string target(List[i].songName);
		target+='\t';
		target+=List[i].singerName;
		target+='\t';
		target+=List[i].songAbbr;
		target+='\t';
		target+=to_string(List[i].songStar);
		target+='\t';
		target+=to_string(List[i].scoreNum);
		target+='\t';
		target+=to_string(List[i].playedNum);
		target+='\n';
		fputs(target.c_str(),pfile);
	}
} 

void SongList::saveToFile_suggest(FILE* pfile){
	for(int i=0;i<songnum;i++){
		string target(List[i].songName);
		target+='\t';
		target+=List[i].singerName;
		target+='\n';
		fputs(target.c_str(),pfile);
	}
}

vector <SongInfo> SongList::searchByName(string name){//������ͨ����Ϊ�˷����û������ֶ�����ģ�������������Ӵ������ҡ� 
	vector <SongInfo> target;
	target.clear();
	for(int i=0;i<songnum;i++){
		string::size_type idx;
		idx=List[i].songName.find(name);
		if(idx!=string::npos){
			SongInfo thesong=List[i];
			target.push_back(thesong);
		}
	}
	return target; 
}

vector <SongInfo> SongList::searchBySinger(string singer){
	vector <SongInfo> target;
	target.clear();
	for(int i=0;i<songnum;i++){
		string::size_type idx;
		idx=List[i].singerName.find(singer);
		if(idx!=string::npos){
			SongInfo thesong=List[i];
			target.push_back(thesong);
		}
	}
	return target; 
}

vector <SongInfo> SongList::searchByAbbr(string abbr){
	vector <SongInfo> target;
	target.clear();
	for(int i=0;i<songnum;i++){
		string::size_type idx;
		idx=List[i].songAbbr.find(abbr);
		if(idx!=string::npos){
			SongInfo thesong=List[i];
			target.push_back(thesong);
		}
	}
	return target; 
}

void SongList::scoreSong(SongInfo *p,int score){	//������ͨ������������ 
	double final;
	final=((p->songStar)*(p->scoreNum)+(double)score)/(double)(p->scoreNum+1);
	p->songStar=final;
	p->scoreNum++;
}

bool SongList::switchSong(){	//������ͨ����ע���������������ʹ��ʱ�����½��ޡ� 
	if (pickednum==0) return false;
	else{
		SongInfo * switched=locateSong(PickedList[0].songId);
		switched->songStatus=0;
		PickedList.erase(PickedList.begin(),PickedList.begin()+1);
		pickednum--;
		for(int i=0;i<pickednum;i++) {
			SongInfo* target=locateSong(PickedList[i].songId);
			target->songStatus=PickedList[i].songStatus=i+1;
			if(target->songStatus==1) target->playedNum=PickedList[i].playedNum=target->playedNum+1;
		}
		return true;
	}
} 

bool SongList::topSong(int id){//������ͨ�����ö����� 
	int index=-1; 
	for(int i=1;i<pickednum;i++){
		if(PickedList[i].songId==id) {
			index=i;
			break;
		}
	}
	if(index==-1) return false;
	SongInfo* p=locateSong(id);
	p->songStatus=2;
	SongInfo top=(*p);
	for(int i=index;i>1;i--){
		PickedList[i-1].songStatus++;
		PickedList[i]=PickedList[i-1];
		SongInfo* qq=locateSong(PickedList[i].songId);
		qq->songStatus++;
	}
	PickedList[1]=top;
	return true;
} 

int SongList::getId(int status){
	for(int i=0;i<songnum;i++){
		if(List[i].songStatus==status) return List[i].songId;
	}
	return -1;
} 

void SongList::removeSong(int id){
	for(int i=1;i<pickednum;i++){
		if(PickedList[i].songId==id){
			SongInfo *p=locateSong(id);
			PickedList.erase(PickedList.begin()+i,PickedList.begin()+i+1);
			p->songStatus=0;
			pickednum--;
			break;
		}
	}
	for(int i=0;i<pickednum;i++){
		SongInfo* target=locateSong(PickedList[i].songId);
		target->songStatus=PickedList[i].songStatus=i+1;
	}
}

SongList::~SongList(){	//�������� 
	List.clear();
	PickedList.clear();
}
