#include "Status.h"




Status::Status():_Steps(0), _Xp(0), _XpToNextLevel(500){
	setLevel(1);
	setGold(0);
	updateLootTable();


}
void Status::StepsUp(){
	_Steps ++;
}
int Status::getSteps() const {
	return _Steps;
}
int Status::getLevel() const {
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
	updateLootTable();
}


void Status::addGold(int gold){
	setGold(gold + getGold());
}
int Status::getGold() const {
	return _Gold;
}

void Status::takeGold(int gold){
	setGold(getGold() - gold); // сделать обработку tekegold в случае когда денег меньше чем нужно
}

std::string Status::print() const {
	std::ostringstream oss;
	oss << "Gold: " << getGold() << "\nLevel: " << getLevel()<< "\nExperience: "<<getXp()<<"/"<<getXpToNextLevel()<<std::endl;
	return oss.str();
}
int Status::getXp() const{
	return _Xp;
}
void Status::addXp(int xp){
	_Xp += xp;
	if (_Xp >= getXpToNextLevel()){
		_Xp = 0;
		_XpToNextLevel *= 1.5;
		LevelUp();
	}
}
int Status::getXpToNextLevel() const{
	return _XpToNextLevel;
}

std::unique_ptr<Object> Status::generateCard(int pos) const{
	ObjectType type = RandomSelection();
	int level = getLevel();
	int baseValue = 5 + level * 2;
	switch(type){
	case ObjectType::BAT:
			{
				return std::make_unique<Bat>(pos, baseValue + rand() % (3 * level) + 5);
			}
		case ObjectType::BOMB:
			{
				return std::make_unique<Bomb>(pos, baseValue + rand() % (3 * level));
			}
		case ObjectType::CHEST:
			{
				return std::make_unique<Chest>(pos, getRandomValue() < 0.6 ? ChestType::GOODCHEST : ChestType::BADCHEST);
			}
		case ObjectType::DYNAMITE:
			{
				return std::make_unique<Dynamite>(pos, baseValue + rand() % (3 * level));
			}
		case ObjectType::ELEMENTAL:
			{
				return std::make_unique<Elemental>(pos, baseValue + rand() % (6 * level), getRandomValue() > 0.5 ? DamageType::ICE : DamageType::FIRE);
			}
		case ObjectType::ELMAGIC:
			{
				return std::make_unique<ELmagic>(pos, baseValue + rand() % (6 * level), getRandomValue() > 0.5 ? DamageType::ICE : DamageType::FIRE);
			}
		case ObjectType::ELWEAPON:
			{
				return std::make_unique<ELweapon>(pos, baseValue + rand() % (6 * level), getRandomValue() > 0.5 ? DamageType::ICE : DamageType::FIRE);
			}
		case ObjectType::ENEMY:
			{
				return std::make_unique<Enemy>(pos, baseValue + rand() % (4 * level));
			}
		case ObjectType::GOLD:
			{
				return std::make_unique<Gold>(pos, baseValue + rand() % (5 * level));
			}
		case ObjectType::GUN:
			{
				return std::make_unique<Gun>(pos, baseValue + rand() % (4 * level), std::array<bool, 4>{false, true, getRandomValue() < 0.3 ? false : true, getRandomValue() < 0.5 ? false : true});
			}
		case ObjectType::MAG:
			{
				return std::make_unique<Mag>(pos, baseValue + rand() % (4 * level));
			}
		case ObjectType::OBJECT:
			return std::make_unique<Gold>(pos, baseValue + rand() % (5 * level));
		
		case ObjectType::POTION:
			{
				return std::make_unique<Potion>(pos, baseValue + rand() % (3 * level), getRandomValue() > 0.7 ? PotionType::POISON : PotionType::HEAL);
			}
		
		case ObjectType::RUBY:
			{
				return std::make_unique<Ruby>(pos, baseValue + rand() % (3 * level));
			}
		case ObjectType::THORN:
			{
				return std::make_unique<Thorn>(pos, baseValue + rand() % (3 * level), std::array<bool, 4>{false, true, getRandomValue() < 0.3 ? false : true, getRandomValue() < 0.5 ? false : true});
			}
		case ObjectType::WEAPON:
			{
				return std::make_unique<Weapon>(pos, baseValue + rand() % (6 * level));
			}
		default:
			std::cerr<<"None type of generateCard in Status.cpp"<<std::endl;
			return nullptr;
	}
}
std::unique_ptr<Object> Status::generateChestLoot(int pos, ChestType type) const{
	double randomValue = getRandomValue();
	int level = getLevel();
	int baseValue = 5 + level * 2;
	switch(type){
		case ChestType::BADCHEST:
			{
				if (randomValue < 0.4){
					return std::make_unique<Potion>(pos, baseValue + rand() % (6 * level), PotionType::POISON);
				} else if (randomValue < 0.7){
					return std::make_unique<Bomb>(pos, baseValue + rand() % (6 * level));
				} else {
					return std::make_unique<Enemy>(pos, baseValue + rand() % (6 * level));
				}
			}
		case ChestType::GOODCHEST:
			{
				if (randomValue < 0.4){
					return std::make_unique<Potion>(pos, baseValue + rand() % (6 * level), PotionType::HEAL);
				} else if (randomValue < 0.7){
					return std::make_unique<Gold>(pos, baseValue + rand() % (6 * level));
				} else {
					return std::make_unique<Weapon>(pos, baseValue + rand() % (6 * level));
				}
			}
		default:
			std::cerr<<"None type of Chest in Status.cpp"<<std::endl;
			return nullptr;

	}

}

ObjectType Status::RandomSelection() const {
	if (LootTable.empty()) {
		std::cerr << "ERROR: LootTable is empty! Returning RUBY as fallback." << std::endl;
		return ObjectType::OBJECT;
	}
	double totalWeight = 0.0;
	for (const auto& item : LootTable) {
		totalWeight += item.second;
	}
	double randomValue = getRandomValue() * totalWeight;
	double sumWeight = 0.0;
	
	for (const auto& item : LootTable){
		sumWeight += item.second;
		if (randomValue <= sumWeight + 1e-10){
			return item.first;
		}
	}
	return LootTable.rbegin()->first;
}

double Status::getRandomValue() const {
	return static_cast<double>(rand()) / (RAND_MAX + 1.0);
}
void Status::updateLootTable(){
	LootTable.clear();
	int level = getLevel();
	if (level <= 2){
		LootTable = {
			{ObjectType::ENEMY, 5},
			{ObjectType::BAT, 1},
			{ObjectType::GOLD, 4},
			{ObjectType::WEAPON, 4},
			{ObjectType::RUBY, 1},
			{ObjectType::ELWEAPON, 2},
			{ObjectType::GUN, 5}
		};
	} else if (level <= 4){
		LootTable = {
			{ObjectType::ENEMY, 6},
			{ObjectType::BAT, 2},
			{ObjectType::GUN, 2},
			{ObjectType::BOMB, 1},
			{ObjectType::DYNAMITE, 1},
			{ObjectType::GOLD, 4},
			{ObjectType::WEAPON, 4},
			{ObjectType::RUBY, 1},
			{ObjectType::ELWEAPON, 2},
			{ObjectType::THORN, 2},
			{ObjectType::POTION, 2},
			{ObjectType::CHEST, 20},
			{ObjectType::ELMAGIC, 1}
		};
	}else{
		LootTable = {
			{ObjectType::ENEMY, 6},
			{ObjectType::BAT, 2},
			{ObjectType::GUN, 2},
			{ObjectType::BOMB, 1},
			{ObjectType::DYNAMITE, 1},
			{ObjectType::GOLD, 3},
			{ObjectType::WEAPON, 4},
			{ObjectType::RUBY, 2},
			{ObjectType::ELWEAPON, 2},
			{ObjectType::THORN, 2},
			{ObjectType::POTION, 2},
			{ObjectType::CHEST, 3},
			{ObjectType::ELMAGIC, 1},
			{ObjectType::ELEMENTAL, 2},
			{ObjectType::MAG, 1}
		};
	}
}