/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Characters.h
 * @brief Base class for all characters in the game (Player and Enemy).
 * 
 * Extends Object class with health management, damage calculation, and character-specific properties.
 * Provides foundation for player and enemies.
 */
#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Object.h"
#include "Weapon.h"

/**
 * @class Character
 * @brief Base class for all characters with health and combat capabilities.
 * 
 * Inherits from Object and adds health management, damage calculation,
 * and character-specific properties like name and health points.
 */
class Character: public Object {
private:
    std::string _Name;   ///< Name of the character
    int _HP;            ///< Current health points
    int _MAX_HP;        ///< Maximum health points

public:
    /**
     * @brief Default constructor.
     * Creates a character with default values.
     */
    Character();
    
    /**
     * @brief Parameterized constructor.
     * @param pos Initial position on the grid.
     * @param name Name of the character.
     * @param hp Current health points.
     * @param maxhp Maximum health points.
     */
    Character(int pos, std::string name, int hp, int maxhp);

    /**
     * @brief Gets the character's name.
     * @return Character's name as string.
     */
    std::string getName() const;
    
    /**
     * @brief Gets current health points.
     * @return Current HP value.
     */
    int getHP() const;
    
    /**
     * @brief Gets maximum health points.
     * @return Maximum HP value.
     */
    int getMaxHP() const;

    /**
     * @brief Sets the character's name.
     * @param name for the Character.
     */
    void setName(const std::string& name);
    
    /**
     * @brief Sets current health points.
     * @param hp New HP value.
     */
    void setHP(int hp);
    
    /**
     * @brief Sets maximum health points.
     * @param maxhp New maximum HP value.
     */
    void setMaxHP(int maxhp);
    
    /**
     * @brief Reduces character's health by specified amount.
     * @param hp Amount of health to subtract.
     */
    void takeHP(int hp);
    
    /**
     * @brief Gets display information for UI rendering.
     * @return DisplayInfo structure with character status.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Applies damage from a weapon.
     * @param o Pointer to the weapon dealing damage.
     * 
     * Reduces character's HP by weapon damage and triggers damage callback.
     * Also applies damage to the weapon based on damage dealt.
     */
    virtual void takeDamage(Weapon* o);
    
    /**
     * @brief Applies damage with specified type.
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     * 
     * Calculates final damage considering type,
     * reduces HP, and triggers damage callback.
     */
    void takeDamage(int dmg, DamageType type) override;
    
    /**
     * @brief Calculates final damage after applying type modifiers.
     * @param dmg Base damage amount.
     * @param type Type of damage being applied.
     * @return Final damage amount after modifications.
     * 
     * Base implementation returns unmodified damage. 
     */
    virtual int calculateFinalDamage(int dmg, DamageType type);
};

#endif
