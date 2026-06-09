#pragma once
#include "Character.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include <vector>
#include <memory>   // для умных указателей

// класс игрока — наследует Character, добавляет инвентарь~~
class Player : public Character {
private:
    Weapon* equippedWeapon;   // экипированное оружие (может быть nullptr)
    Armor*  equippedArmor;    // экипированная броня  (может быть nullptr)
    std::vector<Potion*> potions;  // зелья в инвентаре

public:
    Player(const std::string& name, int maxHp, int baseAttack, int baseDefense);
    ~Player();

    // экипировка
    void equipWeapon(Weapon* weapon);
    void equipArmor(Armor* armor);
    void addPotion(Potion* potion);

    // использовать i-е зелье из инвентаря (счёт с 0)
    bool usePotion(int index);

    // переопределяем силу атаки и защиты с учётом снаряжения
    int getAttackPower() const override;
    int getDefenseValue() const override;

    // вывод всего снаряжения
    void printInventory() const;

    void printStatus() const override;

    // сколько зелий осталось
    int getPotionCount() const;
};
