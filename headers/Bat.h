/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Bat.h
 * @brief Bat enemy class - basic flying enemy type.
 * 
 * Simple enemy with random health/damage values. Drops healing potions on death.
 */
#ifndef BAT_H
#define BAT_H

#include "Enemy.h"

/**
 * @class Bat
 * @brief Basic flying enemy with variable damage based on health.
 * 
 * Inherits from Enemy. Damage equals current health.
 * Drops healing potions when defeated.
 */
class Bat : public Enemy {
public:
    /**
     * @brief Constructs a Bat with specified health.
     * @param pos Grid position.
     * @param hp Health points (also determines damage).
     */
    Bat(int pos, int hp);
    
    /**
     * @brief Constructs a Bat with random health (10-19).
     * @param pos Grid position.
     */
    Bat(int pos);
    
    /**
     * @brief Gets display information for bat.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::BAT enum value.
     */
    ObjectType returntype()const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::COMBAT_DEPENDENT enum value.
     */
    InteractionType returnInteractionType() const override;
};

#endif
