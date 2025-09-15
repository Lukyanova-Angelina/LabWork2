/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Chest.h
 * @brief Chest container class with randomized loot.
 * 
 * Interactive containers that generate random loot when activated.
 * Can be either good chests (positive items) or bad chests (negative items).
 */
#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "Status.h"

class Status;

/**
 * @class Chest
 * @brief Container object that generates random loot when opened.
 * 
 * Inherits from Object. Comes in two variants: good chests (helpful items)
 * and bad chests (harmful items). Generates loot based on game status.
 */
class Chest: public Object {
private:
    ChestType _Type;    ///< Type of chest (good or bad)

public:
    /**
     * @brief Constructs a Chest with specified type.
     * @param pos Grid position.
     * @param type Chest type (GOODCHEST or BADCHEST).
     */
    Chest(int pos, ChestType type);
    
    /**
     * @brief Gets the chest type.
     * @return ChestType enum value.
     */
    ChestType getChestType() const;
    
    /**
     * @brief Gets display information for the chest.
     * @return DisplayInfo structure indicating chest type.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::CHEST enum value.
     */
    ObjectType returntype() const override;
    
    /**
     * @brief Returns the interaction type.
     * @return InteractionType::TRIGGER_ON_STAY enum value.
     */
    InteractionType returnInteractionType() const override;
    
    /**
     * @brief Generates random loot based on chest type and game status.
     * @param status Reference to game status for loot generation.
     * @return Unique pointer to generated loot object.
     */
    std::unique_ptr<Object> generateLoot(const Status& status) const;
};

#endif
