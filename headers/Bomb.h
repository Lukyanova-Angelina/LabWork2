#ifndef BOMB_H
#define BOMB_H

#include "Object.h"

class Bomb: public Object {
private:
	int _Amount;
	int _Duration;

public:
	Bomb(int pos, int amount);
	DisplayInfo print() const override;
	ObjectType returntype() const override;
	InteractionType returnInteractionType() const override;
	int getAmount() const;
	void setAmount(int amount);
	int getDuration() const;
	void setDuration(int dur);
	void update() override;
	void takeDamage(int dmg, DamageType type);
};

#endif