#include "Weapon.h"

Weapon::Weapon(const std::string& name, const std::string& description, int attackBonus)
    : Item(name, description), attackBonus(attackBonus) {}

int Weapon::getAttackBonus() const {
    return attackBonus;
}

// переопределённый метод — добавляет инфо об уроне~~
std::string Weapon::getFullInfo() const {
    return "[Оружие] " + getName() + " (+" + std::to_string(attackBonus) + " атк) — " + getDescription();
}
