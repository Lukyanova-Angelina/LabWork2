#ifndef GAME_H
#define GAME_H
#include "Characters.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include <memory>
#include <array>
#include <map>
#include <set>

extern const int CELL_WIDTH = 24;
extern const int LINES_PER_CELL = 5;

class Game{
private:
	std::array<std::unique_ptr<Object>, 9> game;
	Player* player = nullptr;
	int Steps=0;
public:
	Game();
	~Game() = default;
	void moveorattack(int direction);
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
	void handleCOMBAT_DEPENDENT(int pos1);
	void drawANIMATION(int pos1, int pos2);
	void drawcard(int pos1, int pos2, int col, int row);

};


#endif