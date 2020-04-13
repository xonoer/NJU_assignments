#include "Einstein.h"
#include <ctime>
#include <cstdio>
#include <cmath> 
#define FINAL 3
using namespace std;
//variable
int move_chess;
int move_direct;
int board[5][5];
int flex[13];
int preboard[5][5];
int finalboard[5][5];
int predis=0;
int nowdis=0;
bool start=false; 
//constant
int distance[5][5]={0,1,2,3,4,1,1,2,3,4,2,2,2,3,4,3,3,3,3,4,4,4,4,4,4};
double value[5][5]={100,10,5,2.5,1.25,10,8,4,2,1,5,4,4,2,1,2.5,2,2,2,1,1.25,1,1,1,0.1};
//data type
struct Location{
	int line;
	int row;
	Location():line(-1),row(-1){}
};
struct EXP{ //Execution Points，代表攻击力 
	double red;
	double blue;
	EXP():red(0),blue(0){}
};      
struct DIS{
	int red;
	int blue;
	DIS():red(0),blue(0){}
};
//function
	//assist:
static string  getCurrentTimeStr();

void trans(int dice, int* chessboard,int board[][5]);
bool valid_input(int board[][5]);
bool is_red(int dice);//确定本方阵营 
Location chess_location(int n,int board[][5]);//获取指定棋子位置 
bool chess_inboard(int n,int board[][5]);//判断棋子是否还在棋盘上 
int get_high(int dice,int board[][5]);//根据点数获得可以移动的较高点数的棋子 
int get_low(int dice,int board[][5]);//根据点数获得可以移动的较低点数的棋子 
bool canl(int n,int board[][5]);//判断棋子是否能左移 
bool canu(int n,int board[][5]);//判断棋子是否能上移 
bool canlu(int n,int board[][5]);//判断棋子是否能左上移 
int dis(int att, int def, int dice,int board[][5]);//求两棋子之间的攻击距离 
int chessnum(int dice,int board[][5]);
int enemynum(Location loc,int dice,int board[][5]);
void copymatrix(int a[][5],int b[][5]);
DIS getdis(int dice,int board[][5]);
int getalldis(DIS dis);
string output_board(int board[][5]);
	//evaluation
void count_flex(int board[][5]);//求所有棋子的灵活度 
double kill_pro(int n, int dice,int board[][5]);//求指定棋子的被歼灭可能度 
double kill_all(int dice,int board[][5]);//求敌方被全歼可能度
EXP count_exp(int dice,int board[][5]);//求双方攻击值 
	//judge
void goATT(int dice,int high,int low,int num);
void evaATT(int dice,int high,int low,int num);
 

/*在程序中，我们始终假定本方为蓝方。 
  如果本方为红方，通过骰子点数可知，此时trans中将棋盘旋转即可 
  由此，程序中，我们只考虑蓝方走棋的情况就可以了。 
  可以通过is_red函数确定右下方阵营 
*/ 
void test(int dice);
//===============================================================
//*************************************************************** 
Einstein::Einstein()
{
	logger.clear();
	this->clientsocket.connectServer();
	clientsocket.sendMsg(ID);
}

Einstein::~Einstein()
{
	this->clientsocket.close();
}

Einstein::parse(std::string s){
	int len=s.length();
	int num=0;
	for(int i=0;i<len;i++){
		if(s[i]=='0'||(s[i]>='2'&&s[i]<='9')){
			string d;
			d.clear();
			d+=s[i];
			if(num<=24) chessboard[num]=atoi(d.c_str());
			else dice=atoi(d.c_str());
			num++;
		}
		if(s[i]=='1'){
			string d;
			d.clear();
			d+=s[i];
			if(s[i+1]>='0'&&s[i+1]<='2'){
				d+=s[i+1];
				i++;
			}
			if(num<=24) chessboard[num]=atoi(d.c_str());
			else dice=atoi(d.c_str());
			num++;
		}
	}
	trans(dice, chessboard, board);
	return 0;
}
//delete
/*
int Einstein::handle_sb(){//0 left 1 up 2 leftup 3 right 4 down 5 rightdown  move_direct
	//test handle
	
	move_direct=-1;
	clientsocket.recvMsg();
	parse(this->clientsocket.getRecvMsg());
	if(!valid_input(board)) return 0;
	test(dice);
	int high=get_high(dice,board);
	int low=get_low(dice,board);
	
	if(high!=-1) move_chess=high;
	else move_chess=low;
	if(canlu(move_chess,board)) move_direct=2;
	else if(canl(move_chess,board)) move_direct=0;
	else if(canu(move_chess,board)) move_direct=1;
	if(is_red(dice)) move_direct+=3;
	if(move_direct==-1) return -1;
	string s;
	s.clear();
	s+=to_string(move_chess);
	s+='|';
	switch(move_direct){
		case 0:s+="left";break;
		case 1:s+="up";break;
		case 2:s+="leftup";break;
		case 3:s+="right";break;
		case 4:s+="down";break;
		case 5:s+="rightdown";break;
	}

	logging(s);
	return 1;
}
*/
//
int Einstein::handle(){
	move_direct=-1;
	move_chess=-1;
	int aa=clientsocket.recvMsg();
	if(aa==1) {
		cout<<"Game finish!\n"<<endl;
		logger.push_back("Game finish!\n");
		return 0;
	}
	if((nowdis==24||nowdis==23)&&!start){
		cout<<"Round finish\n======================================\nRound Start!\n";
		logger.push_back("Round finish\n======================================\nRound Start!\n");
	}
	if(!start){
		cout<<"Game start!\n"<<endl;
		start=true;
	}
	
	parse(this->clientsocket.getRecvMsg());
	
	string time=getCurrentTimeStr();
	time+='\n';
	time+=output_board(board);
	
	EXP exp=count_exp(dice,board);
	nowdis=getalldis(getdis(dice,board));
	time+="**RED ";
	time+=to_string((int)exp.red);
	time+=" : ";
	time+=to_string((int)exp.blue);
	time+=" BLUE**\n";
	logger.push_back(time);
	cout<<time;
	count_flex(board);
	int high=get_high(dice,board);
	int low=get_low(dice,board);
	int num=chessnum(dice,board);
	double k=kill_all(dice,board);
	if(k==0) goATT(dice,low,high,num);
	else evaATT(dice,low,high,num);
	if(move_direct==-1) return -1;
	string s;
	s.clear();
	s+=to_string(move_chess);
	s+='|';
	switch(move_direct){
		case 0:s+="left";break;
		case 1:s+="up";break;
		case 2:s+="leftup";break;
		case 3:s+="right";break;
		case 4:s+="down";break;
		case 5:s+="rightdown";break;
	}
	logging(s);
	return 1;
}
void goATT(int dice,int low,int high,int num){
	bool red=is_red(dice);
	EXP ori=count_exp(dice,board);
//	cout<<"红方攻击值："<<ori.red<<endl;
//	cout<<"蓝方攻击值："<<ori.blue<<endl;
	int max=-1;
	int type=0;
	bool initial=false;
	if(low!=-1){
		if(canlu(low,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(low,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row-1]=low;
			preboard[loc.line][loc.row]=0;
			
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can) 
//			cout<<"推演："<<low<<"斜向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<low<<"斜向：被围剿"<<endl; 
			if (!initial||((red?after.red:after.blue)>=max&&can)){
				max=(red?after.red:after.blue);
				move_chess=low;
				move_direct=(red?5:2);
				type=1;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canl(low,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(low,board);
			Location aloc;
			aloc.line=loc.line;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line][loc.row-1]=low;
			preboard[loc.line][loc.row]=0;
			
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<low<<"横向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<low<<"横向：被围剿"<<endl; 
			if (!initial||((red?after.red:after.blue)>=max&&can)){
				max=(red?after.red:after.blue);
				move_chess=low;
				move_direct=(red?3:0);
				type=2;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canu(low,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(low,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row]=low;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<low<<"竖向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<low<<"竖向：被围剿"<<endl; 
			if (!initial||((red?after.red:after.blue)>=max&&can)){
				max=(red?after.red:after.blue);
				move_chess=low;
				move_direct=(red?4:1);
				type=3;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
	}
	if(high!=-1&&high!=low){
		if(canlu(high,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(high,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row-1]=high;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<high<<"斜向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<high<<"斜向：被围剿"<<endl; 
			if (!initial||((red?after.red:after.blue)>=max&&can)){
				max=(red?after.red:after.blue);
				move_chess=high;
				move_direct=(red?5:2);
				type=4;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canl(high,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(high,board);
			Location aloc;
			aloc.line=loc.line;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line][loc.row-1]=high;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<high<<"横向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<high<<"横向：被围剿"<<endl; 
			if (!initial||((red?after.red:after.blue)>=max&&can)){
				max=(red?after.red:after.blue);
				move_chess=high;
				move_direct=(red?3:0);
				type=5;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canu(high,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(high,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row]=high;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<high<<"竖向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<high<<"竖向：被围剿"<<endl; 
			if (!initial||((red?after.red:after.blue)>=max&&can)){
				max=(red?after.red:after.blue);
				move_chess=high;
				move_direct=(red?4:1);
				type=6;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
	}
//	cout<<"(进攻方案)最终决定：";
//	switch(type){
//		case 1:cout<<low<<"斜向"<<endl;break;
//		case 2:cout<<low<<"横向"<<endl;break;
//		case 3:cout<<low<<"竖向"<<endl;break;
//		case 4:cout<<high<<"斜向"<<endl;break;
//		case 5:cout<<high<<"横向"<<endl;break;
//		case 6:cout<<high<<"竖向"<<endl;break;
//		default:cout<<"错误"<<endl;
//	} 
}
void evaATT(int dice,int low,int high,int num){
	bool red=is_red(dice);
	EXP ori=count_exp(dice,board);
//	cout<<"红方攻击值："<<ori.red<<endl;
//	cout<<"蓝方攻击值："<<ori.blue<<endl;
	bool initial=false;
	int max=-9999999;
	int type=0;
	copymatrix(board,preboard);
	if(low!=-1){
		if(canlu(low,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(low,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row-1]=low;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<low<<"斜向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<low<<"斜向：被围剿"<<endl; 
			if(after.blue==0||after.red==0){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=low;
				move_direct=(red?5:2);
				type=1;
				initial=true;
//				cout<<"已全歼。"<<endl;
				copymatrix(preboard,finalboard);
				return;
			}
			if (!initial||((red?after.red-after.blue:after.blue-after.red)>=max&&can)){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=low;
				move_direct=(red?5:2);
				type=1;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canl(low,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(low,board);
			Location aloc;
			aloc.line=loc.line;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line][loc.row-1]=low;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<low<<"横向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<low<<"横向：被围剿"<<endl; 
			if(after.blue==0||after.red==0){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=low;
				move_direct=(red?3:0);
				type=2;
				initial=true;
//				cout<<"已全歼。"<<endl;
				copymatrix(preboard,finalboard);
				return;
			}
			if (!initial||((red?after.red-after.blue:after.blue-after.red)>=max&&can)){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=low;
				move_direct=(red?3:0);
				type=2;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canu(low,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(low,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row]=low;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<low<<"竖向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<low<<"竖向：被围剿"<<endl; 
			if(after.blue==0||after.red==0){
					max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=low;
				move_direct=(red?4:1);
				type=3;
				initial=true;
//				cout<<"已全歼。"<<endl;
				copymatrix(preboard,finalboard);
				return;
			}
			if (!initial||((red?after.red-after.blue:after.blue-after.red)>=max&&can)){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=low;
				move_direct=(red?4:1);
				type=3;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
	}
	if(high!=-1&&high!=low){
		if(canlu(high,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(high,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row-1]=high;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<high<<"斜向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<high<<"斜向：被围剿"<<endl; 
			if(after.blue==0||after.red==0){
					max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=high;
				move_direct=(red?5:2);
				type=4;
				initial=true;
//				cout<<"已全歼。"<<endl;
				copymatrix(preboard,finalboard);
				return;
			}
			if (!initial||((red?after.red-after.blue:after.blue-after.red)>=max&&can)){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=high;
				move_direct=(red?5:2);
				type=4;
				initial=true;
				copymatrix(preboard,finalboard);
			}
			
		}
		if(canl(high,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(high,board);
			Location aloc;
			aloc.line=loc.line;
			aloc.row=loc.row-1;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line][loc.row-1]=high;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<high<<"横向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<high<<"横向：被围剿"<<endl; 
			if(after.blue==0||after.red==0){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=high;
				move_direct=(red?3:0);
				type=5;
				initial=true;
				copymatrix(preboard,finalboard);
//				cout<<"已全歼。"<<endl;
				return;
			}
			if (!initial||((red?after.red-after.blue:after.blue-after.red)>=max&&can)){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=high;
				move_direct=(red?3:0);
				type=5;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		if(canu(high,board)){
			copymatrix(board,preboard);
			bool can=true;
			Location loc=chess_location(high,board);
			Location aloc;
			aloc.line=loc.line-1;
			aloc.row=loc.row;
			if(num<=2&&enemynum(aloc,dice,board)>=2) can=false;
			preboard[loc.line-1][loc.row]=high;
			preboard[loc.line][loc.row]=0;
			count_flex(preboard);
			EXP after=count_exp(dice,preboard);
//			if(can)
//			cout<<"推演："<<high<<"竖向：\t红方攻击"<<after.red<<"\t蓝方攻击"<<after.blue<<endl; 
//			else
//			cout<<"推演："<<high<<"竖向：被围剿:"<<endl; 
			if(after.blue==0||after.red==0){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=high;
				move_direct=(red?4:1);
				type=6;
				initial=true;
//				cout<<"已全歼。"<<endl;
				copymatrix(preboard,finalboard);
				return;
			}
			if (!initial||((red?after.red-after.blue:after.blue-after.red)>=max&&can)){
				max=(red?after.red-after.blue:after.blue-after.red);
				move_chess=high;
				move_direct=(red?4:1);
				type=6;
				initial=true;
				copymatrix(preboard,finalboard);
			}
		}
		
	}
//	cout<<"（综合方案）最终决定：";
//	switch(type){
//		case 1:cout<<low<<"斜向"<<endl;break;
//		case 2:cout<<low<<"横向"<<endl;break;
//		case 3:cout<<low<<"竖向"<<endl;break;
//		case 4:cout<<high<<"斜向"<<endl;break;
//		case 5:cout<<high<<"横向"<<endl;break;
//		case 6:cout<<high<<"竖向"<<endl;break;
//		default:cout<<"错误"<<endl;
//	} 
}
int Einstein::logging(std::string s){
	
	clientsocket.sendMsg(s.c_str());
	string head = "action: ";
	head+=s;
	head+='\n';
	head+=output_board(finalboard);
	EXP exp=count_exp(dice,finalboard);
	predis=getalldis(getdis(dice,finalboard));
	head+="**RED ";
	head+=to_string((int)exp.red);
	head+=" : ";
	head+=to_string((int)exp.blue);
	head+=" BLUE**\n";
	cout<<head<<endl;
	logger.push_back(head); 
}

int Einstein::writelog(){
string t;
	t=getCurrentTimeStr();
	int len=t.length();
	for(int i=0;i<len;i++){
		if(t[i]==' '||t[i]==':') t[i]='-';
	}
	t+=".log";
	FILE* pfile=fopen(t.c_str(),"w");
	list<string>::iterator itor=logger.begin();
	while(itor!=logger.end()){
		string s=*itor;
		fputs(s.c_str(),pfile);
		itor++;
	}
	fclose(pfile);
}
//=====================================================================
//*********************************************************************
//assistant function for games.
static string  getCurrentTimeStr(){
	time_t t = time(NULL);	
	char ch[64] = {0};	
	strftime(ch, sizeof(ch) - 1, "%Y-%m-%d %H-%M-%S: ", localtime(&t));     //年-月-日 时-分-秒	
	return ch;
}
void trans(int dice, int *chessboard,int board[][5]){
	if(!is_red(dice)){
	
		for(int i=0;i<25;i++){
			int line = i/5;
			int row = i%5;
			board[line][row]=chessboard[i];
		}
	}
	else{
		for(int i=0;i<25;i++){
			int line=4-i/5;
			int row=4-i%5;
			board[line][row]=chessboard[i];
		}
	}
}
bool valid_input(int board[][5]){
	int c[13]={0};
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(board[i][j]<0||board[i][j]>12)  return false;
			else if(board[i][j]==0) continue;
			else{
				if(c[board[i][j]]==1) return false; //two same chess number
				c[board[i][j]]=1;
			}
		}
	}
	return true;
}
bool is_red(int dice){
	return dice>=1&&dice<=6;
}

Location chess_location(int n,int board[][5]){
	Location loc;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if (board[i][j]==n){
				loc.line=i;
				loc.row=j;
				return loc;
			}
			
		}
	/* if the return value contains -1, that means 
	   the chess has been removed.
	*/
	}
	return loc;
}
bool chess_inboard(int n,int board[][5]){
	Location loc=chess_location(n,board);
	if(loc.line==-1&&loc.row==-1) return false;
	else return true;
}
int get_high(int dice,int board[][5]){
	for(int i=dice;i<=(is_red(dice) ? 6 : 12);i++){
		if(chess_inboard(i,board)) return i;
	}
	return -1;
}
int get_low(int dice,int board[][5]){
	for(int i=dice;i>=(is_red(dice) ? 1 : 7);i--){
		if(chess_inboard(i,board)) return i;
	}
	return -1;
}
bool canl(int n,int board[][5]){
	if(!chess_inboard(n,board)) return false;
	Location loc=chess_location(n,board);
	if(loc.row==0) return false;
	return true;
}
bool canu(int n,int board[][5]){
	if(!chess_inboard(n,board)) return false;
	Location loc=chess_location(n,board);
	if(loc.line==0) return false;
	return true;
}
bool canlu(int n,int board[][5]){
	if(!chess_inboard(n,board)) return false;
	Location loc=chess_location(n,board);
	if(loc.line==0||loc.row==0) return false;
	return true;
}
int dis(int att,int def,int dice,int board[][5]){
	Location attl=chess_location(att,board);
	Location defl=chess_location(def,board);
	int result;
	if(is_red(att)==is_red(def)) result=-100;//Error
	if(attl.line==-1||attl.row==-1||defl.line==-1||defl.row==-1) result=-200;//Error
	if(is_red(att)==is_red(dice)){//如果攻击方为本方 
		if(attl.line<defl.line||attl.row<defl.row) result=-1;
		else{
			result=(attl.line-defl.line)>(attl.row-defl.row)? (attl.line-defl.line):(attl.row-defl.row);
		}
	}
	if(is_red(att)!=is_red(dice)){//若攻击方不为本方 
		if(attl.line>defl.line||attl.row>defl.row) result=-1;
		else{
			result=(defl.line-attl.line)>(defl.row-attl.row)? (defl.line-attl.line):(defl.row-attl.row);
		}
	}
	
	return result;
}
void count_flex(int board[][5]){
	for(int n=1;n<=6;n++){
		int add=0;
		for(int point=1;point<=6;point++){
			if(get_high(point,board)==n||get_low(point,board)==n) add++;
		}
		flex[n]=add;
	}
	for(int n=7;n<=12;n++){
		int add=0;
		for(int point=7;point<=12;point++){
			if(get_high(point,board)==n||get_low(point,board)==n) add++;
		}
		flex[n]=add;
	}
	
}
double kill_pro(int n,int dice,int board[][5]){//敌我方通用 
	bool red=is_red(n);
	double max=-1;
	double kill;
	for(int i=(red?7:1);i<=(red?12:6);i++){
		if(!chess_inboard(i,board)) continue;
		if(dis(i,n,dice,board)==-100||dis(i,n,dice,board)==-200) return -1;
		if(dis(i,n,dice,board)==-1) {
			kill=0;
		}
		else kill=flex[i]/(double)dis(i,n,dice,board);
		if(kill>max) max=kill;
	}
	
	return max;
	
}
double kill_all(int dice,int board[][5]){//对敌方而言 
	bool red=is_red(dice);
	double muti=1;
	int num=0;
	for (int i=(red?7:1);i<=(red?12:6);i++){
		if(!chess_inboard(i,board)) continue;
		double kill=kill_pro(i,dice,board);
	//	if(kill==0) cout<<"棋子"<<i<<"不能被歼灭"<<endl; 
		muti*=kill;
		num++;
	}
	return pow(muti,1.0/num);
}
EXP count_exp(int dice,int board[][5]){//a=6V*log6 (F+1)/K
	EXP exp;
	for(int i=1;i<=12;i++){
		bool self=(is_red(dice)==is_red(i));
		if(!chess_inboard(i,board)) continue;
		Location loc=chess_location(i,board);
		double att;
		double val=self?value[loc.line][loc.row]:value[4-loc.line][4-loc.row];
		double k=kill_pro(i,dice,board);
		if(k!=0) 
		att=6.0*val*(1.0/4.0*k+1.0)*(pow(2.0,flex[i]-6.0)+2.0);
		else
		att=6.0*val*2.5*(pow(2.0,flex[i]-6.0)+2.0);
		if(i>=1&&i<=6) exp.red+=att;
		else exp.blue+=att;
		//if(i<=6) cout<<"棋子"<<i<<"被歼灭可能度"<<((k==0.125)?0:k)<<"\t棋盘价值"<<val<<"\t攻击力"<<att<<endl;
	}
	return exp;
}
int chessnum(int dice,int board[][5]){
	int num=0;
	bool red=is_red(dice);
	for(int i=(red?1:7);i<=(red?6:12);i++){
		if(chess_inboard(i,board)) num++;
	}
	return num;
} 
void copymatrix(int a[][5],int b[][5]){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			b[i][j]=a[i][j];
		}
	}
}
int enemynum(Location loc,int dice,int board[][5]){
	bool red=is_red(dice);
	int num=0;
	if(loc.line==0){
		if(red?(board[0][loc.row-1]>=7&&board[0][loc.row-1]<=12):(board[0][loc.row-1]>=1&&board[0][loc.row-1]<=6)) return 1;
	}
	if(loc.row==0){
		if(red?(board[loc.line-1][0]>=7&&board[loc.line-1][0]<=12):(board[loc.line-1][0]>=1&&board[loc.line-1][0]<=6)) return 1;
	}
	if(red?(board[0][loc.row-1]>=7&&board[0][loc.row-1]<=12):(board[0][loc.row-1]>=1&&board[0][loc.row-1]<=6)) num++;
	if(red?(board[loc.line-1][0]>=7&&board[loc.line-1][0]<=12):(board[loc.line-1][0]>=1&&board[loc.line-1][0]<=6)) num++;
	if(red?(board[loc.line-1][loc.row-1]>=7&&board[loc.line-1][loc.row-1]<=12):(board[loc.line-1][loc.row-1]>=1&&board[loc.line-1][loc.row-1]<=6)) num++;
	return num;
}
DIS getdis(int dice,int board[][5]){
	DIS dis;
	for(int i=1;i<=6;i++){
		int distance;
		if(!chess_inboard(i,board)) continue;
		Location loc=chess_location(i,board);
		if(is_red(dice)) distance=loc.line>loc.row? loc.line:loc.row;
		else distance=loc.line>loc.row? (4-loc.row):(4-loc.line);
		dis.red+=distance; 
	}
	for(int i=7;i<=12;i++){
		int distance;
		if(!chess_inboard(i,board)) continue;
		Location loc=chess_location(i,board);
		if(!is_red(dice)) distance=loc.line>loc.row? loc.line:loc.row;
		else distance=loc.line>loc.row? (4-loc.row):(4-loc.line);
		dis.blue+=distance; 
	}
	return dis;
}
int getalldis(DIS dis){
	return dis.red+dis.blue;
}
string output_board(int board[][5]){
	string s;
	s.clear();
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(board[i][j]!=0){
			
				string num=to_string(board[i][j]);
				s+=num;
			}
			else{
				s+='-';
			}
			s+='\t';
		}
		s+='\n';
	}
	return s;
}
//test
void test(int dice){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			cout<<board[i][j]<<"\t";
		}
		cout<<endl;
	}
}
