#include "Object.h"
// Конструктор
Object::Object(int pos) :_POSITION(pos){
}

// Деструктор
Object::~Object() {}

// Реализация оператора <<
// std::ostream& operator<<(std::ostream& os, const Object& obj) {
//     obj.print(os); // Вызов виртуального метода
//     return os;
// }
DisplayInfo Object::print() const {
    return {
        "Object",
        "",
        "",
        Color::GREEN
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
    return InteractionType::COMBAT_DEPENDENT;
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
            return getPosition() - 3;
        case 1:
            return getPosition() + 1;
        case 2:
            return getPosition() + 3;
        case 3:
            return getPosition() - 1;
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


std::string centerText(const std::string& text, long unsigned int width) {
    if (text.length() >= width) return text.substr(0, width);
    int padding = (width - text.length()) / 2;
    return std::string(padding, ' ') + text + std::string(width - text.length() - padding, ' ');
}

std::string leftAlign(const std::string& text, long unsigned int width, char fill) {
    if (text.length() >= width) return text.substr(0, width);
    return text + std::string(width - text.length(), fill);
}
