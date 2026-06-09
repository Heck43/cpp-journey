#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& name, const std::string& type,
             int maxHp, int baseAttack, int baseDefense)
    : Character(name, maxHp, baseAttack, baseDefense), type(type) {}

std::string Enemy::getType() const {
    return type;
}

void Enemy::printStatus() const {
    std::cout << "[ " << getName() << " (" << type << ") ] HP: "
              << getCurrentHp() << "/" << getMaxHp()
              << " | АТК: " << getAttackPower()
              << " | ЗАЩ: " << getDefenseValue() << "\n";
}
