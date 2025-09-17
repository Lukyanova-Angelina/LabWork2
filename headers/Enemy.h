/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Enemy.h
 * @brief Base enemy class for hostile game entities.
 * 
 * Extends Character class with enemy-specific behavior and interactions.
 * Serves as base class for all enemy types in the game.
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Characters.h"

/**
 * @class Enemy
 * @brief Base class for all enemy entities.
 * 
 * Inherits from Character and defines enemy-specific properties
 * and combat interaction behavior.
 */
class Enemy : public Character {
public:
    /**
     * @brief Constructs an Enemy with specified parameters.
     * @param pos Grid position.
     * @param name Enemy name.
     * @param hp Health points.
     * @param maxhp Maximum health points.
     */
    Enemy(int pos, std::string name, int hp, int maxhp);
    
    /**
     * @brief Constructs an Enemy with health parameter.
     * @param pos Grid position.
     * @param hp Health points (damage value).
     */
    Enemy(int pos, int hp);
    
    /**
     * @brief Constructs an Enemy with default parameters.
     * @param pos Grid position.
     */
    Enemy(int pos);
    
    /**
     * @brief Gets display information for enemy.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::ENEMY enum value.
     */
    ObjectType returntype()const override;
    
    /**
     * @brief Returns the interaction type for enemies.
     * @return InteractionType::COMBAT_DEPENDENT enum value.
     */
    InteractionType returnInteractionType() const override;
};

#endif
