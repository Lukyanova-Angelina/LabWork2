/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Bomb.h
 * @brief Bomb object class with timed explosion.
 * 
 * Object that explodes after duration expires, dealing damage in four directions.
 */
#ifndef BOMB_H
#define BOMB_H

#include "Object.h"

/**
 * @class Bomb
 * @brief Timed explosive that damages adjacent cells.
 * 
 * Inherits from Object. Has countdown timer and explosion damage value.
 * Explodes when timer reaches zero.
 */
class Bomb: public Object {
private:
    int _Amount;    ///< Explosion damage amount
    int _Duration;  ///< Turns until explosion

public:
    /**
     * @brief Constructs a Bomb with specified damage.
     * @param pos Grid position.
     * @param amount Explosion damage amount.
     */
    Bomb(int pos, int amount);
    
    /**
     * @brief Gets display information for bomb.
     * @return DisplayInfo structure with countdown visualization.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::BOMB enum value.
     */
    ObjectType returntype() const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::SWAP_REQUIRED enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Gets explosion damage amount.
     * @return Damage value of explosion.
     */
    int getAmount() const;
    
    /**
     * @brief Sets explosion damage amount.
     * @param amount New damage value.
     */
    void setAmount(int amount);
    
    /**
     * @brief Gets remaining duration until explosion.
     * @return Turns remaining.
     */
    int getDuration() const;
    
    /**
     * @brief Sets explosion duration.
     * @param dur New duration value.
     */
    void setDuration(int dur);
    
    /**
     * @brief Updates bomb state - decreases countdown.
     */
    void update() override;
    
    /**
     * @brief Applies damage to bomb (reduces explosion power).
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     */
    void takeDamage(int dmg, DamageType type);
};

#endif
