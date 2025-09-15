/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

/**
 * @file ELmagic.h
 * @brief Elemental magic wand weapon class.
 * 
 * Special weapon that deals elemental damage and has complex elemental interactions, can attack card behind enemy.
 * Can heal Elemental enemy or another magic wand when hit with same element or take double damage from opposite element.
 */
#ifndef ELMAGIC_H
#define ELMAGIC_H

#include "Weapon.h"

/**
 * @class ELmagic
 * @brief Elemental magic wand with complex damage calculations.
 * 
 * Inherits from Weapon and adds elemental damage type system.
 * Features damage modifiers based on elemental interactions.
 */
class ELmagic: public Weapon {
private:
    DamageType _Type; ///< Elemental type of the magic wand

public:
    /**
     * @brief Constructs an ELmagic with random damage and specified element.
     * @param pos Grid position.
     * @param el Elemental type (FIRE or ICE).
     */
    ELmagic(int pos, DamageType el); 
    
    /**
     * @brief Constructs an ELmagic with specified damage and element.
     * @param pos Grid position.
     * @param damage Initial damage value.
     * @param el Elemental type (FIRE or ICE).
     */
    ELmagic(int pos, int damage, DamageType el);
    
    /**
     * @brief Gets display information including elemental type.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::ELMAGIC enum value.
     */
    ObjectType returntype() const override;
    
    /**
     * @brief Gets the elemental type of the magic wand.
     * @return DamageType enum value (FIRE or ICE).
     */
    DamageType getElement()const;
    
    /**
     * @brief Creates a copy of the magic wand.
     * @return Unique pointer to cloned ELmagic.
     */
    std::unique_ptr<Object> clone() const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::IMMEDIATE_PASS enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Calculates final damage with elemental interactions.
     * @param dmg Base damage amount.
     * @param type Type of damage being applied.
     * @return Final damage after elemental calculations.
     */
    int calculateFinalDamage(int dmg, DamageType type) override;

};

#endif
