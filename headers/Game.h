/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Game.h
 * @brief Main game controller class managing game state, objects, and interactions.
 * 
 * Handles the 3x3 grid game logic, player input, object interactions,
 * and game state management. Coordinates all game systems and objects.
 */
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
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

inline const int CELL_WIDTH = 24;    ///< Width of each cell in UI
inline const int LINES_PER_CELL = 5; ///< Number of text lines per cell

/**
 * @class Game
 * @brief Main game controller managing the 3x3 grid game.
 */
class Game {
private:
    std::array<std::unique_ptr<Object>, 9> game; ///< 3x3 grid of game objects
    Player* player = nullptr;                    ///< Pointer to player object
    Status _STATUS;                              ///< Game status and progression system
    bool gameOver = false;                       ///< Game over flag
    std::function<void(int, DamageType)> damageCallback; ///< Damage callback reference

public:

    /**
     * @brief Constructs the game and initializes game state.
     */
    Game();
    
    ~Game() = default;
    friend class GameTestAccess;
    
    /**
     * @brief Generates initial game state with player and objects.
     */
    void generate_game();
    
    /**
     * @brief Updates game state (called each frame).
     * Handles object updates, damage.
     */
    void update();
    
    /**
     * @brief Renders the game grid and UI.
     */
    void draw();
    
    /**
     * @brief Clears the console screen.
     */
    void clean();
    
    /**
     * @brief Handles player input and triggers appropriate actions.
     * @param input Character input from player ('w', 'a', 's', 'd').
     */
    void handleInput(char input);
    
    /**
     * @brief Swaps positions of two objects on the grid.
     * @param pos1 First object position.
     * @param pos2 Second object position.
     */
    void switchcards(int pos1, int pos2);
    
    /**
     * @brief Moves an object in specified direction.
     * @param pos Object position to move.
     * @param direction Direction to move (0-3).
     */
    void movecard(int pos, int direction);
    
    /**
     * @brief Handles complex movement logic for grid shifting.
     * @param direction Direction of player movement.
     */
    void gotodir(int direction);
    
    /**
     * @brief Generates a new object at specified position.
     * @param pos Grid position to generate object at.
     */
    void generatecard(int pos);
    
    /**
     * @brief Handles immediate pass interactions (weapons, items, etc.).
     * @param pos1 Player position.
     * @param pos2 Target object position.
     */
    void handleIMMEDIATE_PASS(int pos1, int pos2);
    
    /**
     * @brief Handles swap-required interactions (bombs, dynamite).
     * @param pos1 Player position.
     * @param pos2 Target object position.
     */
    void handleSWAP_REQUIRED(int pos1, int pos2);
    
    /**
     * @brief Handles on-stay trigger interactions (chests).
     * @param pos1 Object position to trigger.
     */
    void handleTRIGGER_ON_STAY(int pos1);
    
    /**
     * @brief Handles combat-dependent interactions (enemies).
     * @param pos1 Player position.
     * @param pos2 Enemy position.
     */
    void handleCOMBAT_DEPENDENT(int pos1, int pos2);
    
    /**
     * @brief Checks if player is alive.
     * @return true if player has HP > 0.
     */
    bool isPlayerAlive() const;
    
    /**
     * @brief Checks if game is over.
     * @return true if game over condition met (player's death).
     */
    bool isGameOver() const;
    
    /**
     * @brief Initializes damage callbacks for all game objects.
     */
    void initializeDamageCallbacks();
    
    /**
     * @brief Handles damage events from objects.
     * @param pos Position of damaged object.
     * @param type Type of damage applied.
     */
    void handleObjectDamage(int pos, DamageType type);
    
    /**
     * @brief Handles object death and replacement.
     * @param pos Position of dead object.
     */
    void handleObjectDeath(int pos);
    
    /**
     * @brief Checks for and converts gold lines to rubies.
     */
    void checkAndConvertGoldToRubies();
};

#endif
