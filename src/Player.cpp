/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Player.cpp
 * @brief Implementation of Player class methods.
 */
#include "Player.h"

Player::Player(int pos, std::string name, int hp, int maxhp): Character(pos, name, hp, maxhp), _weapon(nullptr) {}

Player::Player(int pos)
    : Character(pos, "name", 10, 10), _weapon(nullptr) {}

Player::~Player(){
    removeWeapon();
}

Weapon* Player::getWeapon() const {
    return _weapon.get();
}

void Player::setWeapon(std::unique_ptr<Weapon> weapon) {
    _weapon = std::move(weapon);
}

void Player::removeWeapon() {
    _weapon.reset();
}

DisplayInfo Player::print() const {
    return {
        "Player",
        "HP:" + std::to_string(getHP()) + "/" + std::to_string(getMaxHP()),
        "" + (_weapon ? _weapon->print().header + " " + std::to_string(_weapon->getDamage()) : ""),
        Color::GREEN
    };
}

ObjectType Player::returntype() const {
    return ObjectType::PLAYER;
}
