/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Player.h
 * @brief Player character class with weapon management capabilities.
 * 
 * Extends Character class with weapon handling functionality for combat.
 * Represents the player-controlled character in the game.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "Characters.h"
#include "Weapon.h"
#include "ELmagic.h"
#include "ELweapon.h"
#include <memory>

/**
 * @class Player
 * @brief Player character with weapon equipment system.
 * 
 * Inherits from Character and adds weapon management for combat interactions.
 * Handles weapon equipping, removal, and display information.
 */
class Player : public Character {
private:
    std::unique_ptr<Weapon> _weapon; ///< Currently equipped weapon

public:
    /**
     * @brief Constructs a Player with specified parameters.
     * @param pos Grid position.
     * @param name Character name.
     * @param hp Health points.
     * @param maxhp Maximum health points.
     */
    Player(int pos, std::string name, int hp, int maxhp); 
    
    /**
     * @brief Constructs a Player with default parameters.
     * @param pos Grid position.
     */
    Player(int pos);
    
    /**
     * @brief Virtual destructor for proper cleanup.
     */
    virtual ~Player() override;
    
    /**
     * @brief Gets the currently equipped weapon.
     * @return Pointer to equipped weapon or nullptr if none.
     */
    Weapon* getWeapon() const;
    
    /**
     * @brief Equips a weapon.
     * @param weapon Unique pointer to weapon to equip.
     */
    void setWeapon(std::unique_ptr<Weapon> weapon);
    
    /**
     * @brief Removes currently equipped weapon.
     */
    void removeWeapon();
    
    /**
     * @brief Gets display information including weapon status.
     * @return DisplayInfo structure for UI rendering.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::PLAYER enum value.
     */
    ObjectType returntype()const override;
};

#endif
