#ifndef ELMAGIC_H
#define ELMAGIC_H

#include "Weapon.h"

class ELmagic:public Weapon { // волшебная палочка с видом элемента
private:
	DamageType _Type;
public:
	ELmagic(int pos, DamageType el); 
	ELmagic(int pos, int damage, DamageType el);
	DisplayInfo print() const override;
	ObjectType returntype() const override;
	DamageType getElement()const;
	std::unique_ptr<Object> clone() const override;
	InteractionType returnInteractionType() const override;
	int calculateFinalDamage(int dmg, DamageType type) override;

};

#endif 