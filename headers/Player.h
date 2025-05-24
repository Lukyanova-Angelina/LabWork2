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
	~Player() = default;
	Weapon* getWeapon() const;
	void setWeapon(std::unique_ptr<Weapon> weapon) ;
	void removeWeapon();
	// std::unique_ptr<Object> clone() const override;
	DisplayInfo print() const override;
	ObjectType returntype()const override;
	
};

#endif