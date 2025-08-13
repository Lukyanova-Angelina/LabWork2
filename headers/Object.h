#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <memory>

enum class InteractionType {
	IMMEDIATE_PASS,    // перейти на карточку в любом случае
	SWAP_REQUIRED,     // поменяться местами с карточкой
	TRIGGER_ON_STAY,  // какое-то действие с карточкой (но стоим на месте)
	COMBAT_DEPENDENT       // зависит от условий (наличие оружия, здоровье и тд)
};
enum class ObjectType {
	OBJECT,
	ENEMY,
	ELEMENTAL,
	MAG,
	BURGLAR,
	BAT,
	WEAPON,
	ELMAGIC,
	ELWEAPON,
	GOLD,
	RUBY,
	THORN,
	GUN,
	BOMB,
	DYNAMITE,
	POISON,
	FASTHEAL,
	TIMEHEAL,
	BADCHEST,
	GOODCHEST,	
	PLAYER
};

namespace Color {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BGRED = "\033[41m";
    const std::string BGGREEN = "\033[42m";
    const std::string BGYELLOW = "\033[43m";
    const std::string BGBLUE = "\033[44m";
    const std::string BGMAGENTA = "\033[45m";
    const std::string BGCYAN = "\033[46m";
    const std::string BGWHITE = "\033[47m";
    const std::string RESET = "\033[0m";
}

struct DisplayInfo {
    std::string header;
    std::string status;
    std::string details;
    std::string color;
};
size_t utf8Len(const std::string& str);
std::string centerText(const std::string& text, long unsigned int width);
std::string leftAlign(const std::string& text, long unsigned int width, char fill = ' ');

class Object{
private:
	int _POSITION;
public:
	Object(int pos);
	virtual ~Object();
	virtual DisplayInfo print()const;
	virtual ObjectType returntype() const;
	virtual InteractionType returnInteractionType() const;
	virtual std::unique_ptr<Object> clone() const;
	virtual void update();
	virtual void OnINTERACT(Object* obj);
	
	int getPosition() const;
	void setPosition(int pos);
	
	void move(int direction);
	bool possibletomove(int direction);
	int getTargetPosition(int direction) const;
	int getTargetDirection(int pos2) const;

	
};

#endif 
