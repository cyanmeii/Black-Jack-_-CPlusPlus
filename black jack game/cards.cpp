#include "cards.h"
#include <random>
#include <utility>

/// <summary>
/// Логика подсчета очков для карт такова:
/// туз (Ace) оценивается в 11 очков,
/// карты от валета (Jack) до короля (King) оцениваются в 10 очков,
/// а остальные карты оцениваются по их номиналу.
/// </summary>
/// <param name="rank">Ранг карты</param>
/// <returns>Количество очков для карты</returns>
static int cardPoints(Rank rank) {

    if (rank == Ace) {
        return 11;
    }

    if (rank >= Jack) {
        return 10;
    }

    return static_cast<int>(rank);
}

/// <summary>
/// Создает карту с заданным мастью и рангом.
/// </summary>
/// <param name="suit">Масть карты</param>
/// <param name="rank">Ранг карты</param>
/// <returns>Карта с заданными характеристиками</returns>
Card makeCard(Suit suit, Rank rank) {

    Card c;

    c.suit = suit;
    c.rank = rank;

    c.points = cardPoints(rank);

    return c;
}

/// <summary>
/// Инициализирует колоду карт.
/// </summary>
/// <param name="deck">Колода карт</param>
void initDeck(Deck& deck) {

    int i = 0;

    for (int s = Spades; s <= Hearts; ++s) {

        for (int r = Six; r <= Ace; ++r) {

            deck.cards[i++] = makeCard(static_cast<Suit>(s), static_cast<Rank>(r));
        }
    }

    deck.top = 0;
}

/// <summary>
/// Перемешивает карты в колоде.
/// </summary>
/// <param name="deck">Колода карт</param>
void shuffleDeck(Deck& deck) {

    static std::mt19937 gen{std::random_device{}()};

    for (int i = DeckSize - 1; i > 0; --i) {

        std::uniform_int_distribution<int> dist(0, i);

        std::swap(deck.cards[i], deck.cards[dist(gen)]);
    }

    deck.top = 0;
}

/// <summary>
/// Раздает карту из колоды.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <returns>Разданная карта</returns>
Card dealCard(Deck& deck) {

	if (deck.top >= DeckSize) {
		throw std::out_of_range("No more cards in the deck");
	}

    return deck.cards[deck.top++];
}
