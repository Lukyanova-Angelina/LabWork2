#ifndef STATUS_H
#define STATUS_H
#include <iostream>
#include <string>
#include <sstream>

class Status{
private: 
	int _Gold;
	int _Level;
	int _Steps;

public:
	Status();
	int getLevel();
	void setLevel(int level);
	void LevelUp();
	void setGold(int gold);
	void addGold(int gold);
	int getGold();
	void takeGold(int gold);
	std::string print();
	void StepsUp();
	int getSteps();
};
#endif