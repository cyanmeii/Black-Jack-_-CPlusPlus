#include "game.h"

#include <iostream>

extern const int MaxScore = 21;
extern const int DealerLimit = 17;

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

static const char* suitName(Suit s) {

    switch (s) {

        case Spades:   return "Spades";
        case Clubs:    return "Clubs";
        case Diamonds: return "Diamonds";
        default:       return "Hearts";
    }
}

void show(const Card& card) {

    std::cout << "[" << rankName(card.rank) << " of " << suitName(card.suit) << "]";
}

void show(const Player& player) {

    std::cout << player.name << ": ";

    for (int i = 0; i < player.cardsCount; ++i) {
        show(player.hand[i]);
        std::cout << ' ';
    }

    std::cout << "(score: " << player.score << ")\n";
}

void show(const Player& player, bool hideSecond) {

    if (!hideSecond) {
        show(player);
        return;
    }

    std::cout << player.name << ": ";

    show(player.hand[0]);

    std::cout << " [hidden]\n";
}

void initPlayer(Player* p, const std::string& name) {

    p->name = name;
    p->cardsCount = 0;
    p->score = 0;
}

void addCard(Player* p, Card c) {

    if (p->cardsCount < MaxHand) {

        p->hand[p->cardsCount++] = c;
        p->score += c.points;
    }
}

bool hitAction(Deck& deck, Player* player) {

    Card c = dealCard(deck);
    addCard(player, c);

    std::cout << player->name << " takes ";
    show(c);

    std::cout << "\n";
    show(*player);

    return true;
}
bool standAction(Deck&, Player* player) {

    std::cout << player->name << " stands.\n";

    return false;
}

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

void printRoundResult(const Player& player, const Player& dealer) {

    static int roundsPlayed = 0;
    ++roundsPlayed;

    std::cout << "\nRound " << roundsPlayed << " result\n";

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

void playRound(Deck& deck, Player* player, Player* dealer) {

    initDeck(deck);
    shuffleDeck(deck);

    initPlayer(player, player->name);
    initPlayer(dealer, dealer->name);

    for (int i = 0; i < 2; ++i) {

        addCard(player, dealCard(deck));
        addCard(dealer, dealCard(deck));
    }

    std::cout << "\nNew round\n";

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
