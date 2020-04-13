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
    prePos = pos;
    prePlay = cards;
}

vector<Card> DDZPlayer::play() {
    // 轮到你出牌，返回打出的牌。
    // TODO：（第一题）请完善这个函数
    // 如果你使用不同的数据结构进行处理，你可以现将hand变量转换为你使用的结构，
    // 处理过后再将打出的牌转换为vector<Card>，存入card变量。
    vector<Card> cards;
    if (prePos == position || prePos == -1) {
        // 出任意牌
        
    } else {
        // 位于prePos的玩家打出了prePlay的牌，你需要出什么牌？
    }

    // 你需要保证打出的牌是合法的
    // assert函数在参数为false的时候会使程序报错退出。
    // 这样做的好处是，如果你有没注意到的错误导致程序在此报错退出，
    // 你就知道是在出牌的合法性上出了问题，而不用排查程序的其他部分。
    // assert(legal(cards));

    // 将打出的牌从手牌中删去
    substractFromHand(cards);
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
