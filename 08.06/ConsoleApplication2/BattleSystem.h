#pragma once
#include "Player.h"
#include "Enemy.h"

// класс управляет всем боем — один бой между игроком и врагом~~
class BattleSystem {
private:
    Player& player;
    Enemy&  enemy;
    int     turnNumber;

    // вспомогательные методы
    void printSeparator() const;
    void printBattleStatus() const;

    // ход игрока — возвращает true если ход был совершён успешно
    bool playerTurn();

    // ход врага
    void enemyTurn();

    // проверка исходов
    bool checkVictory() const;
    bool checkDefeat() const;

public:
    BattleSystem(Player& player, Enemy& enemy);

    // запустить бой — возвращает true если игрок победил
    bool startBattle();
};
