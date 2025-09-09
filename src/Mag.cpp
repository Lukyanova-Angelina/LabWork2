#include "Mag.h"

Mag::Mag(int pos, int hp)
    : Enemy(pos, hp) {}

Mag::Mag(int pos)
    : Enemy(pos, "name", 10, 10) {}


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
    setHP(std::min(getHP()+1, getMaxHP()));
}
InteractionType Mag::returnInteractionType() const{
    return InteractionType::COMBAT_DEPENDENT;
}