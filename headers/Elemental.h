/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Elemental.h
 * @brief Elemental enemy class with complex elemental interactions.
 * 
 * Enemy with elemental affinity that has special damage reactions
 * to different elemental attacks. Can heal or take bonus damage.
 */
#ifndef ELEMENTAL_H
#define ELEMENTAL_H

#include "Enemy.h"
#include "ELmagic.h"

/**
 * @class Elemental
 * @brief Elemental enemy with damage type interactions.
 * 
 * Inherits from Enemy. Has FIRE or ICE affinity and reacts differently
 * to elemental attacks. Can heal from same element or take double damage from opposite.
 */
class Elemental : public Enemy {
private:
    DamageType _Type; ///< Elemental affinity (FIRE or ICE)

public:
    /**
     * @brief Constructs an Elemental with specified health and element.
     * @param pos Grid position.
     * @param hp Health points.
     * @param type Elemental affinity (FIRE or ICE).
     */
    Elemental(int pos, int hp, DamageType type);
    
    /**
     * @brief Gets display information including elemental type.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::ELEMENTAL enum value.
     */
    ObjectType returntype()const override;
    
    /**
     * @brief Gets the elemental affinity.
     * @return DamageType enum value (FIRE or ICE).
     */
    DamageType getElement() const;
    
    /**
     * @brief Takes damage from weapon with elemental calculations.
     * @param o Pointer to weapon dealing damage.
     */
    void takeDamage(Weapon* o) override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::COMBAT_DEPENDENT enum value.
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
