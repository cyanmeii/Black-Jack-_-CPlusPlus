#ifndef CARDS_H_
#define CARDS_H_

enum Suit {
    Spades,
    Clubs,
    Diamonds,
    Hearts
};

enum Rank {
    Six = 6,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

const int DeckSize = 36;

struct Card {
    Suit suit;
    Rank rank;
    int points;
};

struct Deck {
    Card cards[DeckSize];
    int top;
};

Card makeCard(Suit suit, Rank rank);

void initDeck(Deck& deck);

void shuffleDeck(Deck& deck);

Card dealCard(Deck& deck);

#endif