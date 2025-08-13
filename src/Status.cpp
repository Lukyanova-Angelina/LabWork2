#include "Status.h"




Status::Status():_Steps(0){
	setLevel(1);
	setGold(0);

}
void Status::StepsUp(){
	_Steps ++;
}
int Status::getSteps(){
	return _Steps;
}
int Status::getLevel(){
	return _Level;
}

void Status::setLevel(int level){
	_Level = level;
}
void Status::setGold(int gold){
	_Gold = gold;
}

void Status::LevelUp(){
	setLevel(getLevel() + 1);
}


void Status::addGold(int gold){
	setGold(gold + getGold());
}
int Status::getGold(){
	return _Gold;
}

void Status::takeGold(int gold){
	setGold(getGold() - gold); // сделать обработку tekegold в случае когда денег меньше чем нужно
}

std::string Status::print() {
	std::ostringstream oss;
	oss << "Gold: " << getGold() << "\nLevel: " << getLevel();
	return oss.str();
}