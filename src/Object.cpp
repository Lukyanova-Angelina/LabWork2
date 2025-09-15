#include "Object.h"
// Конструктор
Object::Object(int pos) :_POSITION(pos){
}

// Деструктор
Object::~Object() {
    removeCallback();
}


DisplayInfo Object::print() const {
    return {
        "Object",
        "",
        "",
        Color::BLUE
    };
}
std::unique_ptr<Object> Object::clone() const {
        return std::make_unique<Object>(*this);
    }
int Object::getPosition() const
{
    return _POSITION;
}
void Object::setPosition(int pos)
{
    _POSITION = pos;
}
ObjectType Object::returntype() const {
    return ObjectType::OBJECT;
}
InteractionType Object::returnInteractionType() const{
    return InteractionType::IMMEDIATE_PASS;
}
void Object::move(int direction){
    if (direction == 0 && getPosition() > 2){
        setPosition(getPosition() - 3);
    }else if (direction == 1 && getPosition() % 3 != 2){
        setPosition(getPosition() + 1);
    }else if (direction == 3 && getPosition() % 3 != 0){
        setPosition(getPosition() - 1);
    }else if (direction == 2 && getPosition() < 6){
        setPosition(getPosition() + 3);
    }
}
int Object::getTargetPosition(int direction) const {
    switch (direction) {
        case 0:
            if ((getPosition() -3) >= 0) {return getPosition() -3;}
            return -1;
        case 1:
            if ((getPosition() + 1) / 3 == getPosition() / 3) 
                {return getPosition() + 1;}
            return -1;
        case 2:
            if ((getPosition() +3) <= 8) {return getPosition() +3;}
            return -1;
        case 3:
            if ((getPosition() - 1) / 3 == getPosition() / 3) {return getPosition() -1;}
            return -1;
        default:
            return -1; 
    }
}
int Object::getTargetDirection(int pos2) const{
    switch(getPosition() - pos2){
        case 1:
            return 3;
        case -1:
            return 1;
        case 3:
            return 0;
        case -3:
            return 2;
        default:
            return -1;
    }
}

bool Object::possibletomove(int direction){
    if (direction == 0 && getPosition() > 2){
        return true;
    }else if (direction == 1 && getPosition() % 3 != 2){
        return true;
    }else if (direction == 3 && getPosition() % 3 != 0){
        return true;
    }else if (direction == 2 && getPosition() < 6){
        return true;
    }
    return false;

}
void Object::update(){
}
void Object::OnINTERACT(Object* obj){}


void Object::takeDamage(int dmg, DamageType type){
    if (OnDamageCallback){
        OnDamageCallback(getPosition(), type);
    }
}
void Object::setOnDamageCallback(std::function<void(int, DamageType)> callback){
    OnDamageCallback = callback;
}
void Object::removeCallback(){
    OnDamageCallback = nullptr;
}



std::string centerText(const std::string& text, size_t width) {
    if (text.empty()) {
        return std::string(width, ' ');
    }
    
    
    static const std::unordered_map<std::string, int> symbolCorrections = {
        {"→", -2},
        {"←", -2},
        {"↓", -2},
        {"↑", -2},
        {"▲", -2},
        {"◀", -2},
        {"▶", -2},
        {"▼", -2},
        {"⚔", -2}
    };
    
    size_t effectiveLength = text.length();
    
    for (const auto& [symbol, correction] : symbolCorrections) {
        if (text.find(symbol) != std::string::npos) {
            effectiveLength += correction;
        }
    }

    if (effectiveLength >= width) {
        return text.substr(0, width);
    }
    
    size_t leftPadding = (width - effectiveLength) / 2;
    size_t rightPadding = width - effectiveLength - leftPadding;
    
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}
std::string leftAlign(const std::string& text, size_t width, char fill) {
    if (text.length() >= width) {
        return text.substr(0, width);
    }
    return text + std::string(width - text.length(), fill);
}