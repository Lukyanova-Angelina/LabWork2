/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Object.h
 * @brief Base class for all game objects in the game.
 * 
 * Provides core functionality for position management, movement, interaction,
 * damage handling, and UI representation. All game entities inherit from this class.
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include "Colors.h"
#include "Enums.h"

/**
 * @struct DisplayInfo
 * @brief Contains information for rendering an object in the game UI.
 */
struct DisplayInfo {
    std::string header;      ///< Main title/name of the object
    std::string status;      ///< Current status information (e.g., health, damage)
    std::string details;     ///< Additional descriptive details
    std::string color;       ///< Color code for UI representation
};

// Utility functions for text formatting in UI
std::string centerText(const std::string& text, size_t width);
std::string leftAlign(const std::string& text, size_t width, char fill = ' ');

/**
 * @class Object
 * @brief Abstract base class representing any entity in the game world.
 * 
 * Stores position on a 3x3 grid, provides movement capabilities, interaction handling,
 * and a callback system for damage events. Serves as the foundation for all game entities.
 */
class Object {
private:
    int _POSITION; ///< Current position on the 3x3 grid (0-8)

protected:
    std::function<void(int, DamageType)> OnDamageCallback; ///< Callback for damage events

public:
    /**
     * @brief Constructs an Object at the specified position.
     * @param pos Initial position on the 3x3 grid (0-8).
     */
    Object(int pos);
    
    /**
     * @brief Virtual destructor for proper polymorphic destruction.
     * Removes any active damage callback.
     */
    virtual ~Object();
    
    /**
     * @brief Display information for UI rendering.
     * @return DisplayInfo structure with object representation data.
     */
    virtual DisplayInfo print() const;
    
    /**
     * @brief Returns the type of this object.
     * @return ObjectType enum value identifying the object type.
     */
    virtual ObjectType returntype() const;
    
    /**
     * @brief Defines how this object interacts with others.
     * @return InteractionType enum value specifying interaction behavior.
     */
    virtual InteractionType returnInteractionType() const;
    
    /**
     * @brief Creates a copy of this object.
     * @return std::unique_ptr<Object> pointing to the cloned object.
     */
    virtual std::unique_ptr<Object> clone() const;
    
    /**
     * @brief Updates object state (called each game step).
     * Base implementation does nothing - override for custom behavior.
     */
    virtual void update();
    
    /**
     * @brief Gets the current grid position.
     * @return Integer position (0-8) on the 3x3 grid.
     */
    int getPosition() const;
    
    /**
     * @brief Sets the object's grid position.
     * @param pos New position (0-8) on the 3x3 grid.
     */
    void setPosition(int pos);
    
    /**
     * @brief Moves the object in the specified direction.
     * @param direction Movement direction (0=up, 1=right, 2=down, 3=left).
     * Only moves if the movement is valid within grid boundaries.
     */
    void move(int direction);
    
    /**
     * @brief Checks if movement in a direction is possible.
     * @param direction Direction to check (0=up, 1=right, 2=down, 3=left).
     * @return true if movement is valid, false otherwise.
     */
    bool possibletomove(int direction);
    
    /**
     * @brief Calculates target position for a movement direction.
     * @param direction Movement direction (0=up, 1=right, 2=down, 3=left).
     * @return Target position if valid, -1 if movement would go off-grid.
     */
    int getTargetPosition(int direction) const;
    
    /**
     * @brief Calculates direction to reach a target position.
     * @param pos2 Target position to reach.
     * @return Direction (0=up, 1=right, 2=down, 3=left) or -1 if not adjacent.
     */
    int getTargetDirection(int pos2) const;
    
    /**
     * @brief Applies damage to the object.
     * @param dmg Amount of damage to apply.
     * @param type Type of damage being applied.
     * Triggers the OnDamageCallback if set.
     */
    virtual void takeDamage(int dmg, DamageType type);
    
    /**
     * @brief Sets a callback function for damage events.
     * @param callback Function to call when damage is taken.
     * The callback receives (position, damageType) parameters.
     */
    void setOnDamageCallback(std::function<void(int, DamageType)> callback);
    
    /**
     * @brief Removes the current damage callback.
     */
    void removeCallback();
};

#endif
