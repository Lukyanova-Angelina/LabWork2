/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
 /**
 * @file Gold.cpp
 * @brief Gold class.
 */
#include "Gold.h"

Gold::Gold(int pos, int amount):Object(pos), _Amount(amount){}

DisplayInfo Gold::print() const {
    return {
        "Gold!!!!",
        "" + std::to_string(getAmount()),
        "",
        Color::YELLOW
    };
}



ObjectType Gold::returntype() const{
    return ObjectType::GOLD;
}
InteractionType Gold::returnInteractionType() const{
    return InteractionType::IMMEDIATE_PASS;
}

int Gold::getAmount() const{
    return _Amount;
}
void Gold::setAmount(int amount){
    _Amount = amount;
}

void Gold::takeAmount(int amount){
    setAmount(getAmount() - amount);
}

void Gold::takeDamage(int dmg, DamageType type){
    if (getAmount() <= 0) return;
    int finalDamage = dmg;
    setAmount(getAmount() - finalDamage);
    
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), type);
    }
}
