#ifndef ELWEAPON_H
#define ELWEAPON_H

#include "Weapon.h"

class ELweapon:public Weapon { // оружие может заряжаться определенным элементом
private:
	DamageType _Type;
public:
	ELweapon(int pos, DamageType el); 
	ELweapon(int pos, int damage, DamageType el);
	~ELweapon();
	DisplayInfo print() const override;
	std::unique_ptr<Object> clone() const override;
	ObjectType returntype() const override;
	DamageType getElement()const;
	InteractionType returnInteractionType() const override;
	int calculateFinalDamage(int dmg, DamageType type) override;

};

#endif