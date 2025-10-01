/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/* @file Bomb.cpp
 * @brief Bomb class.
 */
#include "Bomb.h"

Bomb::Bomb(int pos, int amount):Object(pos), _Amount(amount), _Duration(5){}

DisplayInfo Bomb::print() const {
	return {
		"Bomb",
		std::to_string(getAmount()),
		std::string(getDuration(), '*'),
		""
	};
}

ObjectType Bomb::returntype() const {
	return ObjectType::BOMB;
}

InteractionType Bomb::returnInteractionType() const {
	return InteractionType::SWAP_REQUIRED;
}

int Bomb::getAmount() const{
	return _Amount;
}
void Bomb::setAmount(int amount){
	_Amount = amount;
}

int Bomb::getDuration() const{
	return _Duration;
}
void Bomb::setDuration(int dur){
	_Duration = dur;
}

void Bomb::update(){
	setDuration(getDuration() - 1);
}
void Bomb::takeDamage(int dmg, DamageType type){
    if (getAmount() <= 0) return;
    int finalDamage = dmg;
    setAmount(getAmount() - finalDamage);
    
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), type);
    }
}
