#ifndef GAME_H_
#define GAME_H_
#include <string>
#include "cards.h"

extern const int MaxScore;
extern const int DealerLimit;

const int MaxHand = 12;

struct Player {
    std::string name;
    Card hand[MaxHand];
    int cardsCount;
    int score;
};

inline bool isBust(const Player& p) { 
    return p.score > MaxScore; 
}

inline bool dealerMustHit(const Player& p) {
    return p.score < DealerLimit;
}

inline bool isNatural(const Player& p) {
    return p.cardsCount == 2 && p.score == MaxScore; 
}

typedef bool (*ActionFn)(Deck&, Player*);

void initPlayer(Player* p, const std::string& name);

void addCard(Player* p, Card c);

bool hitAction(Deck& deck, Player* player);

bool standAction(Deck& deck, Player* player);

void dealerTurn(Deck& deck, Player* dealer);

void show(const Card& card);

void show(const Player& player);

void show(const Player& player, bool hideSecond);

void printRoundResult(const Player& player, const Player& dealer);

void playRound(Deck& deck, Player* player, Player* dealer);

#endif