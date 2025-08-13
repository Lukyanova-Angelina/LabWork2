#ifndef THORN_H
#define THORN_H
#include <array>
#include "Object.h"

class Thorn: public Object {
private:
	int _Amount;
	std::array<bool, 4> directions;

public:
	Thorn(int pos, int amount, const std::array<bool, 4>& dirs = {false});
	DisplayInfo print()const override;
	ObjectType returntype() const override;
	InteractionType returnInteractionType() const override;
	virtual void update() override;
	
	void turn();
	int getAmount() const;
	std::array<bool, 4> getDirections() const;

};

#endif