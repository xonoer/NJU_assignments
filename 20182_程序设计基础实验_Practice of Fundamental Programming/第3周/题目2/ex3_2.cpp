/* 数组下标   0   1   2   3     4     5     6   7         8      9     10    11    12   13      14 
   牌  名     3   4   5   6     7     8     9   10        J      Q     K     A      2   joker   JOKER 
   类型名     单  双  三  三一 三二  连对 顺子  四二单  四二对  飞机  飞一 飞二  炸弹  王炸  */
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
enum CardName{C_3,C_4,C_5,C_6,C_7,C_8,C_9,C_10,C_J,C_Q,C_K,C_A,C_2,C_joker,C_JOKER};
enum CardType{sig,doub,trip,tri1,tri2,con2,con1,fwith1,fwith2,plane,p1,p2,boom,maxboom};
struct Node{ 
	bool canplay; //出牌时使用，能否出牌。 
	CardName card1;
	CardName card2; //连对、顺子、飞机的终止牌 ，其他类型则与card1一样 。 
	int appendnum;  //这两行仅在出牌时使用，存储带的牌及其数量。 
	CardName append[20]; 
};
struct Player{
	string player_name;
	int* player_card;
	int last_card[15];
	Player* next;
};
 
int handCard1[15];
int handCard2[15];
int handCard3[15];

int lastCard[15];

Node* type[14];

CardName transferName(char *p){    //输入字符串与牌名的转换 
	if(*p=='j') return C_joker;
	if(*p=='J'){
		if(*(p+1)=='O') return C_JOKER;
		else return C_J;
	}
	if(*p=='Q') return C_Q;
	if(*p=='K') return C_K;
	if(*p=='A') return C_A;
	if(*p=='2') return C_2;
	if(*p=='1') return C_10;
	if((*p)>='3'&&(*p)<='9') return (CardName)((*p)-'0'-3);
}
void inputCard(int* c,int num){    //输入卡牌字符串并转换 
	char card[7];
	for(int i=0;i<num;i++){
		cin>>card;
		CardName id=transferName(card);
		c[id]++;
	}
}
//以下为各种牌型判断函数 
bool is_maxboom(int* card){//王炸 13
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if (i>=C_3&&i<=C_2&&card[i]!=0) return false; 
		if (i>=C_joker&&i<=C_JOKER&&card[i]!=1) return false;
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=C_joker;
	p->card2=C_JOKER;
	type[maxboom]=p;
	return true;
}
bool is_sig(int *card){//单牌 0
	CardName target=C_JOKER;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0&&card[i]!=1) return false;
		if(card[i]==1){
			if(target<i) return false;
			else target=i;
		}
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[sig]=p;
	return true;
}
bool is_doub(int *card){//对子 1
	CardName target=C_JOKER;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0&&card[i]!=2) return false;
		if(card[i]==2){
			if(target<i) return false;
			else target=i;
		}
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[doub]=p;
	return true;
}
bool is_trip(int *card){//三张 2 
	CardName target=C_JOKER;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0&&card[i]!=3) return false;
		if(card[i]==3){
			if(target<i) return false;
			else target=i;
		}
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[trip]=p;
	return true;
} 
bool is_boom(int *card){//炸弹 12 
	CardName target=C_JOKER;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0&&card[i]!=4) return false;
		if(card[i]==4){
			if(target<i) return false;
			else target=i;
		}
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[boom]=p;
	return true;
} 
bool is_tri1(int *card){//三带一 3 
	CardName target=C_JOKER;
	CardName append=C_JOKER;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0&&card[i]!=1&&card[i]!=3) return false;
		if(card[i]==3){
			if(target<i) return false;
			else target=i;
		}
		if(card[i]==1){
			if(append<i) return false;
			else append=i;
		}
		if(i==C_JOKER&&card[i]==0&&append==C_JOKER) return false;
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[tri1]=p;
	return true;

}
bool is_tri2(int *card){//三带二 4 
	CardName target=C_JOKER;
	CardName append=C_JOKER;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0&&card[i]!=2&&card[i]!=3) return false;
		if(card[i]==3){
			if(target<i) return false;
			else target=i;
		}
		if(card[i]==2){
			if(append<i) return false;
			else append=i;
		}
	}
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[tri2]=p;
	return true;
} 
bool is_fwith1(int *card){//四带二单 7 
	CardName target=C_JOKER;
	int count=0;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]==3) return false;
		if(card[i]==4) {
			if(target<i) return false;
			else target=i;
		}
	}
	if(target==C_JOKER) return false;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(i==target) continue;
		count+=card[i];
	}
	if(count!=2) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[fwith1]=p;
	return true;
} 
bool is_fwith2(int *card){//四带二对 8 
	CardName target=C_JOKER;
	int count=0;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]==3||card[i]==1) return false;
		if(card[i]==4) {
			if(target<i) return false;
			else target=i;
		}
	}
	if(target==C_JOKER) return false;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(i==target) continue;
		count+=card[i];
	}
	if(count!=4) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=p->card2=target;
	type[fwith2]=p;
	return true;
} 
bool is_con1(int *card){//顺子 6 
	CardName start;
	CardName finish;
	for(start=C_3;start<=C_J;start=(CardName)(start+1)){
		if(card[start]>=2) return false;
		if(card[start]==1) break;
	}
	for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
		if(card[finish]>=2) return false;
		if(card[finish]==0) break;
	}
	for(CardName i=(CardName)(finish+1);i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]>=1) return false;
	}
	if((int)(finish-start)<5) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=start;
	p->card2=(CardName)(finish-1);
	type[con1]=p;
	return true;
}
bool is_con2(int *card){//连对 5 
	CardName start;
	CardName finish;
	for(start=C_3;start<=C_K;start=(CardName)(start+1)){
		if(card[start]>=3||card[start]==1) return false;
		if(card[start]==2) break;
	}
	for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
		if(card[finish]>=3||card[finish]==1) return false;
		if(card[finish]==0) break;
	}
	for(CardName i=(CardName)(finish+1);i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]>=1) return false;
	}
	if((int)(finish-start)<3) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=start;
	p->card2=(CardName)(finish-1);
	type[con2]=p;
	return true;
} 
bool is_plane(int *card){//飞机 9 
	CardName start;
	CardName finish;
	for(start=C_3;start<=C_A;start=(CardName)(start+1)){
		if(card[start]>=4||card[start]==1||card[start]==2) return false;
		if(card[start]==3) break;
	}
	for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
		if(card[finish]>=4||card[finish]==1||card[finish]==2) return false;
		if(card[finish]==0) break;
	}
	for(CardName i=(CardName)(finish+1);i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]>=1) return false;
	}
	if((int)(finish-start)<2) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=start;
	p->card2=(CardName)(finish-1);
	type[plane]=p;
	return true;
}
bool is_p1(int *card){//飞机带一张 10 
	CardName start;
	CardName finish;
	int count=0;
	for(start=C_3;start<=C_A;start=(CardName)(start+1)){
		if(card[start]==3) break;
	}
	for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
		if(card[finish]!=3) break;
	}
	if((int)(finish-start)<2){//就怕有一些人才，小翼出三张一样的。所以再来一遍 
		for(start=(CardName)(finish+1);start<=C_J;start=(CardName)(start+1)){
			if(card[start]==3) break;
		}
		for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
			if(card[finish]==0) break;
		}
	}
	if((int)(finish-start)<2) return false;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(i<start||i>=finish) count+=card[i];
	} 
	if(count!=(int)(finish-start)) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=start;
	p->card2=(CardName)(finish-1);
	type[p1]=p;
	return true;
}
bool is_p2(int *card){//飞机带两张 11 
	CardName start;
	CardName finish;
	int count=0;
	for(start=C_3;start<=C_A;start=(CardName)(start+1)){
		if(card[start]==3) break;
	}
	for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
		if(card[finish]!=3) break;
	}
	if((int)(finish-start)<2) return false;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(i<start||i>=finish){
			if(card[i]==1||card[i]==3) return false;
			count+=card[i];
		}
	}
	if(count!=(int)(finish-start)*2) return false;
	Node *p=new Node;
	p->canplay=true;
	p->card1=start;
	p->card2=(CardName)(finish-1);
	type[p2]=p;
	return true;
} 

CardType judgeType(int* card){ //判断牌型 
	for(int i=0;i<13;i++) type[i]=NULL;
	if(is_maxboom(card)) return maxboom;
	if(is_sig(card)) return sig;
	if(is_doub(card)) return doub;
	if(is_trip(card)) return trip;
	if(is_tri1(card)) return tri1;
	if(is_tri2(card)) return tri2;
	if(is_boom(card)) return boom;
	if(is_fwith1(card)) return fwith1;
	if(is_fwith2(card)) return fwith2;
	if(is_con1(card)) return con1;
	if(is_con2(card)) return con2;
	if(is_plane(card)) return plane;
	if(is_p1(card)) return p1;
	if(is_p2(card)) return p2;
}
//以下为各种出牌函数 
Node askfor_maxboom(int *card){//王炸 
	Node play;
	if(card[C_joker]==1&&card[C_JOKER]==1){
		play.canplay=true;
		play.card1=C_joker;
		play.card2=C_JOKER;
		play.appendnum=0;
		card[C_joker]=card[C_JOKER]=0;
		return play;
	}
	else{
		play.canplay=false;
		return play;
	}
}
Node askfor_boom(int *card){//炸弹
	Node play;
	CardName min;
	if (type[boom]==NULL) min=C_3;
	else min=(CardName)(type[boom]->card1+1);
	for(CardName i=min;i<=C_2;i=(CardName)(i+1)){
		if(card[i]==4){
			play.canplay=true;
			play.card1=play.card2=i;
			play.appendnum=0;
			card[i]-=4;
			return play;
		}
	} 
	play.canplay=false;
	return play;
}
Node askfor_sig(int *card){//单张
	Node play;
	CardName min=type[sig]->card1;
	for(CardName i=(CardName)(min+1);i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]==1){
			play.canplay=true;
			play.card1=play.card2=i;
			play.appendnum=0;
			card[i]--;
			return play;
		}
	} 
	play.canplay=false;
	return play;
}
Node askfor_doub(int *card){//对子 
	Node play;
	CardName min=type[doub]->card1;
	for(CardName i=(CardName)(min+1);i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=2){
			play.canplay=true;
			play.card1=play.card2=i;
			play.appendnum=0;
			card[i]-=2;
			return play;
		}
	} 
	play.canplay=false;
	return play;
}
Node askfor_trip(int *card){//三张 
	Node play;
	CardName min=type[trip]->card1;
	for(CardName i=(CardName)(min+1);i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=3){
			play.canplay=true;
			play.card1=play.card2=i;
			play.appendnum=0;
			card[i]-=3;
			return play;
		}
	} 
	play.canplay=false;
	return play;
}
Node askfor_tri1(int *card){//三带一 
	Node play;
	play.card1=C_JOKER;
	CardName min=type[tri1]->card1;
	for(CardName i=(CardName)(min+1);i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=3){
			play.card1=play.card2=i;
			break;
		} 
	} 
	if(play.card1==C_JOKER){
		play.canplay=false;
		return play;
	}
	card[play.card1]-=3;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]>=1){
			play.canplay=true;
			play.appendnum=1;
			play.append[0]=i;
			card[i]--; 
			return play;
		}
	}
	card[play.card1]+=3;
	play.canplay=false;
	return play;
}
Node askfor_tri2(int *card){//三带二 
	Node play;
	play.card1=C_JOKER;
	CardName min=type[tri2]->card1;
	for(CardName i=(CardName)(min+1);i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=3){
			play.card1=play.card2=i;
			break;
		} 
	} 
	if(play.card1==C_JOKER){
		play.canplay=false;
		return play;
	}
	card[play.card1]-=3;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]>=2){
			play.canplay=true;
			play.appendnum=2;
			play.append[0]=play.append[1]=i;
			card[play.card1]-=3;
			card[i]-=2; 
			return play;
		}
	}
	card[play.card1]+=3;
	play.canplay=false;
	return play;
}
Node askfor_fwith1(int *card){//四带二单 
	Node play;
	play.card1=C_JOKER;
	CardName min=type[fwith1]->card1;
	for(CardName i=(CardName)(min+1);i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=4){
			play.card1=play.card2=i;
			break;
		} 
	} 
	if(play.card1==C_JOKER){
		play.canplay=false;
		return play;
	}
	card[play.card1]-=4;
	play.appendnum=0;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		while(card[i]>=1){
			play.append[play.appendnum]=i;
			play.appendnum++;
			card[i]--;
			if(play.appendnum==2) break;
		}
		if(play.appendnum==2) break;
	}
	if(play.appendnum==2){
		play.canplay=true;
		return play;
	}
	else{
		card[play.card1]+=4;
		for(int i=0;i<play.appendnum;i++){
			card[play.append[i]]++;
		}
		play.canplay=false;
		return play;
	}
} 
Node askfor_fwith2(int *card){//四带二对 
	Node play;
	play.card1=C_JOKER;
	CardName min=type[fwith2]->card1;
	for(CardName i=(CardName)(min+1);i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=4){
			play.card1=play.card2=i;
			break;
		} 
	} 
	if(play.card1==C_JOKER){
		play.canplay=false;
		return play;
	}
	card[play.card1]-=4;
	play.appendnum=0;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		while(card[i]>=2){
			play.append[play.appendnum]=play.append[play.appendnum+1]=i;
			play.appendnum+=2;
			card[i]-=2;
			if(play.appendnum==4) break;
		}
		if(play.appendnum==4) break;
	}
	if(play.appendnum==4){
		play.canplay=true;
		return play;
	}
	else{
		card[play.card1]+=4;
		for(int i=0;i<play.appendnum;i++){
			card[play.append[i]]++;
		}
		play.canplay=false;
		return play;
	}
}
Node askfor_con1(int *card){ //顺子 
	Node play;
	play.canplay=false;
	CardName start=type[con1]->card1;
	CardName finish=type[con1]->card2;
	int num=(int)(finish-start+1);
	for(CardName i=(CardName)(start+1);i<=C_J;i=(CardName)(i+1)){
		CardName j=i;
		for(j=i;j<(CardName)(i+num);j=(CardName)(j+1)){
			if(card[j]==0) break;
		}
		if(j==(CardName)(i+num)){
			play.canplay=true;
			play.card1=i;
			play.card2=(CardName)(i+num-1);
			play.appendnum=0;
			for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]--;
			return play;
		}
	}
	return play;
}
Node askfor_con2(int *card){ //连对 
	Node play;
	play.canplay=false;
	CardName start=type[con2]->card1;
	CardName finish=type[con2]->card2;
	int num=(int)(finish-start+1);
	for(CardName i=(CardName)(start+1);i<=C_K;i=(CardName)(i+1)){
		CardName j=i;
		for(j=i;j<(CardName)(i+num);j=(CardName)(j+1)){
			if(card[j]<=1) break;
		}
		if(j==(CardName)(i+num)){
			play.canplay=true;
			play.card1=i;
			play.card2=(CardName)(i+num-1);
			play.appendnum=0;
			for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]-=2;
			return play;
		}
	}
	return play;
}
Node askfor_plane(int *card){//飞机 
	Node play;
	play.canplay=false;
	CardName start=type[plane]->card1;
	CardName finish=type[plane]->card2;
	int num=(int)(finish-start+1);
	for(CardName i=(CardName)(start+1);i<=C_A;i=(CardName)(i+1)){
		CardName j=i;
		for(j=i;j<(CardName)(i+num);j=(CardName)(j+1)){
			if(card[j]<=2) break;
		}
		if(j==(CardName)(i+num)){
			play.canplay=true;
			play.card1=i;
			play.card2=(CardName)(i+num-1);
			play.appendnum=0;
			for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]-=3;
			return play;
		}
	}
	return play;
} 
Node askfor_p1(int *card){ //飞机带单 
	Node play;
	play.canplay=false;
	CardName start=type[p1]->card1;
	CardName finish=type[p1]->card2;
	int num=(int)(finish-start+1);
	for(CardName i=(CardName)(start+1);i<=C_A;i=(CardName)(i+1)){
		CardName j=i;
		for(j=i;j<(CardName)(i+num);j=(CardName)(j+1)){
			if(card[j]<=2) break;
		}
		if(j==(CardName)(i+num)){
			play.canplay=true;
			play.card1=i;
			play.card2=(CardName)(i+num-1);
			play.appendnum=0;
		}
	}
	if(play.canplay==false) return play;
	for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]-=3;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		while(card[i]>=1){
			play.append[play.appendnum]=i;
			play.appendnum++;
			card[i]--;
			if(play.appendnum==num) break;
		}
		if(play.appendnum==num) break;
	}
	if(play.appendnum==num) return play;
	else{
		play.canplay=false;
		for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]+=3;
		for(int i=0;i<play.appendnum;i++) card[play.append[i]]++;
		return play;
	}
}
Node askfor_p2(int *card){//飞机带对 
	Node play;
	play.canplay=false;
	CardName start=type[p2]->card1;
	CardName finish=type[p2]->card2;
	int num=(int)(finish-start+1);
	for(CardName i=(CardName)(start+1);i<=C_A;i=(CardName)(i+1)){
		CardName j=i;
		for(j=i;j<(CardName)(i+num);j=(CardName)(j+1)){
			if(card[j]<=2) break;
		}
		if(j==(CardName)(i+num)){
			play.canplay=true;
			play.card1=i;
			play.card2=(CardName)(i+num-1);
			play.appendnum=0;
		}
	}
	if(play.canplay==false) return play;
	for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]-=3;
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		while(card[i]>=2){
			play.append[play.appendnum]=play.append[play.appendnum+1]=i;
			play.appendnum+=2;
			card[i]-=2;
			if(play.appendnum==num*2) break;
		}
		if(play.appendnum==num*2) break;
	}
	if(play.appendnum==num*2) return play;
	else{
		play.canplay=false;
		for(CardName k=play.card1;k<=play.card2;k=(CardName)(k+1)) card[k]+=3;
		for(int i=0;i<play.appendnum;i++) card[play.append[i]]++;
		return play;
	}
} 

void output(CardName n){ //用于输出 
	switch (n){
		case C_3:cout<<"3 ";break;
		case C_4:cout<<"4 ";break;
		case C_5:cout<<"5 ";break;
		case C_6:cout<<"6 ";break;
		case C_7:cout<<"7 ";break;
		case C_8:cout<<"8 ";break;
		case C_9:cout<<"9 ";break;
		case C_10:cout<<"10 ";break;
		case C_J:cout<<"J ";break;
		case C_Q:cout<<"Q ";break;
		case C_K:cout<<"K ";break;
		case C_A:cout<<"A ";break;
		case C_2:cout<<"2 ";break;
		case C_joker:cout<<"joker ";break;
		case C_JOKER:cout<<"JOKER ";break;
	}
}
void playforboom(int *card,int *last_card){ //询问炸弹 
	Node result=askfor_boom(card);
	if(result.canplay){
		for(int i=0;i<4;i++) {
			output(result.card1);
			last_card[result.card1]++; 
		} 
	}
	else if(askfor_maxboom(card).canplay){
		cout<<"JOKER joker";
		last_card[C_JOKER]++;
		last_card[C_joker]++;
	}
	else{
		cout<<"pass.";
	}
}
void sortarr(CardName *a,int num){ //数组排序 
	for(int i=0;i<num-1;i++){
		for(int j=i+1;j<num;j++){
			if(a[i]<a[j]){
				CardName temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
}
void afterplay(int *card,CardType t,int *last_card){ //（跟牌）出牌类型控制 
	Node result;
	switch(t){
		case maxboom: cout<<"pass.";break;
		case boom: playforboom(card,last_card);break;
		case sig:
			result=askfor_sig(card);
			if(result.canplay){
				output(result.card1);
				last_card[result.card1]++;
			}
			else playforboom(card,last_card);
			break;
		case doub:
			result=askfor_doub(card);
			if(result.canplay){
				for(int i=0;i<2;i++) {
					output(result.card1);
					last_card[result.card1]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case trip:
			result=askfor_trip(card);
			if(result.canplay){
				for(int i=0;i<3;i++) {
					output(result.card1);
					last_card[result.card1]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case tri1:
			result=askfor_tri1(card);
			if(result.canplay){
				if(result.card1>result.append[0]){
					for(int i=0;i<3;i++) {
						output(result.card1);
						last_card[result.card1]++;
					}
					output(result.append[0]);
					last_card[result.append[0]]++;
				}
				else{
					output(result.append[0]);
					last_card[result.append[0]]++;
					for(int i=0;i<3;i++) {
						output(result.card1);
						last_card[result.card1]++;
					}
				}
			}
			else playforboom(card,last_card);
			break;
		case tri2:
			result=askfor_tri2(card);
			if(result.canplay){
				if(result.card1>result.append[0]){
					for(int i=0;i<3;i++) {
						output(result.card1);
						last_card[result.card1]++;
					}
					for(int i=0;i<2;i++) {
						output(result.append[0]);
						last_card[result.append[0]]++;
					}
				}
				else{
					for(int i=0;i<2;i++) {
						output(result.append[0]);
						last_card[result.append[0]]++;
					}
					for(int i=0;i<3;i++) {
						output(result.card1);
						last_card[result.card1]++;
					}
				}
			}
			else playforboom(card,last_card);
			break;
		case fwith1:
			result=askfor_fwith1(card);
			if(result.canplay){
				result.append[2]=result.append[3]=result.append[4]=result.append[5]=result.card1;
				sortarr(result.append,6);
				for(int i=0;i<6;i++) {
					output(result.append[i]);
					last_card[result.append[i]]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case fwith2:
			result=askfor_fwith2(card);
			if(result.canplay){
				result.append[4]=result.append[5]=result.append[6]=result.append[7]=result.card1;
				sortarr(result.append,8);
				for(int i=0;i<8;i++) {
					output(result.append[i]);
					last_card[result.append[i]]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case con1:
			result=askfor_con1(card);
			if(result.canplay){
				for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)) {
					output(i);
					last_card[i]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case con2:
			result=askfor_con2(card);
			if(result.canplay){
				for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
					for(int k=0;k<2;k++) {
						output(i);
						last_card[i]++;
					}
				}
			}
			else playforboom(card,last_card);
			break;
		case plane:
			result=askfor_plane(card);
			if(result.canplay){
				for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
					for(int k=0;k<3;k++){
						output(i);
						last_card[i]++;
					}
				}
			}
			else playforboom(card,last_card);
			break;
		case p1:
			result=askfor_p1(card);
			if(result.canplay){
				int num=(int)(result.card2-result.card1+1);
				CardName card=result.card1;
				for(int i=result.appendnum;i<4*num;i+=3){
					result.append[i]=result.append[i+1]=result.append[i+2]=card;
					card=(CardName)(card+1);
				}
				sortarr(result.append,4*num);
				for(int i=0;i<4*num;i++) {
					output(result.append[i]);
					last_card[i]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case p2:
			result=askfor_p2(card);
			if(result.canplay){
				int num=(int)(result.card2-result.card1+1);
				CardName card=result.card1;
				for(int i=result.appendnum;i<5*num;i+=3){
					result.append[i]=result.append[i+1]=result.append[i+2]=card;
					card=(CardName)(card+1);
				}
				sortarr(result.append,5*num);
				for(int i=0;i<5*num;i++) {
					output(result.append[i]);
					last_card[i]++;
				}
			}
			else playforboom(card,last_card);
			break;
		default: cout<<"pass.";break; 
	}
}
//以上全部为跟牌操作
//以下三种牌型，如果有，优先出掉，然后考虑散牌的情况。 （不拆炸弹） 
Node has_con1(int *card){//是否有顺子 
	Node play;
	for(CardName start=C_3;start<=C_J;start=(CardName)(start+1)){
		if(card[start]>=1&&card[start]<4){
			CardName finish;
			for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
				if(card[finish]==0||card[finish]==4) break;
			}
			if((int)(finish-start)>=5){
				play.canplay=true;
				play.card1=start;
				play.card2=(CardName)(finish-1);
				play.appendnum=0;
				return play;
			}
		}
	}
	play.canplay=false;
	return play;
} 
Node has_con2(int *card){//是否有连对 
	Node play;
	for(CardName start=C_3;start<=C_J;start=(CardName)(start+1)){
		if(card[start]>=2&&card[start]<4){
			CardName finish;
			for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
				if(card[finish]==0||card[finish]==4||card[finish]==1) break;
			}
			if((int)(finish-start)>=3){
				play.canplay=true;
				play.card1=start;
				play.card2=(CardName)(finish-1);
				play.appendnum=0;
				return play;
			}
		}
	}
	play.canplay=false;
	return play;
} 
Node has_tri(int *card){//是否有三张或飞机
 	Node play;
	for(CardName start=C_3;start<=C_J;start=(CardName)(start+1)){
		if(card[start]==3){
			CardName finish;
			for(finish=(CardName)(start+1);finish<=C_2;finish=(CardName)(finish+1)){
				if(card[finish]!=3) break;
			}
			if((int)(finish-start)>=1){
				play.canplay=true;
				play.card1=start;
				play.card2=(CardName)(finish-1);
				play.appendnum=0;
				return play;
			}
		}
	}
	play.canplay=false;
	return play;
	
} 
void initplay(int *card,int *last_card){//首位出牌
	Node result=has_con2(card);
	if(result.canplay){
		for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
			card[i]-=2;
			output(i);output(i);last_card[i]+=2;
			
		}
		return;
	}
	result=has_con1(card);
	if(result.canplay){
		for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
			card[i]--;
			output(i);last_card[i]++;
			
		}
		return;
	}
	result=has_tri(card);
	if(result.canplay){
		CardName start=result.card1;
		CardName finish=result.card2;
		int num=(int)(finish-start+1);
		for(CardName i=finish;i>=start;i=(CardName)(i-1)){
			card[i]-=3;
		}
		for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
			while(card[i]>=2&&card[i]<4){
				result.append[result.appendnum]=result.append[result.appendnum+1]=i;
				card[i]-=2;
				result.appendnum+=2;
				if(result.appendnum==num*2) break;
			}
			if(result.appendnum==num*2) break;
		}
		if(result.appendnum==num*2){
			CardName thecard=start;
			for(int i=result.appendnum;i<5*num;i+=3){
				result.append[i]=result.append[i+1]=result.append[i+2]=thecard;
				thecard=(CardName)(thecard+1);
			}
			sortarr(result.append,5*num);
			for(int i=0;i<5*num;i++){
				 output(result.append[i]);
				 last_card[result.append[i]]++;
			}
			return;
		}
		for(int i=0;i<result.appendnum;i++) card[result.append[i]]++;
		result.appendnum=0;
		for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
			while(card[i]>=1&&card[i]<4){
				result.append[result.appendnum]=i;
				card[i]--;
				result.appendnum++;
				if(result.appendnum==num) break;
			}
			if(result.appendnum==num) break;
		}
		if(result.appendnum==num){
			CardName thecard=start;
			for(int i=result.appendnum;i<4*num;i+=3){
				result.append[i]=result.append[i+1]=result.append[i+2]=thecard;
				thecard=(CardName)(thecard+1);
			}
			sortarr(result.append,4*num);
			for(int i=0;i<4*num;i++) {
				output(result.append[i]);
				last_card[result.append[i]]++;
			}
			return;
		}
		for(int i=0;i<result.appendnum;i++) card[result.append[i]]++;
		result.appendnum=0;
		for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
			card[i]--;
			output(i);output(i);output(i);last_card[i]+=3;
			
		}
		return;
	}
	//以上三种情况都不满足：
	CardName boom=C_JOKER;
	for(CardName i=C_3;i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=1&&card[i]<4){
			int num=card[i];
			for(int j=0;j<num;j++) {
				output(i);
				last_card[i]++;
				card[i]--;
			}
			return;
		}
		if(card[i]==4) boom=i;
	} 
	if(card[C_joker]==1&&card[C_JOKER]==0){
		card[C_joker]--;
		output(C_joker);
		last_card[C_joker]++;
		return;
	} 
	if(card[C_JOKER]==1&&card[C_joker]==0){
		card[C_JOKER]--;
		output(C_JOKER);
		last_card[C_JOKER]++;
		return;
	}
	if(boom!=C_JOKER){
		for(int i=0;i<4;i++){
			card[boom]--;
			output(boom);
			last_card[boom]++;
		}
		return;
	}
	if(card[C_joker]==1&&card[C_JOKER]==1){
		card[C_joker]--;
		output(C_joker);
		last_card[C_joker]++;
		card[C_JOKER]--;
		output(C_JOKER);
		last_card[C_JOKER]++;
		return;
	}
}
bool card_remain(Player *player){
	bool remain=false;
	for(CardName i=C_JOKER;i>=C_3;i=(CardName)(i-1)){
		if(player->player_card[i]>=1){
			remain=true;
			for(int k=0;k<player->player_card[i];k++) output(i);
		}
	}
	if(remain==false){
		cout<<"No card remains."<<endl<<endl;
		cout<<"Game Over."<<endl;
		cout<<player->player_name<<"wins!"<<endl;
	}
	return remain;
}
void deleteCard(int *card){
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)) card[i]=0;
}
bool is_empty(int *card){
	for(CardName i=C_3;i<=C_JOKER;i=(CardName)(i+1)){
		if(card[i]!=0) return false;
	}
	return true;
}
void gameplay(int *card1,int* card2,int *card3){
	Player* head=NULL;
	Player* p1=new Player;
	p1->player_name="Player 1: ";
	p1->player_card=card1;
	deleteCard(p1->last_card);
	head=p1;
	Player* p2=new Player;
	p2->player_name="Player 2: ";
	p2->player_card=card2;
	deleteCard(p2->last_card);
	p1->next=p2;
	Player* p3=new Player;
	p3->player_name="Player 3: ";
	p3->player_card=card3;
	deleteCard(p3->last_card);
	p2->next=p3;
	p3->next=p1;
	bool remain=false;
	for(Player *p=head;!remain;p=p->next){

		int* t=p->next->next->last_card;
		int* t2=p->next->last_card;
		cout<<p->player_name<<"action: ";
		if(is_empty(t)&&is_empty(t2)){
			deleteCard(p->last_card);
			initplay(p->player_card,p->last_card);
		}
		else	if(!is_empty(t)){
			CardType target=judgeType(t);
			deleteCard(p->last_card);
			afterplay(p->player_card,target,p->last_card);
		}
		else	if(!is_empty(t2)){
			CardType target=judgeType(t2);
			deleteCard(p->last_card);
			afterplay(p->player_card,target,p->last_card);
		}
		cout<<endl;
		cout<<p->player_name<<"remain: ";
		remain=!card_remain(p);
		cout<<endl<<endl;
	}
}
void card_display(int *card1,int* card2,int *card3){
	cout<<"初始手牌展示："<<endl;
	cout<<"Player 1（地主）: ";
	for(int i=14;i>=0;i--){
		for(int j=0;j<card1[i];j++) output((CardName)i);
	} 
	cout<<endl<<"Player 2（农民）: ";
	for(int i=14;i>=0;i--){
		for(int j=0;j<card2[i];j++) output((CardName)i);
	} 
	cout<<endl<<"Player 3（农民）: ";
	for(int i=14;i>=0;i--){
		for(int j=0;j<card3[i];j++) output((CardName)i);
	} 
	cout<<endl<<endl;
	cout<<"Game Start!"<<endl<<endl;
}
int main(){
	freopen("test.txt","r",stdin);
	freopen("result.txt","w",stdout);
	inputCard(handCard1,20);
	inputCard(handCard2,17);
	inputCard(handCard3,17);
	card_display(handCard1,handCard2,handCard3);
	gameplay(handCard1,handCard2,handCard3);
	return 0;
} 
