#include "ELmagic.h"


ELmagic::ELmagic(int pos, int el):Weapon(pos), _Element(el){}


ELmagic::ELmagic(int pos, int damage, int el):Weapon(pos, damage), _Element(el){}

ELmagic::~ELmagic(){}
DisplayInfo ELmagic::print() const {
    return {
        "ELmagic",
        "Dmg: " + std::to_string(getDamage()),"",
        Color::RED
    };
}
ObjectType ELmagic::returntype() const {
    return ObjectType::ELMAGIC;
}
int ELmagic::getElement()const{
	return _Element;
}
InteractionType ELmagic::returnInteractionType() const{
	return InteractionType::IMMEDIATE_PASS;
}
std::unique_ptr<Object> ELmagic::clone() const {
        return std::make_unique<ELmagic>(*this);
    }