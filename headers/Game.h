#ifndef GAME_H
#define GAME_H
#include "Characters.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Status.h"
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
#include <memory>
#include <array>
#include <map>
#include <set>

inline const int CELL_WIDTH = 24;
inline const int LINES_PER_CELL = 5;

class Game{
private:
	std::array<std::unique_ptr<Object>, 9> game; // array of game objects
	Player* player = nullptr;
	Status _STATUS;
	bool gameOver = false;
	std::function<void(int, DamageType)> damageCallback;
public:
	Game();
	~Game() = default;
	void generate_game();
	void update();
	void draw();
	void clean();
	void handleInput(char input);
	void switchcards(int pos1, int pos2);
	void movecard(int pos, int direction);
	void gotodir(int direction);
	void generatecard(int pos);
	void handleIMMEDIATE_PASS(int pos1, int pos2);
	void handleSWAP_REQUIRED(int pos1, int pos2);
	void handleTRIGGER_ON_STAY(int pos1);
	void handleCOMBAT_DEPENDENT(int pos1, int pos2);
	void drawANIMATION(int pos1, int pos2);
	void drawcard(int pos1, int col, int row);
	bool isPlayerAlive() const;
	bool isGameOver() const;
	void initializeDamageCallbacks();
	void handleObjectDamage(int pos, DamageType type);
	void handleObjectDeath(int pos);
	//void checkForThreeGoldInARow();
};


#endif