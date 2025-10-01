/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Dynamite.h
 * @brief Dynamite object class - explosive that damages entire row.
 * 
 * Another version of bomb that damages all cells in its row.
 * Inherits bomb functionality with different explosion pattern.
 */
#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "Bomb.h"

/**
 * @class Dynamite
 * @brief Explosive that damages entire row when activated.
 * 
 * Inherits from Bomb. Explodes to damage all cells in the same row.
 */
class Dynamite: public Bomb {
public:
    /**
     * @brief Constructs a Dynamite with specified damage.
     * @param pos Grid position.
     * @param amount Explosion damage amount.
     */
    Dynamite(int pos, int amount);
    
    /**
     * @brief Gets display information for dynamite.
     * @return DisplayInfo structure with dynamite visualization.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::DYNAMITE enum value.
     */
    ObjectType returntype() const override;
};

#endif
