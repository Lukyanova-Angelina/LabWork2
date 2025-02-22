#include "Characters.h"

Character::Character()
	: _Name("Unknown"), _HP(100), _X(0), _Y(0), _MANA(50), _JUMP(false), _ALIVE(true) {}

Character::Character(std::string name, int hp, int x, int y, int mana, bool jump, bool alive)
	: _Name(name), _HP(hp), _X(x), _Y(y), _MANA(mana), _JUMP(jump), _ALIVE(alive)
{}
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

int Character::getX() const
{
	return _X;
}

int Character::getY() const
{
	return _Y;
}

int Character::getMana() const
{
	return _MANA;
}

bool Character::getJump() const
{
	return _JUMP;
}

bool Character::getAlive() const
{
	return _ALIVE;
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

void Character::setX(int x)
{
	_X = x;
}

void Character::setY(int y)
{
	_Y = y;
}

void Character::setMana(int mana)
{
	_MANA = mana;
}

void Character::setJump(bool jump)
{
	_JUMP = jump;
}

void Character::setAlive(bool alive)
{
	_ALIVE = alive;
}