/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

/**
 * @file ELweapon.h
 * @brief Elemental weapon class with charged elemental damage.
 * Weapon that can be charged with elemental energy, providing damage bonuses.
 */
#ifndef ELWEAPON_H
#define ELWEAPON_H

#include "Weapon.h"

/**
 * @class ELweapon
 * @brief Elemental weapon with charged damage system.
 * 
 * Inherits from Weapon and adds elemental charging functionality.
 * Provides damage bonuses when hitting with correct element.
 */
class ELweapon: public Weapon {
private:
    DamageType _Type; ///< Charged elemental type

public:
    /**
     * @brief Constructs an ELweapon with random damage and specified element.
     * @param pos Grid position.
     * @param el Elemental type.
     */
    ELweapon(int pos, DamageType el); 
    
    /**
     * @brief Constructs an ELweapon with specified damage and element.
     * @param pos Grid position.
     * @param damage Initial damage value.
     * @param el Elemental type to charge with.
     */
    ELweapon(int pos, int damage, DamageType el);
    
    /**
     * @brief Gets display information including elemental charge.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Creates a copy of the elemental weapon.
     * @return Unique pointer to cloned ELweapon.
     */
    std::unique_ptr<Object> clone() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::ELWEAPON enum value.
     */
    ObjectType returntype() const override;
    
    /**
     * @brief Gets the charged elemental type.
     * @return DamageType enum value of the charge.
     */
    DamageType getElement()const;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::IMMEDIATE_PASS enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Calculates final damage with elemental charge bonuses.
     * @param dmg Base damage amount.
     * @param type Type of damage being applied.
     * @return Final damage after elemental calculations.
     */
    int calculateFinalDamage(int dmg, DamageType type) override;

};

#endif
