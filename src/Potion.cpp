#include "Potion.h"

Potion::Potion(int pos, PotionType type):Object(pos), _Type(type){
	switch(type) {
		case PotionType::HEAL:
			setPower(20 + rand() % 31);
			break;
		case PotionType::POISON:
			setPower(20 + rand() % 15);
			break;
	}
}
Potion::Potion(int pos, int power, PotionType type):Object(pos), _Power(power), _Type(type){}


int Potion::getPower() const{
	return _Power;
}
void Potion::setPower(int power){
	_Power = power;
}

PotionType Potion::getPotionType()const{
	return _Type;
}
void Potion::setPotionType(PotionType type){
	_Type = type;
}

DisplayInfo Potion::print() const {
	switch(getPotionType()){
		case PotionType::HEAL:
			{
				return
				{
					"Heal",
					"power:" + std::to_string(getPower()),
					"",
					Color::GREEN
				};
			}
		case PotionType::POISON:
			{
				return
				{
					"Poison",
					"power:" + std::to_string(getPower()),
					"",
					Color::MAGENTA
				};
			}
		default:
			return {
				"Unknown",
				"Power:" + std::to_string(getPower()),
				"",
				Color::WHITE
			};
	}
}

void Potion::takeDamage(Weapon* o){
	setPower(getPower() - o->getDamage());
}
void Potion::takeDamage(int dmg, DamageType type){
	if (getPower() <= 0) return;
	int finalDamage = dmg;
	setPower(getPower() - finalDamage);
	
	if (OnDamageCallback) {
		OnDamageCallback(getPosition(), type);
	}
}
InteractionType Potion::returnInteractionType() const{
	return InteractionType::IMMEDIATE_PASS;
}
ObjectType Potion::returntype() const{
	return ObjectType::POTION;
}