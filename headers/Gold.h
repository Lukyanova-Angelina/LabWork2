/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Gold.h
 * @brief Gold currency class for advancement in the game.
 * 
 * Represents collectible gold coins that can be picked up by player.
 * Can be damaged/destroyed, reducing the gold amount.
 */
#ifndef GOLD_H
#define GOLD_H

#include "Object.h"

/**
 * @class Gold
 * @brief Collectible gold currency object.
 * 
 * Inherits from Object. Represents gold coins that player can collect.
 * Has amount value that can be reduced by damage or collection.
 */
class Gold: public Object {
private:
    int _Amount; ///< Amount of gold represented

public:
    /**
     * @brief Constructs a Gold with specified amount.
     * @param pos Grid position.
     * @param amount Amount of gold.
     */
    Gold(int pos, int amount);
    
    /**
     * @brief Gets display information for gold.
     * @return DisplayInfo structure with gold amount.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::GOLD enum value.
     */
    ObjectType returntype() const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::IMMEDIATE_PASS enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Gets the gold amount.
     * @return Current gold value.
     */
    int getAmount() const;
    
    /**
     * @brief Sets the gold amount.
     * @param amount New gold value.
     */
    void setAmount(int amount);
    
    /**
     * @brief Reduces gold amount by specified value.
     * @param amount Amount to subtract.
     */
    void takeAmount(int amount);
    
    /**
     * @brief Applies damage to gold (reduces amount).
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     */
    void takeDamage(int dmg, DamageType type);
};

#endif
