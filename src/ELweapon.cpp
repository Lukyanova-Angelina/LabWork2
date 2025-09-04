#include "ELweapon.h"


ELweapon::ELweapon(int pos, DamageType el):Weapon(pos), _Type(el){}


ELweapon::ELweapon(int pos, int damage, DamageType el):Weapon(pos, damage), _Type(el){}

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
DamageType ELweapon::getElement()const{
	return _Type;
}
InteractionType ELweapon::returnInteractionType() const{
	return InteractionType::IMMEDIATE_PASS;
}
std::unique_ptr<Object> ELweapon::clone() const {
        return std::make_unique<ELweapon>(*this);
    }
int ELweapon::calculateFinalDamage(int dmg, DamageType type) {
    DamageType el = getElement();
    if (type == el){
        return -dmg;
    }
    else {
        return dmg;
    }
}