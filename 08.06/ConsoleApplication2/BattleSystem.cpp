#include "BattleSystem.h"
#include <iostream>
#include <limits>

BattleSystem::BattleSystem(Player& player, Enemy& enemy)
    : player(player), enemy(enemy), turnNumber(1) {}

void BattleSystem::printSeparator() const {
    std::cout << "----------------------------------------\n";
}

void BattleSystem::printBattleStatus() const {
    std::cout << "\n=== ХОД " << turnNumber << " ===\n";
    player.printStatus();
    enemy.printStatus();
    printSeparator();
}

// ход игрока: выбор действия через меню~~
bool BattleSystem::playerTurn() {
    std::cout << "\nВаш ход! Выберите действие:\n";
    std::cout << "  1. Атаковать " << enemy.getName() << "\n";
    std::cout << "  2. Использовать зелье";
    if (player.getPotionCount() > 0)
        std::cout << " (доступно: " << player.getPotionCount() << ")\n";
    else
        std::cout << " [НЕТ ЗЕЛИЙ]\n";
    std::cout << "  3. Осмотреть снаряжение\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;

    // защита от некорректного ввода
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод! Попробуйте снова.\n";
        return false;  // ход не засчитывается — просим снова
    }

    if (choice == 1) {
        // атака врага
        std::cout << "\n" << player.getName() << " атакует "
                  << enemy.getName() << "! (сила: " << player.getAttackPower() << ")\n";
        enemy.takeDamage(player.getAttackPower());
        return true;

    } else if (choice == 2) {
        // использование зелья
        if (player.getPotionCount() == 0) {
            std::cout << "Зелий нет! Выберите другое действие.\n";
            return false;
        }
        std::cout << "\nВведите номер зелья (1, 2, ...): ";
        int potionIndex;
        std::cin >> potionIndex;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        bool ok = player.usePotion(potionIndex - 1);  // переводим в 0-индекс
        return ok;

    } else if (choice == 3) {
        // просмотр снаряжения — ход не тратится
        player.printInventory();
        return false;

    } else {
        std::cout << "Нет такого варианта! Выберите 1, 2 или 3.\n";
        return false;
    }
}

// враг всегда просто атакует игрока~~
void BattleSystem::enemyTurn() {
    std::cout << "\n" << enemy.getName() << " атакует "
              << player.getName() << "! (сила: " << enemy.getAttackPower() << ")\n";
    player.takeDamage(enemy.getAttackPower());
}

bool BattleSystem::checkVictory() const {
    return !enemy.isAlive();
}

bool BattleSystem::checkDefeat() const {
    return !player.isAlive();
}

// главный цикл боя~~
bool BattleSystem::startBattle() {
    std::cout << "\n";
    printSeparator();
    std::cout << "!!! ВСТРЕЧА С ПРОТИВНИКОМ !!!\n";
    std::cout << "Вы столкнулись с " << enemy.getName()
              << " (" << enemy.getType() << ")!\n";
    printSeparator();

    while (player.isAlive() && enemy.isAlive()) {
        printBattleStatus();

        // ход игрока — цикл пока не будет совершён валидный ход
        bool turnDone = false;
        while (!turnDone) {
            turnDone = playerTurn();
        }

        // проверяем победу сразу после удара
        if (checkVictory()) break;

        // ход врага
        enemyTurn();

        // проверяем поражение
        if (checkDefeat()) break;

        turnNumber++;
    }

    printSeparator();

    if (checkVictory()) {
        // ==== ПОБЕДА ====
        std::cout << "\n*** ПОБЕДА! ***\n";
        std::cout << enemy.getName() << " повержен!\n";
        std::cout << "Вы выжили с " << player.getCurrentHp()
                  << " HP. Поздравляем, герой!\n";
        return true;
    } else {
        // ==== ПОРАЖЕНИЕ ====
        std::cout << "\n*** ПОРАЖЕНИЕ... ***\n";
        std::cout << player.getName() << " пал в бою...\n";
        std::cout << "Игра окончена. Попробуйте ещё раз!\n";
        return false;
    }
}
