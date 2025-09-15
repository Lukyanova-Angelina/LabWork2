#include "Characters.h"

Character::Character()
	: Object(0), _Name("Unknown"), _HP(100), _MAX_HP(0){}

Character::Character(int pos, std::string name, int hp, int maxhp)
	:Object(pos), _Name(name), _HP(hp), _MAX_HP(maxhp){}

std::string Character::getName() const 
{
	return _Name;
}
int Character::getHP() const
{
	return _HP;
}



int Character::getMaxHP() const
{
	return _MAX_HP;
}

// setters
void Character::setName(const std::string& name)
{
	_Name = name;
}

void Character::setHP(int hp)
{
	_HP = hp;
}


void Character::setMaxHP(int maxhp)
{
	_MAX_HP = maxhp;
}


DisplayInfo Character::print() const {
	return {
		"Character",
		"HP:" + std::to_string(getHP()) + "/" + std::to_string(getMaxHP()),
		"",
		Color::GREEN
	};
}
void Character::takeDamage(Weapon* o){
	int hp = getHP();
	setHP(getHP() - (o->getDamage()));
	
	if (OnDamageCallback) {
		OnDamageCallback(getPosition(), o->getElement());
	}
	o->takeDamage(std::min(o->getDamage(), hp), DamageType::NORMAL);
}

void Character::takeHP(int hp){
	setHP(getHP() - hp);
}

void Character::takeDamage(int dmg, DamageType type){
	if (getHP() <= 0) return;
	int finalDamage = calculateFinalDamage(dmg, type);
	takeHP(finalDamage);
	
	if (OnDamageCallback) {
		OnDamageCallback(getPosition(), type);
	}
}
int Character::calculateFinalDamage(int dmg, DamageType type){
	return dmg;
}