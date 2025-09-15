/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Characters.cpp
 * @brief Implementation of Character class methods.
 */
#include "Characters.h"

// Default constructor
Character::Character()
    : Object(0), _Name("Unknown"), _HP(100), _MAX_HP(0) {}

// Parameterized constructor
Character::Character(int pos, std::string name, int hp, int maxhp)
    : Object(pos), _Name(name), _HP(hp), _MAX_HP(maxhp) {}

// Getters
std::string Character::getName() const { return _Name; }
int Character::getHP() const { return _HP; }
int Character::getMaxHP() const { return _MAX_HP; }

// Setters
void Character::setName(const std::string& name) { _Name = name; }
void Character::setHP(int hp) { _HP = hp; }
void Character::setMaxHP(int maxhp) { _MAX_HP = maxhp; }

// Display info with health status
DisplayInfo Character::print() const {
    return {
        "Character",
        "HP:" + std::to_string(getHP()) + "/" + std::to_string(getMaxHP()),
        "",
        Color::GREEN
    };
}

/**
 * @brief Applies damage from weapon and damages the weapon in return.
 * @param o Weapon dealing the damage.
 */
void Character::takeDamage(Weapon* o){
    int hp = getHP();
    setHP(getHP() - (o->getDamage()));
    
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), o->getElement());
    }
    o->takeDamage(std::min(o->getDamage(), hp), DamageType::NORMAL);
}

// Reduces health by specified amount
void Character::takeHP(int hp){
    setHP(getHP() - hp);
}

/**
 * @brief Applies damage with type consideration and callback.
 * @param dmg Base damage amount.
 * @param type Type of damage being applied.
 */
void Character::takeDamage(int dmg, DamageType type){
    if (getHP() <= 0) return;
    int finalDamage = calculateFinalDamage(dmg, type);
    takeHP(finalDamage);
    
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), type);
    }
}

// Base damage calculation (no modifications)
int Character::calculateFinalDamage(int dmg, DamageType type){
    return dmg;
}
