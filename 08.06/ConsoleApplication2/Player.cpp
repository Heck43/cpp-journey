#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int maxHp, int baseAttack, int baseDefense)
    : Character(name, maxHp, baseAttack, baseDefense),
      equippedWeapon(nullptr), equippedArmor(nullptr) {}

// деструктор — освобождаем память от предметов которые создали~~
Player::~Player() {
    delete equippedWeapon;
    delete equippedArmor;
    for (Potion* p : potions) {
        delete p;
    }
}

void Player::equipWeapon(Weapon* weapon) {
    // если уже было оружие — удаляем старое
    delete equippedWeapon;
    equippedWeapon = weapon;
    std::cout << getName() << " экипирует: " << weapon->getFullInfo() << "\n";
}

void Player::equipArmor(Armor* armor) {
    delete equippedArmor;
    equippedArmor = armor;
    std::cout << getName() << " надевает: " << armor->getFullInfo() << "\n";
}

void Player::addPotion(Potion* potion) {
    potions.push_back(potion);
    std::cout << getName() << " подбирает: " << potion->getFullInfo() << "\n";
}

// использование зелья по индексу
bool Player::usePotion(int index) {
    if (index < 0 || index >= static_cast<int>(potions.size())) {
        std::cout << "Зелье с таким номером не существует!\n";
        return false;
    }
    Potion* p = potions[index];
    if (p->isUsed()) {
        std::cout << "Это зелье уже использовано!\n";
        return false;
    }
    std::cout << getName() << " использует \"" << p->getName() << "\"...\n";
    p->use();
    heal(p->getHealAmount());
    return true;
}

// итоговая атака = база + бонус оружия~~
int Player::getAttackPower() const {
    int total = getBaseAttack();
    if (equippedWeapon != nullptr) {
        total += equippedWeapon->getAttackBonus();
    }
    return total;
}

// итоговая защита = база + бонус брони~~
int Player::getDefenseValue() const {
    int total = getBaseDefense();
    if (equippedArmor != nullptr) {
        total += equippedArmor->getDefenseBonus();
    }
    return total;
}

void Player::printInventory() const {
    std::cout << "\n=== Снаряжение " << getName() << " ===\n";

    if (equippedWeapon)
        std::cout << "  " << equippedWeapon->getFullInfo() << "\n";
    else
        std::cout << "  [Оружие] не экипировано\n";

    if (equippedArmor)
        std::cout << "  " << equippedArmor->getFullInfo() << "\n";
    else
        std::cout << "  [Броня] не экипирована\n";

    std::cout << "  Зелья:\n";
    if (potions.empty()) {
        std::cout << "    — нет зелий\n";
    } else {
        for (int i = 0; i < static_cast<int>(potions.size()); i++) {
            std::cout << "    " << (i + 1) << ". " << potions[i]->getFullInfo() << "\n";
        }
    }
    std::cout << "========================\n\n";
}

void Player::printStatus() const {
    std::cout << "[ " << getName() << " ] HP: " << getCurrentHp() << "/" << getMaxHp()
              << " | АТК: " << getAttackPower()
              << " | ЗАЩ: " << getDefenseValue()
              << " | Зелий: " << getPotionCount() << "\n";
}

int Player::getPotionCount() const {
    int count = 0;
    for (const Potion* p : potions) {
        if (!p->isUsed()) count++;
    }
    return count;
}
