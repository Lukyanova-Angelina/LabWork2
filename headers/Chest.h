#ifndef CHEST_H
#define CHEST_H

#include "Object.h"

enum class ChestType{
	BADCHEST,
	GOODCHEST
};

class Chest: public Object {
private:
	ChestType type;
public:
	ChestType getChestType();
	Chest(int pos, int amount);
	DisplayInfo print() const override;
	ObjectType returntype() const override;
	InteractionType returnInteractionType() const override;

};

#endif