#ifndef MAG_H
#define MAG_H

#include "Enemy.h"

class Mag : public Enemy {
public:
	Mag(int pos, std::string name, int hp, int maxhp); 
	Mag(int pos);
	~Mag();
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	InteractionType returnInteractionType() const override;
	void update() override;
};

#endif 