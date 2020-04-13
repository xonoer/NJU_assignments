// Please use UTF-8 encoding so that the comments can be displayed correctly.
// ��עTODO��������Ҫ���Ƶĵط�
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

    // ���ز�������ʹ��������ԱȽϴ�С
    bool operator <(const Card &other) const;
    bool operator >(const Card &other) const;
};


class DDZPlayer {
protected:
    string name;  // �����
    int position;  // ���λ�ñ�ţ�0Ϊ������1Ϊ�����¼ң�2Ϊ�����ϼ�
    vector<Card> hand;  // ����

    int prePos;  //��һ�����Ƶ���λ�ñ�ţ�-1��ʾ��û���˳�����
    vector<Card> prePlay;  // ��һ�����Ƶ��˳���ʲô�ƣ�

    bool legal(vector<Card> cards);  // �жϵ�ǰ���cards�Ƿ�Ϸ�
    void substractFromHand(vector<Card> cards);  // �ӵ�ǰ������ɾȥcards�е���
public:
    DDZPlayer(string name);  // ���캯������ʼ�������
    string getName();
    virtual void draw(Card card);  // ��cards�е��Ƽ�������
    virtual void draw(vector<Card> cards);  // ��cards�е��Ƽ�������
    virtual void setPosition(int pos);  // ��ʼ���ã���������������
    virtual void showHand();  // ��ӡ����
    virtual void observed(int pos, vector<Card> cards);  // �۲⵽��ҳ���
    virtual vector<Card> play();  // �ֵ��Լ�ʱ������ʲô��
    bool leftNoCard();  // �����Ƿ�������ƣ�
};


class DDZGame {
private:
    static int my_random (int i);  // ϴ��ʱ�õ����������
    vector<DDZPlayer*> players;  // ����������ҵ�ָ��
    void showCards(vector<Card> cards);  // ���һ����

public:
    DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  // ���캯��
    void run();  // ִ����Ϸ����
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
    // �����Ĺ��캯��
    prePos = -1;
}

string DDZPlayer::getName() {
    return name;
}

bool DDZPlayer::legal(vector<Card> cards) {
    // ͨ���ϼҴ������prePlay������hand�ж�cards��Ϊ������Ƿ�Ϸ�
    // TODO�����ڶ��⣩�벹ȫ�������
    return true;
}

void DDZPlayer::substractFromHand(vector<Card> cards) {
    // ���������hand��ɾ��cards������cards�е���hand�����õó���������������
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
    // �������������ơ�
    cout << name << " holds: ";
    for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

void DDZPlayer::draw(Card card) {
    // ��card��������
    hand.push_back(card);
    sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::draw(vector<Card> cards) {
    // ��cards�е��Ƽ�������
    hand.insert(hand.end(), cards.begin(), cards.end());
    sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::setPosition(int pos) {
    position = pos;
}

void DDZPlayer::observed(int pos, vector<Card> cards) {
    // ����һ�����Ƶ��˺ͳ���ʲô�Ƽ�¼������
    // ��������¼�������Ϣ����Ĳ���ʹ�ã����ԸĶ����������
    // ���磬��¼�Ѿ�����Щ�Ʊ�������������������Ʋⳡ���Ƿ���ܻ�����ը����
    prePos = pos;
    prePlay = cards;
}

vector<Card> DDZPlayer::play() {
    // �ֵ�����ƣ����ش�����ơ�
    // TODO������һ�⣩�������������
    // �����ʹ�ò�ͬ�����ݽṹ���д���������ֽ�hand����ת��Ϊ��ʹ�õĽṹ��
    // ��������ٽ��������ת��Ϊvector<Card>������card������
    vector<Card> cards;
    if (prePos == position || prePos == -1) {
        // ��������
        
    } else {
        // λ��prePos����Ҵ����prePlay���ƣ�����Ҫ��ʲô�ƣ�
    }

    // ����Ҫ��֤��������ǺϷ���
    // assert�����ڲ���Ϊfalse��ʱ���ʹ���򱨴��˳���
    // �������ĺô��ǣ��������ûע�⵽�Ĵ����³����ڴ˱����˳���
    // ���֪�����ڳ��ƵĺϷ����ϳ������⣬�������Ų������������֡�
    // assert(legal(cards));

    // ��������ƴ�������ɾȥ
    substractFromHand(cards);
    return cards;
}

bool DDZPlayer::leftNoCard() {
    // ���ص�ǰ����Ϊ��
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
    // ����һ������
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
    // �ƾ���Ĺ��캯������Ҫ�������������Ϊ����
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
    // ��������Ϸ����Ҫ����

    // ȡһ�����Ʋ�ϴ��
    vector<Card> deck = Card::get_new_deck();
    random_shuffle(deck.begin(), deck.end(), my_random);

    // ÿ����ҳ�17���ƣ��������ŵ���
    for (int i = 0; i < 54-3; ++i)
        players[i%3]->draw(deck[i]);

    // ���ѡȡ�����������������������
    // * �����ʵ���Լ��Ľе������̣�
    // * ����Ҫ��DDZPlayer�����������Ӧ�ı������洢������ҽе����������
    // * �ͺ���bool DDZPlayer::bid()�������Լ��Ƿ�Ҫ�е�������
    // * �����play()�����ͽе����Ĺ������������̡�
    int landlordPos = my_random(3);
    for (int i = 54-3; i < 54; ++i)
        players[landlordPos]->draw(deck[i]);
    for (int i = 0; i < 3; ++i)
        players[i]->setPosition((i + 3 - landlordPos) % 3); // ��������������λ��
    cout << players[landlordPos]->getName() << " is the landlord." << endl;


    int currentPlayer = landlordPos;
    while (true) {
        // ��ǰ��Ҵ���
        vector<Card> currentCards = players[currentPlayer]->play();
        cout << players[currentPlayer]->getName() << " plays:";
        showCards(currentCards);
        // ������ҿ����˴�����ơ���������ֻ���¼ҿ������ϼ�Ҳ�ܿ�����
        for (int i = 0; i < 3; ++i) {
            // ��ҿ�����λ�ñ�Ŷ��Ǵӵ���Ϊ0��ʼ��
            int relativePos = (currentPlayer + 3 - landlordPos) % 3;
            players[i]->observed(relativePos, currentCards);
        }
        
        // ����ճ����Ƶ����û��������Ϸ����
        if (players[currentPlayer]->leftNoCard()) {
            bool landlordwins = (currentPlayer == landlordPos);
            cout << (landlordwins ? "Landlord wins!" : "Farmers win!") << endl;
            break;
        }

        // ������һ����ҵ��±�
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
        // ����cards��һ��vector<Card>���洢���û��������
        // ����Ҫ�����������ǳ��е��ƣ����ҺϷ��������legal������
        if (legal(cards)) {
            break;
        } else {
            cout << "Illegal cards. Input again." << endl;
        }
    }
    substractFromHand(cards);
    return cards;
}
