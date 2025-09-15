/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

/**
 * @file ELweapon.cpp
 * @brief Implementation of ELweapon class methods.
 */
#include "ELweapon.h"

ELweapon::ELweapon(int pos, DamageType el): Weapon(pos), _Type(el) {}

ELweapon::ELweapon(int pos, int damage, DamageType el): Weapon(pos, damage), _Type(el) {}

DisplayInfo ELweapon::print() const {
    std::string el = (getElement() == DamageType::FIRE ? "FIRE" : "ICE");
    return {
        "ELweapon " + el,
        "Dmg: " + std::to_string(getDamage()),
        "",
        Color::MAGENTA
    };
}

ObjectType ELweapon::returntype() const {
    return ObjectType::ELWEAPON;
}

DamageType ELweapon::getElement()const{
    return _Type;
}

InteractionType ELweapon::returnInteractionType() const{
    return InteractionType::IMMEDIATE_PASS;
}

std::unique_ptr<Object> ELweapon::clone() const {
    return std::make_unique<ELweapon>(*this);
}

int ELweapon::calculateFinalDamage(int dmg, DamageType type) {
    DamageType el = getElement();
    if (type == el){
        return -dmg; // Heal when hit with same element
    }
    else {
        return dmg; // Normal damage for other cases
    }
}
