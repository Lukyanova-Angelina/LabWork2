#include "Chest.h"

Chest::Chest(int pos, ChestType type):Object(pos), _Type(type){}

ChestType Chest::getChestType() const {
	return _Type;
}
DisplayInfo Chest::print() const {
	switch(getChestType()){
	case ChestType::BADCHEST:
		{
			return {
				"Bad chest",
				"",
				"",
				Color::RED
			};
		}
	case ChestType::GOODCHEST:
		{
			return {
				"Good chest",
				"",
				"",
				Color::BLUE
			};
		}
	default:
		std::cerr<<"None ChestType";
		return {
			"UNKNOWN", 
			"Chest", 
			"Error", 
			Color::WHITE};
	}
	
}
ObjectType Chest::returntype() const {
	return ObjectType::CHEST;
}
InteractionType Chest::returnInteractionType() const {
	return InteractionType::TRIGGER_ON_STAY;
}

std::unique_ptr<Object> Chest::generateLoot(const Status& status) const{
	return status.generateChestLoot(getPosition(), getChestType());
}