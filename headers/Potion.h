#ifndef POTION_H
#define POTION_H

#include "Object.h"
#include "Weapon.h"

enum class PotionType{
	POISON,
	HEAL
};

class Potion: public Object {
private:
	
	int _Power;
	PotionType _Type;

public:
	Potion(int pos, PotionType type);
	Potion(int pos, int power, PotionType type);

	int getPower() const;
	void setPower(int power);

	PotionType getPotionType() const;
	void setPotionType(PotionType type);
	
	DisplayInfo print() const override;
	void takeDamage(Weapon* o);
	void takeDamage(int dmg, DamageType type) override;
	InteractionType returnInteractionType() const override;
	ObjectType returntype() const override;

};

#endif 