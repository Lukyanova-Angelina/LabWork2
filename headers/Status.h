#ifndef STATUS_H
#define STATUS_H
#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Gold.h"
#include "Ruby.h"
#include "Thorn.h"
#include "Gun.h"
#include "Potion.h"
#include "Bomb.h"
#include "Dynamite.h"
#include "Chest.h"
#include "Elemental.h"
#include "Bat.h"
#include "Mag.h"
enum class ChestType;
class Status{
private: 
	int _Gold;
	int _Level;
	int _Steps;
	int _Xp;
	int _XpToNextLevel;
	std::vector<std::pair<ObjectType, double>> LootTable;

public:
	Status();
	int getLevel() const;
	void setLevel(int level);
	void LevelUp();
	void setGold(int gold);
	void addGold(int gold);
	int getGold() const;
	void takeGold(int gold);
	std::string print() const;
	void StepsUp();
	int getSteps() const;
	int getXp() const;
	void addXp(int xp);
	int getXpToNextLevel() const;
	std::unique_ptr<Object> generateCard(int pos) const;
	std::unique_ptr<Object> generateChestLoot(int pos, ChestType type) const;
	void updateLootTable();
	ObjectType RandomSelection() const;
	double getRandomValue() const;
};
#endif