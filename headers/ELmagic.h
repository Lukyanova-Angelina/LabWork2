#ifndef ELMAGIC_H
#define ELMAGIC_H

#include "Weapon.h"

class ELmagic:public Weapon { // волшебная палочка с видом элемента
private:
	int _Element;//0 - ice 1 - fire
public:
	ELmagic(int pos, int el); 
	ELmagic(int pos, int damage, int el);
	~ELmagic();
	DisplayInfo print() const override;
	ObjectType returntype() const override;
	int getElement()const;
	std::unique_ptr<Object> clone() const override;
	InteractionType returnInteractionType() const override;

};

#endif // ELMAGIC_H