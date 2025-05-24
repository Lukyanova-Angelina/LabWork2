#ifndef STATUS_h
#define STATUS_H
#include <iostream>

class Status{
private: 
	int Gold;
	int level;

public:
	Status();
	setGold();
	getLevel();
	setLevel();
	LevelUp();
	addGold();
	getGold();
	takeGold();

#endif