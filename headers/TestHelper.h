/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
#include "gtest/gtest.h"
#include "Game.h"


class GameTestAccess {
private:
    Game* game;
    
public:
    GameTestAccess(Game* gameInstance) : game(gameInstance) {}
    Game* getGame(){return game;}
    std::array<std::unique_ptr<Object>, 9>& getGameArray() { return game->game; }
    Player* getPlayer() { return game->player; }
    Status& getStatus() { return game->_STATUS; }
    bool& getGameOver() { return game->gameOver; }
};