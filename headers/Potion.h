/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Potion.h
 * @brief Potion consumable class for health manipulation.
 * 
 * Represents consumable potions that can heal or damage the player.
 * Can be either healing potions or poison potions.
 */
#ifndef POTION_H
#define POTION_H

#include "Object.h"
#include "Weapon.h"

/**
 * @class Potion
 * @brief Consumable item that affects player health.
 * 
 * Inherits from Object. Can be either healing (restores health)
 * or poison (damages player). Has power value determining effect strength.
 */
class Potion: public Object {
private:
    int _Power;         ///< Strength of the potion effect
    PotionType _Type;   ///< Type of potion (heal or poison)

public:
    /**
     * @brief Constructs a Potion with random power based on type.
     * @param pos Grid position.
     * @param type Type of potion (HEAL or POISON).
     */
    Potion(int pos, PotionType type);
    
    /**
     * @brief Constructs a Potion with specified power and type.
     * @param pos Grid position.
     * @param power Effect strength value.
     * @param type Type of potion (HEAL or POISON).
     */
    Potion(int pos, int power, PotionType type);

    /**
     * @brief Gets the potion's effect power.
     * @return Power value.
     */
    int getPower() const;
    
    /**
     * @brief Sets the potion's effect power.
     * @param power New power value.
     */
    void setPower(int power);

    /**
     * @brief Gets the potion type.
     * @return PotionType enum value.
     */
    PotionType getPotionType() const;
    
    /**
     * @brief Sets the potion type.
     * @param type New PotionType value.
     */
    void setPotionType(PotionType type);
    
    /**
     * @brief Gets display information for the potion.
     * @return DisplayInfo structure with type and power.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Applies weapon damage to the potion (reduces power).
     * @param o Weapon dealing the damage.
     */
    void takeDamage(Weapon* o);
    
    /**
     * @brief Applies damage to the potion (reduces power).
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     */
    void takeDamage(int dmg, DamageType type) override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::IMMEDIATE_PASS enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::POTION enum value.
     */
    ObjectType returntype() const override;
};

#endif
