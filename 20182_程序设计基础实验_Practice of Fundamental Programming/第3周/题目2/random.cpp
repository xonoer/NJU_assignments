#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

const bool USE_SUITS = false;

const int N_CARD_VALUES = 15;
const string CARD_VALUES[] = {
    "3", "4", "5", "6",
    "7", "8", "9", "10",
    "J", "Q", "K", "A", "2",
    "joker", "JOKER"
};
const int N_CARD_SUITS = 4;
const string CARD_SUITS[] = {
    "Spade", "Heart", "Diamond", "Club"
};

int my_random (int i) {
    return std::rand()%i;
}

vector<string> get_new_deck() {
    vector<string> deck;
    for (int i = 0; i < N_CARD_VALUES-2; ++i) {
        for (int j = 0; j < N_CARD_SUITS; ++j) {
            string card = CARD_VALUES[i];
            if (USE_SUITS) card = CARD_SUITS[j] + "_" + card;
            deck.push_back(card);
        }
    }
    deck.push_back(CARD_VALUES[13]);
    deck.push_back(CARD_VALUES[14]);
    return deck;
}

int main(int argc, char* argv[]) {
	freopen("test.txt","w",stdout);
    unsigned int random_seed;
    cin >> random_seed;
    srand(random_seed);
    
    vector<string> deck = get_new_deck();
    random_shuffle(deck.begin(), deck.end(), my_random);

    for (int i = 0; i < deck.size(); ++i) {
        cout << deck[i] << ((i == 19 || i == 36 || i == 53) ? "\n" : " ");
    }

    return 0;
}
