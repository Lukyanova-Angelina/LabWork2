/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Enemy.cpp
 * @brief Implementation of Enemy class methods.
 */
#include "Enemy.h"

Enemy::Enemy(int pos, std::string name, int hp, int maxhp)
    : Character(pos, name, hp, maxhp) {}

Enemy::Enemy(int pos, int hp)
    : Character(pos, "name", hp, hp * 1.5) {}

DisplayInfo Enemy::print() const {
    return {
        "Enemy",
        "Dmg: " + std::to_string(getHP()),
        "",
        Color::RED
    };
}

ObjectType Enemy::returntype() const {
    return ObjectType::ENEMY;
}

InteractionType Enemy::returnInteractionType() const {
    return InteractionType::COMBAT_DEPENDENT;
}
