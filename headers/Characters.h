#include <iostream>
#include <string>
class Character
{
private:
	std::string _Name;
	int _HP, _X, _Y, _MANA;
	bool _JUMP, _ALIVE;
public:
	Character();
	Character(std::string name, int hp, int x, int y, int mana, bool jump, bool alive);
	~Character();


	// getters
	std::string getName() const;
	int getHP() const;
	int getX() const;
	int getY() const;
	int getMana() const;
	bool getJump() const;
	bool getAlive() const;

	// setters
	void setName(const std::string& name);
	void setHP(int hp);
	void setX(int x);
	void setY(int y);
	void setMana(int mana);
	void setJump(bool jump);
	void setAlive(bool alive);
};