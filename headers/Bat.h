#ifndef BAT_H
#define BAT_H

#include "Enemy.h"

class Bat : public Enemy {
public:
	Bat(int pos, int hp);
	Bat(int pos);
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	InteractionType returnInteractionType() const override;

};

#endif 