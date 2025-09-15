/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Ruby.cpp
 * @brief Ruby class.
 */
#include "Ruby.h"


Ruby::Ruby(int pos, int amount):Gold(pos, amount){}


DisplayInfo Ruby::print() const {
	return {
        "Ruby",
        "gold x2 " + std::to_string(getAmount()),
        "",
        Color::RED
    };
}
ObjectType Ruby::returntype() const {
	return ObjectType::RUBY;
}
