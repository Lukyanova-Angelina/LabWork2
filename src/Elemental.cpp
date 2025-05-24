#include "Elemental.h"

Elemental::Elemental(int pos, std::string name, int hp, int maxhp)
	: Enemy(pos, name, hp, maxhp) {} // По умолчанию оружия нет

Elemental::Elemental(int pos)
	: Enemy(pos, "name", 10, 10) {} // По умолчанию оружия нет
Elemental::~Elemental() {
}

DisplayInfo Elemental::print() const {
    return {
        "Elemental",
        "Dmg: " + std::to_string(getHP()),
        "",
        Color::RED
    };
}
ObjectType Elemental::returntype() const {
    return ObjectType::ELEMENTAL;
}

int Elemental::getElement(){
	return _Element;
}
void Elemental::takeDamage(Weapon* o){
	if (o->returntype() == ObjectType::ELMAGIC){
		ELmagic* stick = dynamic_cast<ELmagic*>(o);
		if (stick) {
			int el = stick->getElement();
			if (el == getElement()){
				setHP(getHP() + o->getDamage());
			} else{
				setHP(getHP() - 2 * o->getDamage());
			}
		}
	}else{
		setHP(getHP() - o->getDamage());
	}
}
InteractionType Elemental::returnInteractionType() const{
	return InteractionType::COMBAT_DEPENDENT;
}