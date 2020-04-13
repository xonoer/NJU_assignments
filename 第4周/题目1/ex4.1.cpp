// Please use UTF-8 encoding so that the comments can be displayed correctly.
// 标注TODO的是你需要完善的地方
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

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
Node* type[14];
class Card : public string {
public:
    static const int N_CARD_VALUES;
    static const int N_CARD_SUITS;
    static const string CARD_VALUES[];
    static const string CARD_SUITS[];

    Card(const char* str) :string(str) {}; 
    Card() :string() {};                   
    Card(string str) :string(str) {};

    static vector<Card> get_new_deck();

    // 重载操作符，使得牌面可以比较大小
    bool operator <(const Card &other) const;
    bool operator >(const Card &other) const;
};


class DDZPlayer {
protected:
    string name;  // 玩家名
    int position;  // 你的位置编号，0为地主，1为地主下家，2为地主上家
    vector<Card> hand;  // 手牌

    int prePos;  //上一个出牌的人位置编号，-1表示还没有人出过牌
    vector<Card> prePlay;  // 上一个出牌的人出了什么牌？

    bool legal(vector<Card> cards);  // 判断当前打出cards是否合法
    void substractFromHand(vector<Card> cards);  // 从当前手牌中删去cards中的牌
public:
    DDZPlayer(string name);  // 构造函数，初始化玩家名
    string getName();
    virtual void draw(Card card);  // 将cards中的牌加入手牌
    virtual void draw(vector<Card> cards);  // 将cards中的牌加入手牌
    virtual void setPosition(int pos);  // 初始化用，决定地主后设置
    virtual void showHand();  // 打印手牌
    virtual void observed(int pos, vector<Card> cards);  // 观测到玩家出牌
    virtual vector<Card> play();  // 轮到自己时决定出什么牌
    bool leftNoCard();  // 返回是否打完了牌？
};


class DDZGame {
private:
    static int my_random (int i);  // 洗牌时用到的随机函数
    vector<DDZPlayer*> players;  // 保存三个玩家的指针
    void showCards(vector<Card> cards);  // 输出一组牌

public:
    DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  // 构造函数
    void run();  // 执行游戏流程
};


class DDZHumanPlayer: public DDZPlayer {
public:
    DDZHumanPlayer(string name) : DDZPlayer(name) {};
    vector<Card> play();
};

void transferCard(vector<Card> hand,int* targetCard){
	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
		if(*i=="3") targetCard[C_3]++;
		if(*i=="4") targetCard[C_4]++;
		if(*i=="5") targetCard[C_5]++;
		if(*i=="6") targetCard[C_6]++;
		if(*i=="7") targetCard[C_7]++;
		if(*i=="8") targetCard[C_8]++;
		if(*i=="9") targetCard[C_9]++;
		if(*i=="10") targetCard[C_10]++;
		if(*i=="J") targetCard[C_J]++;
		if(*i=="Q") targetCard[C_Q]++;
		if(*i=="K") targetCard[C_K]++;
		if(*i=="A") targetCard[C_A]++;
		if(*i=="2") targetCard[C_2]++;
		if(*i=="joker") targetCard[C_joker]++;
		if(*i=="JOKER") targetCard[C_JOKER]++;
	}
}
void retransferCard(int *targetCard,vector<Card> &hand){
	for(int i=0;i<15;i++){
		for(int j=1;j<=targetCard[i];j++){
			if(i==14) hand.push_back("JOKER");
			if(i==13) hand.push_back("joker");
			if(i==12) hand.push_back("2");
			if(i==11) hand.push_back("A");
			if(i==10) hand.push_back("K");
			if(i==9) hand.push_back("Q");
			if(i==8) hand.push_back("J");
			if(i==7) hand.push_back("10");
			if(i==6) hand.push_back("9");
			if(i==5) hand.push_back("8");
			if(i==4) hand.push_back("7");
			if(i==3) hand.push_back("6");
			if(i==2) hand.push_back("5");
			if(i==1) hand.push_back("4");
			if(i==0) hand.push_back("3");
		}
	}
}
bool is_boom(int* card);
bool is_con1(int* card);
bool is_con2(int *card);
bool is_doub(int *card);
bool is_fwith1(int *card);
bool is_fwith2(int *card);
bool is_maxboom(int *card);
bool is_p1(int *card);
bool is_p2(int *card);
bool is_plane(int *card);
bool is_sig(int *card);
bool is_trip(int *card);
bool is_tri1(int *card);
bool is_tri2(int *card);
bool is_valid(int *card){
	return is_boom(card)||is_con1(card)||is_con2(card)
		||is_doub(card)||is_fwith1(card)||is_fwith2(card)
		||is_maxboom(card)||is_p1(card)||is_p2(card)
		||is_plane(card)||is_sig(card)||is_trip(card)
		||is_tri1(card)||is_tri2(card);
}
// ----------------------------------------------------------------------------

int main() {
    srand(0x5942B);

    DDZPlayer p1("Alice"), p2("Bob"), p3("Charlie");
    DDZGame g(&p1, &p2, &p3);
    g.run();

    return 0;
}


int main2() {
    string name;
    cout << "Please input your name:" << endl;
    getline(cin, name);

    srand(0x5942B);

    DDZPlayer p1("Alice"), p2("Bob");
    DDZHumanPlayer p3(name);
    DDZGame g(&p1, &p2, &p3);
    g.run();

    return 0;
}



bool Card::operator <(const Card &other) const {
    int a = -1, b = -1;
    for (int i = 0; i < N_CARD_VALUES; ++i) {
        if (*this == CARD_VALUES[i]) a = i;
        if (other == CARD_VALUES[i]) b = i;
    }
    return a < b;
}

bool Card::operator >(const Card &other) const {
    return other < *this;
}

DDZPlayer::DDZPlayer(string name): name(name) {
    // 玩家类的构造函数
    prePos = -1;
}

string DDZPlayer::getName() {
    return name;
}

bool DDZPlayer::legal(vector<Card> cards) {
    // 通过上家打出的牌prePlay和手牌hand判断cards作为打出牌是否合法
    // TODO：（第二题）请补全这个函数
    int handCard[15];
    int current[15];
    transferCard(hand,handCard);
    transferCard(cards,current);
    for(int i=0;i<15;i++){
    	if(current[i]>handCard[i]) return false;
    }
    if(!is_valid(current)) return false;
    
    
    return true;
}

void DDZPlayer::substractFromHand(vector<Card> cards) {
    // 这个函数从hand中删除cards。假设cards中的牌hand可以拿得出来（否则会出错）。
    sort(hand.begin(), hand.end(), greater<Card>());
    sort(cards.begin(), cards.end(), greater<Card>());
    vector<Card>::iterator i = hand.begin(), k = cards.begin();
    for (vector<Card>::iterator j = hand.begin(); j != hand.end(); ++j) {
        if (k == cards.end() || *k != *j) *(i++) = *j;
        else if (k != cards.end()) ++k;
    }
    hand.erase(i, hand.end());
}

void DDZPlayer::showHand() {
    // 输出玩家名和手牌。
    cout << name << " holds: ";
    for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

void DDZPlayer::draw(Card card) {
    // 将card加入手牌
    hand.push_back(card);
    sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::draw(vector<Card> cards) {
    // 将cards中的牌加入手牌
    hand.insert(hand.end(), cards.begin(), cards.end());
    sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::setPosition(int pos) {
    position = pos;
}

void DDZPlayer::observed(int pos, vector<Card> cards) {
    // 将上一个出牌的人和出了什么牌记录下来。
    // 如果你想记录更多的信息供你的策略使用，可以改动这个函数。
    // 例如，记录已经有哪些牌被打出（记牌器），以推测场上是否可能还存在炸弹。
    if (cards.size()!=0){
    
    prePos = pos;
    prePlay = cards;
}
}

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
void playforboom(int *card,int *last_card){ //询问炸弹 
	Node result=askfor_boom(card);
	if(result.canplay){
		for(int i=0;i<4;i++) {
			last_card[result.card1]++; 
		} 
	}
	else if(askfor_maxboom(card).canplay){
		last_card[C_JOKER]++;
		last_card[C_joker]++;
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
				last_card[result.card1]++;
			}
			else playforboom(card,last_card);
			break;
		case doub:
			result=askfor_doub(card);
			if(result.canplay){
				for(int i=0;i<2;i++) {
					last_card[result.card1]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case trip:
			result=askfor_trip(card);
			if(result.canplay){
				for(int i=0;i<3;i++) {
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
						last_card[result.card1]++;
					}
					last_card[result.append[0]]++;
				}
				else{
					last_card[result.append[0]]++;
					for(int i=0;i<3;i++) {
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
						last_card[result.card1]++;
					}
					for(int i=0;i<2;i++) {
						last_card[result.append[0]]++;
					}
				}
				else{
					for(int i=0;i<2;i++) {
						last_card[result.append[0]]++;
					}
					for(int i=0;i<3;i++) {
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
					last_card[result.append[i]]++;
				}
			}
			else playforboom(card,last_card);
			break;
		case con1:
			result=askfor_con1(card);
			if(result.canplay){
				for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)) {
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
					last_card[i]++;
				}
			}
			else playforboom(card,last_card);
			break;
		default: break; 
	}
}
vector<Card> DDZPlayer::play() {
    // 轮到你出牌，返回打出的牌。
    // TODO：（第一题）请完善这个函数
    // 如果你使用不同的数据结构进行处理，你可以现将hand变量转换为你使用的结构，
    // 处理过后再将打出的牌转换为vector<Card>，存入card变量。
    vector<Card> cards;
   	int lastCard[15]={0};
   	int card[15]={0};
   	int last_card[15]={0};
   	transferCard(hand,card);
   	
    if (prePos == position || prePos == -1) {
        // 出任意牌
        Node result=has_con2(card);
	if(result.canplay){
		for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
			card[i]-=2;
			last_card[i]+=2;
			
		}
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
	}
	result=has_con1(card);
	if(result.canplay){
		for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
			card[i]--;
			last_card[i]++;
			
		}
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
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
				 last_card[result.append[i]]++;
			}
			retransferCard(last_card,cards);
			substractFromHand(cards);
			return cards;
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
				last_card[result.append[i]]++;
			}
			retransferCard(last_card,cards);
			substractFromHand(cards);
			return cards;
		}
		for(int i=0;i<result.appendnum;i++) card[result.append[i]]++;
		result.appendnum=0;
		for(CardName i=result.card2;i>=result.card1;i=(CardName)(i-1)){
			card[i]--;
			last_card[i]+=3;
			
		}
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
	}
	//以上三种情况都不满足：
	CardName boom=C_JOKER;
	for(CardName i=C_3;i<=C_2;i=(CardName)(i+1)){
		if(card[i]>=1&&card[i]<4){
			int num=card[i];
			for(int j=0;j<num;j++) {
				last_card[i]++;
				card[i]--;
			}
			retransferCard(last_card,cards);
			substractFromHand(cards);
		return cards;
		}
		if(card[i]==4) boom=i;
	} 
	if(card[C_joker]==1&&card[C_JOKER]==0){
		card[C_joker]--;
		last_card[C_joker]++;
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
	} 
	if(card[C_JOKER]==1&&card[C_joker]==0){
		card[C_JOKER]--;
		last_card[C_JOKER]++;
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
	}
	if(boom!=C_JOKER){
		for(int i=0;i<4;i++){
			card[boom]--;
			last_card[boom]++;
		}
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
	}
	if(card[C_joker]==1&&card[C_JOKER]==1){
		card[C_joker]--;
		last_card[C_joker]++;
		card[C_JOKER]--;
		last_card[C_JOKER]++;
		retransferCard(last_card,cards);
		substractFromHand(cards);
		return cards;
	}
        
    } else {
        transferCard(prePlay,lastCard);
        CardType t=judgeType(lastCard);
        afterplay(card,t,last_card);
        retransferCard(last_card,cards);
        substractFromHand(cards);
        return cards;
    }

    // 你需要保证打出的牌是合法的
    // assert函数在参数为false的时候会使程序报错退出。
    // 这样做的好处是，如果你有没注意到的错误导致程序在此报错退出，
    // 你就知道是在出牌的合法性上出了问题，而不用排查程序的其他部分。
    // assert(legal(cards));

    // 将打出的牌从手牌中删去
    
    return cards;
}

bool DDZPlayer::leftNoCard() {
    // 返回当前手牌为空
    return hand.empty();
}

const int Card::N_CARD_VALUES = 15;

const int Card::N_CARD_SUITS = 4;

const string Card::CARD_VALUES[] = {
    "3", "4", "5", "6",
    "7", "8", "9", "10",
    "J", "Q", "K", "A", "2",
    "joker", "JOKER"
};

const string Card::CARD_SUITS[] = {
    "Spades", "Hearts", "Diamonds", "Clubs"
};

vector<Card> Card::get_new_deck() {
    // 生成一副新牌
    vector<Card> deck;
    for (int i = 0; i < N_CARD_VALUES-2; ++i) {
        for (int j = 0; j < N_CARD_SUITS; ++j) {
            Card card(CARD_VALUES[i]);
            deck.push_back(card);
        }
    }
    deck.push_back(Card(CARD_VALUES[13]));
    deck.push_back(Card(CARD_VALUES[14]));
    return deck;
}

int DDZGame::my_random (int i) {
    return std::rand()%i;
}

DDZGame::DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3) {
    // 牌局类的构造函数，需要接受三个玩家作为参数
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
}

void DDZGame::showCards(vector<Card> cards) {
    sort(cards.begin(), cards.end(), greater<Card>());
    for (vector<Card>::iterator i = cards.begin(); i != cards.end(); ++i) {
        cout << *i << " ";
    }
    if (cards.size() == 0) cout << "YAO BU QI";
    cout << endl << endl;
}

void DDZGame::run() {
    // 斗地主游戏的主要流程

    // 取一副新牌并洗牌
    vector<Card> deck = Card::get_new_deck();
    random_shuffle(deck.begin(), deck.end(), my_random);

    // 每个玩家抽17张牌，留下三张底牌
    for (int i = 0; i < 54-3; ++i)
        players[i%3]->draw(deck[i]);

    // 随机选取地主，发给地主最后三张牌
    // * 你可以实现自己的叫地主流程，
    // * 你需要在DDZPlayer类里面加入相应的变量（存储其他玩家叫地主的情况）
    // * 和函数bool DDZPlayer::bid()（返回自己是否要叫地主）。
    // * 请参阅play()函数和叫地主的规则设计这个流程。
    int landlordPos = my_random(3);
    for (int i = 54-3; i < 54; ++i)
        players[landlordPos]->draw(deck[i]);
    for (int i = 0; i < 3; ++i)
        players[i]->setPosition((i + 3 - landlordPos) % 3); // 计算与地主的相对位置
    cout << players[landlordPos]->getName() << " is the landlord." << endl;


    int currentPlayer = landlordPos;
    while (true) {
        // 当前玩家打牌
        vector<Card> currentCards = players[currentPlayer]->play();
        cout << players[currentPlayer]->getName() << " plays:";
        showCards(currentCards);
        // 其他玩家看到了打出的牌。（并不是只有下家看到，上家也能看到）
        for (int i = 0; i < 3; ++i) {
            // 玩家看到的位置编号都是从地主为0开始的
            int relativePos = (currentPlayer + 3 - landlordPos) % 3;
            players[i]->observed(relativePos, currentCards);
        }
        
        // 如果刚出完牌的玩家没有牌了游戏结束
        if (players[currentPlayer]->leftNoCard()) {
            bool landlordwins = (currentPlayer == landlordPos);
            cout << (landlordwins ? "Landlord wins!" : "Farmers win!") << endl;
            break;
        }

        // 计算下一个玩家的下标
        currentPlayer = (currentPlayer + 1) % 3;
    }
}

vector<Card> DDZHumanPlayer::play() {
    vector<Card> cards;
    string s, c;
    while (true) {
        showHand();
        cout << "Please input the cards you want to play." << endl;
        getline(cin, s);
        istringstream iss(s);
        while (iss >> c) {
            cards.push_back(Card(c));
        }
        // 现在cards是一个vector<Card>，存储了用户输入的牌
        // 你需要检测输入的牌是持有的牌，并且合法。请完成legal函数。
        if (legal(cards)) {
            break;
        } else {
            cout << "Illegal cards. Input again." << endl;
        }
    }
    substractFromHand(cards);
    return cards;
}
