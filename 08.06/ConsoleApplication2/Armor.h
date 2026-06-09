#pragma once
#include "Item.h"

// броня — наследует Item, добавляет защиту~~
class Armor : public Item {
private:
    int defenseBonus;  // бонус к защите

public:
    Armor(const std::string& name, const std::string& description, int defenseBonus);

    int getDefenseBonus() const;

    std::string getFullInfo() const override;
};
