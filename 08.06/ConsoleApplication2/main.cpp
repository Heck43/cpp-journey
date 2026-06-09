#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "BattleSystem.h"
#include <locale.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // === Создание игрока с базовыми характеристиками ===
    Player player("Герой", 100, 10, 3);

    // === Экипируем оружие и броню, добавляем зелья ===
    // new — создаём на куче, Player сам удалит в деструкторе
    player.equipWeapon(new Weapon("Длинный меч", "Острый клинок из стали", 15));
    player.equipArmor (new Armor ("Кожаный доспех", "Лёгкая, но прочная броня",  5));
    player.addPotion  (new Potion("Малое зелье лечения", "Восстанавливает 30 HP", 30));
    player.addPotion  (new Potion("Большое зелье лечения","Восстанавливает 60 HP", 60));

    std::cout << "\nДобро пожаловать в мир RPG!\n";
    player.printInventory();

    // === Создание противника ===
    Enemy goblin("Гоблин-воин", "Гоблин", 60, 12, 2);

    // === Запускаем бой ===
    BattleSystem battle(player, goblin);
    bool playerWon = battle.startBattle();

    std::cout << "\nНажмите Enter для выхода...\n";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
