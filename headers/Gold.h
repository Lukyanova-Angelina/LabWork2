#ifndef GOLD_H
#define GOLD_H

#include "Object.h"

class Gold: public Object {
private:
	int _Amount;

public:
	Gold(int pos, int amount);
	DisplayInfo print() const override;
	ObjectType returntype() const override;
	InteractionType returnInteractionType() const override;
	int getAmount() const;
	void setAmount(int amount);
	void takeAmount(int amount);

};

#endif