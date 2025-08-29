#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Object.h"
#include "Weapon.h"
class Character: public Object {
private:
	std::string _Name;
	int _HP;
	int _MAX_HP;

public:
	Character();
	Character(int pos, std::string name, int hp, int maxhp);
	~Character();

	std::string getName() const;
	int getHP() const;
	
	int getMaxHP() const;

	void setName(const std::string& name);
	void setHP(int hp);
	
	void setMaxHP(int maxhp);
	void takeHP(int hp);
	
	DisplayInfo print() const override;
	virtual void takeDamage(Weapon* o);
	void takeDamage(int dmg, DamageType type) override;
	 virtual int calculateFinalDamage(int dmg, DamageType type);
};

#endif 