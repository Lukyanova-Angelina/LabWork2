/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Thorn.h
 * @brief Thorn trap class with rotating damage directions.
 * 
 * Trap object that  can damage entities in specific directions.
 * Directions rotate each turn, creating dynamic hazard patterns. 
* Deals damage to the player when interacting if the thorn is directed at him.
 */
#ifndef THORN_H
#define THORN_H

#include <array>
#include "Object.h"

/**
 * @class Thorn
 * @brief Rotating trap that can damage in specific directions.
 * 
 * Inherits from Object. Has damage amount and directional pattern
 * that rotates each game turn.
 */
class Thorn: public Object {
private:
    int _Amount;                        ///< Damage amount
    std::array<bool, 4> directions;     ///< Active directions (up, right, down, left)

public:
    /**
     * @brief Constructs a Thorn with specified damage and directions.
     * @param pos Grid position.
     * @param amount Damage amount.
     * @param dirs Initial directional pattern (default: all false).
     */
    Thorn(int pos, int amount, const std::array<bool, 4>& dirs = {false});
    
    /**
     * @brief Gets display information with directional arrows.
     * @return DisplayInfo structure with visual direction indicators.
     */
    DisplayInfo print()const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::THORN enum value.
     */
    ObjectType returntype() const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::IMMEDIATE_PASS enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Updates thorn state - rotates directions.
     */
    virtual void update() override;
    
    /**
     * @brief Rotates the directional pattern.
     */
    void turn();
    
    /**
     * @brief Gets damage amount.
     * @return Current damage value.
     */
    int getAmount() const;
    
    /**
     * @brief Sets damage amount.
     * @param amount New damage value.
     */
    void setAmount(int amount);
    
    /**
     * @brief Gets current directional pattern.
     * @return Array of booleans representing active directions.
     */
    std::array<bool, 4> getDirections() const;
    
    /**
     * @brief Applies damage to the thorn (reduces durability).
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     */
    void takeDamage(int dmg, DamageType type) override;
    
    /**
     * @brief Calculates final damage taken (no modifications).
     * @param dmg Base damage amount.
     * @param type Type of damage being applied.
     * @return Unmodified damage amount.
     */
    int calculateFinalDamage(int dmg, DamageType type);
};

#endif
