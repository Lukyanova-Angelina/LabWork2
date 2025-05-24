#include "Characters.h"

Character::Character()
	: Object(0), _Name("Unknown"), _HP(100), _MAX_HP(0){}

Character::Character(int pos, std::string name, int hp, int maxhp)
	:Object(pos), _Name(name), _HP(hp), _MAX_HP(maxhp){}
Character::~Character(){}
//getters
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
	setHP(getHP() - (o->getDamage()));
}

