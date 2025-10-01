/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

/**
 * @file Weapon.h
 * @brief Base weapon class for game combat system.
 * 
 * Represents weapons that can be equipped by player and used in combat.
 * Handles damage and elemental interactions.
 */
#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"

/**
 * @class Weapon
 * @brief Base class for all weapons in the game.
 * 
 * Provides damage management, durability system, and basic combat functionality.
 * Can be equipped by player and used against enemies.
 */
class Weapon: public Object {
private:
    int _damage; ///< Current damage value (also represents durability)

public:
    /**
     * @brief Constructs a Weapon with random damage.
     * @param pos Grid position.
     */
    Weapon(int pos);
    
    /**
     * @brief Constructs a Weapon with specified damage.
     * @param pos Grid position.
     * @param damage Initial damage value.
     */
    Weapon(int pos, int damage);
    
    /**
     * @brief Gets current damage value.
     * @return Current damage/durability.
     */
    int getDamage() const; 
    
    /**
     * @brief Sets damage value.
     * @param damage New damage value.
     */
    void setDamage(int damage);
    
    /**
     * @brief Gets display information for weapon.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Creates a copy of the weapon.
     * @return Unique pointer to cloned weapon.
     */
    std::unique_ptr<Object> clone() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::WEAPON enum value.
     */
    ObjectType returntype()const override;
    
    /**
     * @brief Returns the interaction type for weapons.
     * @return InteractionType::IMMEDIATE_PASS enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Applies damage to weapon (reduces durability).
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     */
    void takeDamage(int dmg, DamageType type) override;
    
    /**
     * @brief Calculates final damage after elemental modifications.
     * @param dmg Base damage amount.
     * @param type Type of damage being applied.
     * @return Final damage after elemental calculations.
     */
    virtual int calculateFinalDamage(int dmg, DamageType type);
    
    /**
     * @brief Gets the elemental type of the weapon.
     * @return DamageType enum value (NORMAL for base weapons).
     */
    virtual DamageType getElement() const;

};

#endif
