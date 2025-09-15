/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Mag.h
 * @brief Magician enemy class with health regeneration.
 * 
 * Enemy that regenerates health each turn, making it more durable
 * in prolonged encounters.
 */
#ifndef MAG_H
#define MAG_H

#include "Enemy.h"

/**
 * @class Mag
 * @brief Magician enemy with health regeneration ability.
 * 
 * Inherits from Enemy. Regenerates 1 health per game update until maxHP.
 * More durable than basic enemies due to self-healing.
 */
class Mag : public Enemy {
public:
    /**
     * @brief Constructs a Mag with specified health.
     * @param pos Grid position.
     * @param hp Health points.
     */
    Mag(int pos, int hp);
    
    /**
     * @brief Constructs a Mag with default health (10).
     * @param pos Grid position.
     */
    Mag(int pos);
    
    /**
     * @brief Gets display information for Mag.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::MAG enum value.
     */
    ObjectType returntype()const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::COMBAT_DEPENDENT enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Updates magician state - regenerates health.
     */
    void update() override;
};

#endif
