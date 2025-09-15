#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "Colors.h"
#include "Enums.h"


struct DisplayInfo {
    std::string header;
    std::string status;
    std::string details;
    std::string color;
};

std::string centerText(const std::string& text, size_t width);
std::string leftAlign(const std::string& text, size_t width, char fill = ' ');
class Object{
private:
	int _POSITION;

protected:
	std::function<void(int, DamageType)> OnDamageCallback;

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
	virtual void takeDamage(int dmg, DamageType type);
	void setOnDamageCallback(std::function<void(int, DamageType)> callback);
	void removeCallback();

};

#endif 
