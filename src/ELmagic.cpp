#include "ELmagic.h"


ELmagic::ELmagic(int pos, DamageType el):Weapon(pos), _Type(el){}


ELmagic::ELmagic(int pos, int damage, DamageType el):Weapon(pos, damage), _Type(el){}

ELmagic::~ELmagic(){}
DisplayInfo ELmagic::print() const {
    std::string el = (getElement() == DamageType::FIRE ? "FIRE" : "ICE");
    return {
        "ELmagic " + el,
        "Dmg: " + std::to_string(getDamage()),
        "",
        Color::GREEN
    };
}
ObjectType ELmagic::returntype() const {
    return ObjectType::ELMAGIC;
}
DamageType ELmagic::getElement()const{
    return _Type;
}
InteractionType ELmagic::returnInteractionType() const{
    return InteractionType::IMMEDIATE_PASS;
}
std::unique_ptr<Object> ELmagic::clone() const {
        return std::make_unique<ELmagic>(*this);
    }
int ELmagic::calculateFinalDamage(int dmg, DamageType type) {
    DamageType el = getElement();
    if (type == el){
        return -dmg;
    }
    else if((type == DamageType::FIRE && el == DamageType::ICE) || (type == DamageType::ICE && el == DamageType::FIRE)){
        return dmg * 2;
    }
    else {
        return dmg;
    }
}