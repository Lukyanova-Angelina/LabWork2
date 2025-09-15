/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Elemental.cpp
 * @brief Implementation of Elemental class methods.
 */
#include "Elemental.h"

Elemental::Elemental(int pos, int hp, DamageType type)
    : Enemy(pos, hp), _Type(type) {}

DisplayInfo Elemental::print() const {
    std::string el = (getElement() == DamageType::FIRE ? "FIRE" : "ICE");
    return {
        "Elemental " + el,
        "Dmg: " + std::to_string(getHP()),
        "",
        Color::RED
    };
}

ObjectType Elemental::returntype() const {
    return ObjectType::ELEMENTAL;
}

DamageType Elemental::getElement() const {
    return _Type;
}

void Elemental::takeDamage(Weapon* o) {
    int hp;
    if (o->returntype() == ObjectType::ELMAGIC) {
        ELmagic* stick = dynamic_cast<ELmagic*>(o);
        if (stick) {
            DamageType el = stick->getElement();
            if (el == getElement()) {
                hp = getHP();
                setHP(hp + std::min(o->getDamage(), hp));
            } else {
                if (2 * o->getDamage() < getHP()) {
                    hp = getHP();
                    setHP(hp - 2 * o->getDamage());
                } else {
                    hp = (getHP() + 1) / 2;
                    setHP(getHP() - 2 * hp);
                }
            }
        }
    } else {
        hp = getHP();
        setHP(getHP() - o->getDamage());
    }
    o->takeDamage(std::min(o->getDamage(), hp), DamageType::NORMAL);
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), o->getElement());
    }
}

InteractionType Elemental::returnInteractionType() const {
    return InteractionType::COMBAT_DEPENDENT;
}

int Elemental::calculateFinalDamage(int dmg, DamageType type) {
    DamageType el = getElement();
    if (type == el) {
        return -dmg; // Heal from same element
    } else if ((type == DamageType::FIRE && el == DamageType::ICE) || 
               (type == DamageType::ICE && el == DamageType::FIRE)) {
        return dmg * 2; // Double damage from opposite element
    } else {
        return dmg; // Normal damage
    }
}
