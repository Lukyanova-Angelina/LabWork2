#include "Enemy.h"

Enemy::Enemy(int pos, std::string name, int hp, int maxhp)
	: Character(pos, name, hp, maxhp) {}

Enemy::Enemy(int pos)
	: Character(pos, "name", 10, 10) {} 
Enemy::~Enemy() {
}

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
InteractionType Enemy::returnInteractionType() const{
	return InteractionType::COMBAT_DEPENDENT;
}