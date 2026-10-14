#include <iostream>
#include <string>
#include "game.h"


int main() {

    Deck deck;
    Player player;
    Player dealer;

    initPlayer(&player, "Player");
    initPlayer(&dealer, "Dealer");

    std::cout << "Blackjack ❤︎ ♦︎ ♠︎ ♣︎\n";

    std::string answer;

    do {

        playRound(deck, &player, &dealer);

        std::cout << "\nPlay again? (y/n): ";

        if (!std::getline(std::cin, answer)) {
            break;
        }

    } 
    while (answer == "y" || answer == "Y");

    std::cout << "Thanks for playing!\n";

    return 0;
}
