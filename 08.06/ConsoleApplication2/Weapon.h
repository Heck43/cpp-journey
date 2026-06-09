#pragma once
#include "Item.h"

// оружие — наследует Item, добавляет урон~~
class Weapon : public Item {
private:
    int attackBonus;  // бонус к атаке

public:
    Weapon(const std::string& name, const std::string& description, int attackBonus);

    int getAttackBonus() const;

    // переопределяем метод из базового класса
    std::string getFullInfo() const override;
};
