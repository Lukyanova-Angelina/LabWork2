#include "Bat.h"

Bat::Bat(int pos, int hp):Enemy(pos, hp){}
Bat::Bat(int pos):Enemy(pos, rand() % 10 + 10){}
DisplayInfo Bat::print() const {
    return {
        "Bat",
        "Dmg: " + std::to_string(getHP()),
        "",
        Color::RED
    };
}
ObjectType Bat::returntype()const {
    return ObjectType::BAT;

}
InteractionType Bat::returnInteractionType() const {
    return InteractionType::COMBAT_DEPENDENT;
}