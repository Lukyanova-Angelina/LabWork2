#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "Status.h"
class Status;
enum class ChestType{
	BADCHEST,
	GOODCHEST
};

class Chest: public Object {
private:
	ChestType _Type;
public:
	Chest(int pos, ChestType type);
	ChestType getChestType() const;
	DisplayInfo print() const override;
	ObjectType returntype() const override;
	InteractionType returnInteractionType() const override;
	std::unique_ptr<Object> generateLoot(const Status& status) const;

};

#endif