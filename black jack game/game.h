#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "cards.h"

/// <summary>
/// Максимальный счет.
/// </summary>
extern const int MaxScore;

/// <summary>
/// Лимит дилера.
/// </summary>
extern const int DealerLimit;

/// <summary>
/// Максимальное количество карт в руке.
/// </summary>
const int MaxHand = 12;

/// <summary>
/// Структура игрока.
/// </summary>
struct Player {
    std::string name;
    Card hand[MaxHand];
    int cardsCount;
    int score;
};

/// <summary>
/// Проверяет, Bust ли у игрока.
/// </summary>
/// <param name="p">Игрок</param>
/// <returns></returns>
inline bool isBust(const Player& p) { 
    return p.score > MaxScore; 
}

/// <summary>
/// Проверяет, должен ли дилер брать карту.
/// </summary>
/// <param name="p">Игрок</param>
/// <returns></returns>
inline bool dealerMustHit(const Player& p) {
    return p.score < DealerLimit;
}

/// <summary>
/// Проверяет, является ли рука натуральным 21.
/// </summary>
/// <param name="p">Игрок</param>
/// <returns></returns>
inline bool isNatural(const Player& p) {
    return p.cardsCount == 2 && p.score == MaxScore; 
}

/// <summary>
/// Тип функции действия.
/// </summary>
typedef bool (*ActionFn)(Deck&, Player*);

/// <summary>
/// Инициализирует игрока.
/// </summary>
/// <param name="p">Игрок</param>
/// <param name="name">Имя игрока</param>
void initPlayer(Player* p, const std::string& name);

/// <summary>
/// Добавляет карту к руке игрока.
/// </summary>
/// <param name="p">Игрок</param>
/// <param name="c">Карта</param>
void addCard(Player* p, Card c);

/// <summary>
/// Выполняет действие "взять карту" для игрока.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="player">Игрок</param>
/// <returns></returns>
bool hitAction(Deck& deck, Player* player);

/// <summary>
/// Выполняет действие "остановиться" для игрока.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="player">Игрок</param>
/// <returns></returns>
bool standAction(Deck& deck, Player* player);

/// <summary>
/// Выполняет ход дилера.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="dealer">Дилер</param>
void dealerTurn(Deck& deck, Player* dealer);

/// <summary>
/// Отображает карту.
/// </summary>
/// <param name="card">Карта</param>
void show(const Card& card);

/// <summary>
/// Отображает игрока.
/// </summary>
/// <param name="player">Игрок</param>
void show(const Player& player);

/// <summary>
/// Отображает игрока с возможностью скрыть вторую карту.
/// </summary>
/// <param name="player">Игрок</param>
/// <param name="hideSecond">Флаг скрытия второй карты</param>
void show(const Player& player, bool hideSecond);

/// <summary>
/// Печатает результат раунда.
/// </summary>
/// <param name="player">Игрок</param>
/// <param name="dealer">Дилер</param>
void printRoundResult(const Player& player, const Player& dealer);

/// <summary>
/// Выполняет раунд игры.
/// </summary>
/// <param name="deck">Колода карт</param>
/// <param name="player">Игрок</param>
/// <param name="dealer">Дилер</param>
void playRound(Deck& deck, Player* player, Player* dealer);

#endif