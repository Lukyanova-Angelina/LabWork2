#ifndef ENUMS_H
#define ENUMS_H

enum class DamageType {
    NORMAL,
    FIRE,
    ICE
};

enum class InteractionType {
    IMMEDIATE_PASS,
    SWAP_REQUIRED,
    TRIGGER_ON_STAY,
    COMBAT_DEPENDENT
};

enum class ObjectType {
    OBJECT,
    ENEMY,
    ELEMENTAL,
    MAG,
    BAT,
    WEAPON,
    ELMAGIC,
    ELWEAPON,
    GOLD,
    RUBY,
    THORN,
    GUN,
    BOMB,
    DYNAMITE,
    POTION,
    CHEST,
    PLAYER
};

enum class ChestType {
    BADCHEST,
    GOODCHEST
};

enum class PotionType {
    POISON,
    HEAL
};

#endif