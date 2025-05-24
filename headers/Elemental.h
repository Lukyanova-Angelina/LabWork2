#ifndef ELEMENTAL_H
#define ELEMENTAL_H

#include "Enemy.h"
#include "ELmagic.h"
class Elemental : public Enemy { 
private:
	int _Element; // 0 - ice 1 - fire 
public:
	Elemental(int pos, std::string name, int hp, int maxhp); 
	Elemental(int pos);
	~Elemental();
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	int getElement();
	void takeDamage(Weapon* o) override;
	InteractionType returnInteractionType() const override;
};

#endif 