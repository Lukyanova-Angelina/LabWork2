/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Ruby.h
 * @brief Ruby currency class - premium version of gold.
 * 
 * Special currency that gives bonus gold and XP when collected.
 * More valuable than regular gold pieces.
 */
#ifndef RUBY_H
#define RUBY_H

#include "Gold.h"

/**
 * @class Ruby
 * @brief Premium currency that gives bonus rewards.
 * 
 * Inherits from Gold. Provides double gold and bonus XP when collected.
 * Special variant of currency with enhanced value.
 */
class Ruby: public Gold {
public:
    /**
     * @brief Constructs a Ruby with specified value.
     * @param pos Grid position.
     * @param amount Base value of the ruby.
     */
    Ruby(int pos, int amount);
    
    /**
     * @brief Gets display information for ruby.
     * @return DisplayInfo structure with ruby visualization.
     */
    DisplayInfo print() const override;
    
    /**
     * @brief Returns the object type identifier.
     * @return ObjectType::RUBY enum value.
     */
    ObjectType returntype() const override;
};

#endif
