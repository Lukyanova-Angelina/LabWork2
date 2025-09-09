#ifndef ENEMY_H
#define ENEMY_H

#include "Characters.h"

class Enemy : public Character {
public:
	Enemy(int pos, std::string name, int hp, int maxhp);
	Enemy(int pos, int hp);
	Enemy(int pos);
	~Enemy();
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	InteractionType returnInteractionType() const override;

};

#endif 