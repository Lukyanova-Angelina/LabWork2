#ifndef ELWEAPON_H
#define ELWEAPON_H

#include "Weapon.h"

class ELweapon:public Weapon { // оружие может заряжаться определенным элементом
private:
	int _Element;//0 - ice 1 - fire
public:
	ELweapon(int pos, int el); 
	ELweapon(int pos, int damage, int el);
	~ELweapon();
	DisplayInfo print() const override;
	std::unique_ptr<Object> clone() const override;
	ObjectType returntype() const override;
	int getElement()const;
	InteractionType returnInteractionType() const override;

};

#endif