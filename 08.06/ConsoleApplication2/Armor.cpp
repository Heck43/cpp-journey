#include "Armor.h"

Armor::Armor(const std::string& name, const std::string& description, int defenseBonus)
    : Item(name, description), defenseBonus(defenseBonus) {}

int Armor::getDefenseBonus() const {
    return defenseBonus;
}

std::string Armor::getFullInfo() const {
    return "[Броня] " + getName() + " (+" + std::to_string(defenseBonus) + " защ) — " + getDescription();
}
