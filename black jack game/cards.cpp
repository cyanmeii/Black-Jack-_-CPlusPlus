#include "cards.h"
#include <random>
#include <utility>

static int cardPoints(Rank rank) {

    if (rank == Ace) {
        return 11;
    }

    if (rank >= Jack) {
        return 10;
    }

    return static_cast<int>(rank);
}

Card makeCard(Suit suit, Rank rank) {

    Card c;

    c.suit = suit;
    c.rank = rank;

    c.points = cardPoints(rank);

    return c;
}

void initDeck(Deck& deck) {

    int i = 0;

    for (int s = Spades; s <= Hearts; ++s) {

        for (int r = Six; r <= Ace; ++r) {

            deck.cards[i++] = makeCard(static_cast<Suit>(s), static_cast<Rank>(r));
        }
    }

    deck.top = 0;
}

void shuffleDeck(Deck& deck) {

    static std::mt19937 gen{std::random_device{}()};

    for (int i = DeckSize - 1; i > 0; --i) {

        std::uniform_int_distribution<int> dist(0, i);

        std::swap(deck.cards[i], deck.cards[dist(gen)]);
    }

    deck.top = 0;
}

Card dealCard(Deck& deck) {

    return deck.cards[deck.top++];
}
