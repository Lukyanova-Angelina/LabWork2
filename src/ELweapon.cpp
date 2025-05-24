#include "ELweapon.h"


ELweapon::ELweapon(int pos, int el):Weapon(pos), _Element(el){}


ELweapon::ELweapon(int pos, int damage, int el):Weapon(pos, damage), _Element(el){}

ELweapon::~ELweapon(){}
DisplayInfo ELweapon::print() const {
    return {
        "ELweapon",
        "Dmg: " + std::to_string(getDamage()),"",
        Color::MAGENTA
    };
}
ObjectType ELweapon::returntype() const {
    return ObjectType::ELWEAPON;
}
int ELweapon::getElement()const{
	return _Element;
}
InteractionType ELweapon::returnInteractionType() const{
	return InteractionType::IMMEDIATE_PASS;
}
std::unique_ptr<Object> ELweapon::clone() const {
        return std::make_unique<ELweapon>(*this);
    }