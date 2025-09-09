#ifndef ELEMENTAL_H
#define ELEMENTAL_H

#include "Enemy.h"
#include "ELmagic.h"
class Elemental : public Enemy { 
private:
	DamageType _Type;
public:
	Elemental(int pos, int hp, DamageType type);
	~Elemental();
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	DamageType getElement() const;
	void takeDamage(Weapon* o) override;
	InteractionType returnInteractionType() const override;
	int calculateFinalDamage(int dmg, DamageType type) override;
};

#endif 