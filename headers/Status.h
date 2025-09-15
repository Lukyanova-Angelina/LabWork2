/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Status.h
 * @brief Game progression and loot management system.
 * 
 * Manages player progression, economy, and object generation.
 * Handles experience, leveling, and loot table probabilities.
 */
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

/**
 * @class Status
 * @brief Game state manager for progression and content generation.
 * 
 * Tracks player stats, experience, economy, and manages procedural
 * content generation through weighted loot tables.
 */
class Status {
private: 
    int _Gold;                          ///< Player's gold amount
    int _Level;                         ///< Player level
    int _Steps;                         ///< Steps taken 
    int _Xp;                            ///< Current experience points
    int _XpToNextLevel;                 ///< XP required for next level
    std::vector<std::pair<ObjectType, double>> LootTable; ///< Weighted loot table

public:
    /**
     * @brief Constructs Status with initial values.
     */
    Status();
    
    /**
     * @brief Gets current player level.
     * @return Current level.
     */
    int getLevel() const;
    
    /**
     * @brief Sets player level and updates loot table.
     * @param level New level value.
     */
    void setLevel(int level);
    
    /**
     * @brief Increases player level and updates progression.
     */
    void LevelUp();
    
    /**
     * @brief Sets gold amount.
     * @param gold New gold value.
     */
    void setGold(int gold);
    
    /**
     * @brief Adds gold to player's total.
     * @param gold Amount to add.
     */
    void addGold(int gold);
    
    /**
     * @brief Gets current gold amount.
     * @return Gold value.
     */
    int getGold() const;
    
    /**
     * @brief Reduces player's gold.
     * @param gold Amount to subtract.
     */
    void takeGold(int gold);
    
    /**
     * @brief Gets formatted status string for UI.
     * @return String with gold, level, and XP information.
     */
    std::string print() const;
    
    /**
     * @brief Increments step counter.
     */
    void StepsUp();
    
    /**
     * @brief Gets steps taken.
     * @return Step count.
     */
    int getSteps() const;
    
    /**
     * @brief Gets current experience points.
     * @return XP value.
     */
    int getXp() const;
    
    /**
     * @brief Adds experience points and handles level ups.
     * @param xp Amount of XP to add.
     */
    void addXp(int xp);
    
    /**
     * @brief Gets XP required for next level.
     * @return XP requirement.
     */
    int getXpToNextLevel() const;
    
    /**
     * @brief Generates a random game object based on loot table.
     * @param pos Grid position for the object.
     * @return Unique pointer to generated object.
     */
    std::unique_ptr<Object> generateCard(int pos) const;
    
    /**
     * @brief Generates loot from chest based on chest type.
     * @param pos Grid position for the loot.
     * @param type Type of chest (good or bad).
     * @return Unique pointer to generated loot object.
     */
    std::unique_ptr<Object> generateChestLoot(int pos, ChestType type) const;
    
    /**
     * @brief Updates loot table weights based on current level.
     */
    void updateLootTable();
    
    /**
     * @brief Selects random object type from loot table.
     * @return Selected ObjectType based on weights.
     */
    ObjectType RandomSelection() const;
    
    /**
     * @brief Gets random value between 0 and 1.
     * @return Random double value.
     */
    double getRandomValue() const;
};

#endif
