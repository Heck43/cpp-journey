#pragma once
#include "Item.h"

// зелье — восстанавливает hp игрока~~
class Potion : public Item {
private:
    int healAmount;   // сколько хп восстанавливает
    bool used;        // было ли уже использовано

public:
    Potion(const std::string& name, const std::string& description, int healAmount);

    int getHealAmount() const;
    bool isUsed() const;

    // помечаем зелье как использованное
    void use();

    std::string getFullInfo() const override;
};
