/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Gun.h
 * @brief Gun trap class - directional weapon emplacement.
 * 
 * Stationary weapon that fires in specific directions.
 * More visually distinct version of thorn that can damage not only a player.
 */
#ifndef GUN_H
#define GUN_H

#include <array>
#include "Thorn.h"

/**
 * @class Gun
 * @brief Directional weapon trap with rotating.
 * 
 * Inherits from Thorn. Uses different visual representation.
 */
class Gun: public Thorn {
private:
    int _Amount;                        ///< Damage amount
    std::array<bool, 4> directions;     ///< Firing directions

public:
    /**
     * @brief Constructs a Gun with specified damage and directions.
     * @param pos Grid position.
     * @param amount Damage amount per shot.
     * @param dirs Initial firing directions (default: all false).
     */
    Gun(int pos, int amount, const std::array<bool, 4>& dirs = {false});
    
    /**
     * @brief Gets display information with weapon sprites.
     * @return DisplayInfo structure with gun visualization.
     */
    DisplayInfo print()const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::GUN enum value.
     */
    ObjectType returntype() const override;
};

#endif
