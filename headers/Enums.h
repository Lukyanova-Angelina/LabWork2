/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Enums.h
 * @brief Centralized enumeration definitions for the game.
 * 
 * Contains all enum classes used throughout the game for type safety
 * and consistent behavior across different game systems.
 */
#ifndef ENUMS_H
#define ENUMS_H

/**
 * @enum DamageType
 * @brief Types of damage that can be applied in combat.
 * 
 * Used for elemental damage systems and resistance calculations.
 */
enum class DamageType {
    NORMAL, ///< Standard physical damage, no special properties
    FIRE,   ///< Fire elemental damage, interacts with ice
    ICE     ///< Ice elemental damage, interacts with fire
};

/**
 * @enum InteractionType
 * @brief Types of interactions between game objects.
 * 
 * Defines how objects behave when player interacts with them.
 */
enum class InteractionType {
    IMMEDIATE_PASS,     ///< Immediate effect when touched (items, gold)
    SWAP_REQUIRED,      ///< Requires swapping positions (bombs, dynamite)
    TRIGGER_ON_STAY,    ///< Activates when player stays on tile (chests)
    COMBAT_DEPENDENT    ///< Resolves through combat system (enemies)
};

/**
 * @enum ObjectType
 * @brief Types of all game objects for identification and casting.
 * 
 * Used for type checking, object creation, and special behavior handling.
 */
enum class ObjectType {
    OBJECT,     ///< Base empty object
    ENEMY,      ///< Basic enemy type
    ELEMENTAL,  ///< Elemental enemy
    MAG,        ///< Magician enemy with regeneration
    BAT,        ///< Bat enemy that drops potions
    WEAPON,     ///< Basic weapon
    ELMAGIC,    ///< Elemental magic wand with complex interactions
    ELWEAPON,   ///< Elemental weapon with charging
    GOLD,       ///< Gold currency
    RUBY,       ///< Premium currency with bonuses
    THORN,      ///< Rotating directional trap
    GUN,        ///< Weapon emplacement trap
    BOMB,       ///< Explosive (4-direction)
    DYNAMITE,   ///< Row-based explosive
    POTION,     ///< Consumable health/poison item
    CHEST,      ///< Loot container
    PLAYER      ///< Player character
};

/**
 * @enum ChestType
 * @brief Types of chests determining loot quality.
 */
enum class ChestType {
    BADCHEST,   ///< Chest containing harmful or dangerous items
    GOODCHEST   ///< Chest containing beneficial items
};

/**
 * @enum PotionType
 * @brief Types of potions determining their effect.
 */
enum class PotionType {
    POISON, ///< Damages the consumer
    HEAL    ///< Heals the consumer
};

#endif
