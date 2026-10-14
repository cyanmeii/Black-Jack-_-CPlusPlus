#include "game.h"

#include <iostream>

/// <summary>
/// Логика игры следующая: игроку раздаются две карты,
/// дилеру раздаются две карты (одна из которых скрыта).
/// Игрок может выбрать "Hit" (взять еще карту) или "Stand" (остановиться).
/// Если сумма очков игрока превышает 21, он проигрывает.
/// После того как игрок завершает свой ход,
/// дилер открывает свою скрытую карту и берет карты до тех пор,
/// пока его сумма очков не достигнет 17 или выше.
/// Побеждает тот, у кого сумма очков ближе к 21, не превышая его. 
/// </summary>

extern const int MaxScore = 21;
extern const int DealerLimit = 17;

/// <summary>
/// Возвращает название ранга карты.
/// </summary>
/// <param name="r">Ранг карты</param>
/// <returns>Название ранга карты</returns>
static const char* rankName(Rank r) {

    switch (r) {

        case Jack:  return "J";
        case Queen: return "Q";
        case King:  return "K";
        case Ace:   return "A";
        case Ten:   return "10";
        case Nine:  return "9";
        case Eight: return "8";
        case Seven: return "7";
        default:    return "6";
    }
}

/// <summary>
/// Возвращает название масти карты.
/// </summary>
/// <param name="s">Масть карты</param>
/// <returns>Название масти карты</returns>
static const char* suitName(Suit s) {

    switch (s) {

        case Spades:   return "Spades";
        case Clubs:    return "Clubs";
        case Diamonds: return "Diamonds";
        default:       return "Hearts";
    }
}

/// <summary>
/// Выводит информацию о карте.
/// </summary>
/// <param name="card">Карта</param>
void show(const Card& card) {

    std::cout << "[" << rankName(card.rank) << " of " << suitName(card.suit) << "]";
}

/// <summary>
/// Выводит информацию о игроке.
/// </summary>
/// <param name="player">Игрок</param>
void show(const Player& player) {

    std::cout << player.name << ": ";

    for (int i = 0; i < player.cardsCount; ++i) {
        show(player.hand[i]);
        std::cout << ' ';
    }

    std::cout << "(score: " << player.score << ")\n";
}

/// <summary>
/// Выводит информацию о игроке, скрывая вторую карту при необходимости.
/// </summary>
/// <param name="player">Игрок</param>
/// <param name="hideSecond">Флаг, указывающий на необходимость скрытия второй карты</param>
void show(const Player& player, bool hideSecond) {

    if (!hideSecond) {
        show(player);
        return;
    }

    std::cout << player.name << ": ";

    show(player.hand[0]);

    std::cout << " [hidden]\n";
}

/// <summary>
/// Инициализирует игрока.
/// </summary>
/// <param name="p">Игрок</param>
/// <param name="name">Имя игрока</param>
void initPlayer(Player* p, const std::string& name) {

    p->name = name;
    p->cardsCount = 0;
    p->score = 0;
}

/// <summary>
/// Добавляет карту к руке игрока.
/// </summary>
/// <param name="p">Игрок</param>
/// <param name="c">Карта</param>
void addCard(Player* p, Card c) {

    if (p->cardsCount < MaxHand) {

        p->hand[p->cardsCount++] = c;
        p->score += c.points;
    }
}

/// <summary>
/// Выполняет действие "взять карту" для игрока.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="player">Игрок</param>
/// <returns></returns>
bool hitAction(Deck& deck, Player* player) {

    Card c = dealCard(deck);
    addCard(player, c);

    std::cout << player->name << " takes ";
    show(c);

    std::cout << "\n";
    show(*player);

    return true;
}

/// <summary>
/// Выполняет действие "остаться" для игрока.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="player">Игрок</param>
/// <returns></returns>
bool standAction(Deck&, Player* player) {

    std::cout << player->name << " stands.\n";

    return false;
}

/// <summary>
/// Выполняет ход дилера.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="dealer">Дилер</param>
void dealerTurn(Deck& deck, Player* dealer) {

    if (!dealerMustHit(*dealer)) {
        return;
    }

    Card c = dealCard(deck);

    addCard(dealer, c);

    std::cout << dealer->name << " takes ";
    show(c);

    std::cout << "\n";
    dealerTurn(deck, dealer);
}

/// <summary>
/// Выводит результат раунда.
/// </summary>
/// <param name="player">Игрок</param>
/// <param name="dealer">Дилер</param>
void printRoundResult(const Player& player, const Player& dealer) {

    static int roundsPlayed = 0;
    ++roundsPlayed;

    std::cout << "\n♣︎ Round " << roundsPlayed << " result ♣︎\n";

    show(player);
    show(dealer);

    if (isBust(player)) {

        std::cout << "Bust! Dealer wins.\n";
    }
    else if (isBust(dealer)) {

        std::cout << "Dealer busts! You win!\n";
    }
    else if (player.score > dealer.score) {

        std::cout << "You win!\n";
    }
    else if (player.score < dealer.score) {

        std::cout << "Dealer wins.\n";
    } 
    else {

        std::cout << "Push (draw).\n";
    }
}

/// <summary>
/// Проигрывает один раунд игры.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="player">Игрок</param>
/// <param name="dealer">Дилер</param>
void playRound(Deck& deck, Player* player, Player* dealer) {

    initDeck(deck);
    shuffleDeck(deck);

    initPlayer(player, player->name);
    initPlayer(dealer, dealer->name);

    for (int i = 0; i < 2; ++i) {

        addCard(player, dealCard(deck));
        addCard(dealer, dealCard(deck));
    }

    std::cout << "\nNew round ✰\n";

    show(*dealer, true);
    show(*player);

    ActionFn actions[2] = { hitAction, standAction };

    if (isNatural(*player)) {

        std::cout << "Natural 21!\n";
    } 
    else {

        while (!isBust(*player)) {

            std::cout << "1 - Hit, 2 - Stand: ";
            std::string line;

            if (!std::getline(std::cin, line)) {

                line = "2";
            }

            if (line != "1" && line != "2") {

                std::cout << "Please enter 1 or 2.\n";
                continue;
            }

            int index = line[0] - '1';

            if (!actions[index](deck, player)) {
                break;
            }
        }
    }

    if (!isBust(*player)) {

        std::cout << "\nDealer's turn. ";

        show(*dealer);
        dealerTurn(deck, dealer);
    }

    printRoundResult(*player, *dealer);
}
