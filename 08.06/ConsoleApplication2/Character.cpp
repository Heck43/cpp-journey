#include "Character.h"
#include <iostream>
#include <algorithm>

Character::Character(const std::string& name, int maxHp, int baseAttack, int baseDefense)
    : name(name), maxHp(maxHp), currentHp(maxHp),
      baseAttack(baseAttack), baseDefense(baseDefense) {}

std::string Character::getName() const { return name; }
int Character::getMaxHp() const { return maxHp; }
int Character::getCurrentHp() const { return currentHp; }
int Character::getBaseAttack() const { return baseAttack; }
int Character::getBaseDefense() const { return baseDefense; }

bool Character::isAlive() const {
    return currentHp > 0;
}

// получаем урон: реальный урон = атака - защита, минимум 1~~
void Character::takeDamage(int damage) {
    int defense = getDefenseValue();
    int realDamage = std::max(1, damage - defense);
    currentHp = std::max(0, currentHp - realDamage);

    std::cout << getName() << " получает " << realDamage
              << " урона (заблокировано " << (damage - realDamage) << ")"
              << " | HP: " << currentHp << "/" << maxHp << "\n";
}

// лечение — не выходим за максимум
void Character::heal(int amount) {
    int oldHp = currentHp;
    currentHp = std::min(maxHp, currentHp + amount);
    std::cout << getName() << " восстанавливает " << (currentHp - oldHp) << " HP"
              << " | HP: " << currentHp << "/" << maxHp << "\n";
}

int Character::getAttackPower() const {
    return baseAttack;
}

int Character::getDefenseValue() const {
    return baseDefense;
}

void Character::printStatus() const {
    std::cout << "[ " << name << " ] HP: " << currentHp << "/" << maxHp
              << " | АТК: " << getAttackPower()
              << " | ЗАЩ: " << getDefenseValue() << "\n";
}
