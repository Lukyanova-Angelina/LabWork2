#include "Thorn.h"
Thorn::Thorn(int pos, int amount, const std::array<bool, 4>& dirs):Object(pos), _Amount(amount), directions(dirs){}

DisplayInfo Thorn::print()const{ //←, →, ↑, ↓.
	auto dir = getDirections();
	return {
		(dir[0] ? "↑": ""),
		(dir[3] ? "← ": "  ") + std::to_string(getAmount()) + (dir[1] ? " →": "  "),
		(dir[2] ? "↓": ""),
		Color::BLUE
	};
}
ObjectType Thorn::returntype() const {
	return ObjectType::THORN;

}
InteractionType Thorn::returnInteractionType() const{
	return InteractionType::IMMEDIATE_PASS;
}
void Thorn::update(){
	turn();
}

void Thorn::turn(){
	bool last = directions[3];
	for (int i = 3; i > 0; --i){
		directions[i] = directions[i-1];
	}
	directions[0] = last;
}

int Thorn::getAmount() const{
	return _Amount;
}
void Thorn::setAmount (int amount){
	_Amount = amount;
}

std::array<bool, 4> Thorn::getDirections() const{
	return directions;
}
void Thorn::takeDamage(int dmg, DamageType type){
    if (getAmount() <= 0) return;
    int finalDamage = calculateFinalDamage(dmg, type);
    setAmount(getAmount() - finalDamage);
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), type);
    }
}
int Thorn::calculateFinalDamage(int dmg, DamageType type){
    return dmg;
}