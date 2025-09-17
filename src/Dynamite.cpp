/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
 /**
  * @file Dynamite.cpp
 * @brief Dynamite class. 
 */
#include "Dynamite.h"
Dynamite::Dynamite(int pos, int amount):Bomb(pos, amount){}
DisplayInfo Dynamite::print() const {
	return {
		"Dynamite",
		std::to_string(getAmount()),
		std::string(getDuration(), '*'),
		""
	};
}
ObjectType Dynamite::returntype() const {
	return ObjectType::DYNAMITE;
}
