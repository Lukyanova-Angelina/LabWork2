#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"

class Weapon:public Object {
private:
	int _damage;

public:
	Weapon(int pos);
	Weapon(int pos, int damage);
	int getDamage() const; 
	void setDamage(int damage);
	DisplayInfo print() const override;
	std::unique_ptr<Object> clone() const override;
	ObjectType returntype()const override;
	InteractionType returnInteractionType() const override;
	void takeDamage(int dmg, DamageType type) override;
	virtual int calculateFinalDamage(int dmg, DamageType type);
	virtual DamageType getElement() const;

};

#endif