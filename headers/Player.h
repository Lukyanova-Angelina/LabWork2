#ifndef PLAYER_H
#define PLAYER_H

#include "Characters.h"
#include "Weapon.h"
#include "ELmagic.h"
#include "ELweapon.h"
#include <memory>

class Player : public Character {
private:
	std::unique_ptr<Weapon> _weapon; 
public:
	Player(int pos, std::string name, int hp, int maxhp); 
	Player(int pos);
	virtual ~Player() override;
	Weapon* getWeapon() const;
	void setWeapon(std::unique_ptr<Weapon> weapon) ;
	void removeWeapon();
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	
};

#endif