	
#include "Weapon.h"

Weapon::Weapon(int pos) : Object(pos){
	_damage = rand() % 42;
}
Weapon::~Weapon() {}
Weapon::Weapon(int pos, int damage) : Object(pos), _damage(damage) {}

int Weapon::getDamage() const {
	return _damage;
}

void Weapon::setDamage(int damage) {
	_damage = damage;
}

DisplayInfo Weapon::print() const {
    return {
        "WEAPON",
        "Dmg: " + std::to_string(getDamage()),"",
        Color::CYAN
    };
}
ObjectType Weapon::returntype() const {
    return ObjectType::WEAPON;
}
InteractionType Weapon::returnInteractionType() const{
	return InteractionType::IMMEDIATE_PASS;
}
std::unique_ptr<Object> Weapon::clone() const {
        return std::make_unique<Weapon>(*this);
    }