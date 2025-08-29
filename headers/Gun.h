#ifndef GUN_H
#define GUN_H
#include <array>
#include "Thorn.h"

class Gun: public Thorn {
private:
	int _Amount;
	std::array<bool, 4> directions;

public:
	Gun(int pos, int amount, const std::array<bool, 4>& dirs = {false});
	DisplayInfo print()const override;
	ObjectType returntype() const override;
};

#endif