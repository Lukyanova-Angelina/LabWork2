#include "Gold.h"

Gold::Gold(int pos, int amount):Object(pos), _Amount(amount){}

DisplayInfo Gold::print() const {
    return {
        "Gold!!!!",
        "" + std::to_string(getAmount()),
        "",
        Color::YELLOW
    };
}



ObjectType Gold::returntype() const{
    return ObjectType::GOLD;
}
InteractionType Gold::returnInteractionType() const{
    return InteractionType::IMMEDIATE_PASS;
}

int Gold::getAmount() const{
    return _Amount;
}
void Gold::setAmount(int amount){
    _Amount = amount;
}

void Gold::takeAmount(int amount){
    setAmount(getAmount() - amount);
}


