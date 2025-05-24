#include "Mag.h"

Mag::Mag(int pos, std::string name, int hp, int maxhp)
	: Enemy(pos, name, hp, maxhp) {} // По умолчанию оружия нет

Mag::Mag(int pos)
	: Enemy(pos, "name", 10, 10) {} // По умолчанию оружия нет
Mag::~Mag() {
}

DisplayInfo Mag::print() const {
    return {
        "Mag",
        "⚔ " + std::to_string(getHP()),
        "",
        Color::RED
    };
}
ObjectType Mag::returntype() const {
    return ObjectType::MAG;
}
void Mag::update(){
	setHP(getHP()+1);
}
InteractionType Mag::returnInteractionType() const{
	return InteractionType::COMBAT_DEPENDENT;
}