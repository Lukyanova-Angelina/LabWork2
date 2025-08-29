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

#include <string>

size_t utf8Len(const std::string& str) {
    size_t len = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];
        if (c <= 0x7F) {
            // ASCII символ
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-байтовый символ UTF-8
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-байтовый символ UTF-8
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            i += 4;
        } else {
            i += 1;
        }
        len++;
    }
    return len;
}

std::string utf8Substr(const std::string& str, size_t maxChars) {
    if (maxChars == 0) return "";
    
    size_t bytePos = 0;
    size_t charCount = 0;
    
    for (size_t i = 0; i < str.length() && charCount < maxChars; ) {
        unsigned char c = str[i];
        size_t charBytes = 1;
        
        if ((c & 0x80) == 0) {
            charBytes = 1;
        } else if ((c & 0xE0) == 0xC0) {
            charBytes = 2;
        } else if ((c & 0xF0) == 0xE0) {
            charBytes = 3;
        } else if ((c & 0xF8) == 0xF0) {
            charBytes = 4;
        }
        
        if (i + charBytes > str.length()) break;
        
        i += charBytes;
        charCount++;
        bytePos = i;
    }
    
    return str.substr(0, bytePos);
}

std::string centerText(const std::string& text, size_t width){
    size_t textLen = utf8Len(text);
    if (textLen >= width) return utf8Substr(text, width);
    
    size_t padding = (width - textLen) / 2;
    return std::string(padding, ' ') + text + std::string(width - textLen - padding, ' ');
}

std::string leftAlign(const std::string& text, size_t width, char fill){
    size_t textLen = utf8Len(text);
    if (textLen >= width) return utf8Substr(text, width);
    return text + std::string(width - textLen, fill);
}
