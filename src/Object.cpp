/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

/**
 * @file Object.cpp
 * @brief Implementation of the Object base class methods.
 */
#include "Object.h"

Object::Object(int pos) : _POSITION(pos) {}

Object::~Object() {
    removeCallback();
}

DisplayInfo Object::print() const {
    return {
        "Object",
        "",
        "",
        Color::BLUE
    };
}

std::unique_ptr<Object> Object::clone() const {
    return std::make_unique<Object>(*this);
}

int Object::getPosition() const {
    return _POSITION;
}

void Object::setPosition(int pos) {
    _POSITION = pos;
}

ObjectType Object::returntype() const {
    return ObjectType::OBJECT;
}

InteractionType Object::returnInteractionType() const {
    return InteractionType::IMMEDIATE_PASS;
}

/**
 * @brief Handles movement within 3x3 grid boundaries.
 * @param direction Movement direction (0=up, 1=right, 2=down, 3=left).
 */
void Object::move(int direction) {
    if (direction == 0 && getPosition() > 2) {
        setPosition(getPosition() - 3);
    } else if (direction == 1 && getPosition() % 3 != 2) {
        setPosition(getPosition() + 1);
    } else if (direction == 3 && getPosition() % 3 != 0) {
        setPosition(getPosition() - 1);
    } else if (direction == 2 && getPosition() < 6) {
        setPosition(getPosition() + 3);
    }
}

/**
 * @brief Calculates target position for movement direction.
 * @param direction Direction to check (0=up, 1=right, 2=down, 3=left).
 * @return Target position or -1 if movement is invalid.
 */
int Object::getTargetPosition(int direction) const {
    switch (direction) {
        case 0:
            if ((getPosition() - 3) >= 0) { return getPosition() - 3; }
            return -1;
        case 1:
            if ((getPosition() + 1) / 3 == getPosition() / 3) { return getPosition() + 1; }
            return -1;
        case 2:
            if ((getPosition() + 3) <= 8) { return getPosition() + 3; }
            return -1;
        case 3:
            if ((getPosition() - 1) / 3 == getPosition() / 3) { return getPosition() - 1; }
            return -1;
        default:
            return -1;
    }
}

/**
 * @brief Calculates direction between two adjacent positions.
 * @param pos2 Target position to reach.
 * @return Direction to move or -1 if positions are not adjacent.
 */
int Object::getTargetDirection(int pos2) const {
    switch (getPosition() - pos2) {
        case 1: return 3;   // Left
        case -1: return 1;  // Right
        case 3: return 0;   // Up
        case -3: return 2;  // Down
        default: return -1; // Not adjacent
    }
}

bool Object::possibletomove(int direction) {
    if (direction == 0 && getPosition() > 2) {
        return true;
    } else if (direction == 1 && getPosition() % 3 != 2) {
        return true;
    } else if (direction == 3 && getPosition() % 3 != 0) {
        return true;
    } else if (direction == 2 && getPosition() < 6) {
        return true;
    }
    return false;
}

// Empty update method for game step processing
void Object::update() {}
/**
 * @brief Applies damage and triggers damage callback.
 * @param dmg Amount of damage to apply.
 * @param type Type of damage being applied.
 */
void Object::takeDamage(int dmg, DamageType type) {
    if (OnDamageCallback) {
        OnDamageCallback(getPosition(), type);
    }
}

/**
 * @brief Sets callback function for damage events.
 * @param callback Function to call when damage is taken.
 */
void Object::setOnDamageCallback(std::function<void(int, DamageType)> callback) {
    OnDamageCallback = callback;
}

/**
 * @brief Removes the current damage callback.
 */
void Object::removeCallback() {
    OnDamageCallback = nullptr;
}

/**
 * @brief Centers text with special handling for Unicode symbols.
 * @param text Text to center.
 * @param width Total width for centering.
 * @return Centered text string with proper Unicode symbol handling.
 */


std::string centerText(const std::string& text, size_t width) {
    if (text.empty()) {
        return std::string(width, ' ');
    }
    
    
    static const std::unordered_map<std::string, int> symbolCorrections = {
        {"→", -2},
        {"←", -2},
        {"↓", -2},
        {"↑", -2},
        {"▲", -2},
        {"◀", -2},
        {"▶", -2},
        {"▼", -2},
        {"⚔", -2}
    };
    
    size_t effectiveLength = text.length();
    
    for (const auto& [symbol, correction] : symbolCorrections) {
        if (text.find(symbol) != std::string::npos) {
            effectiveLength += correction;
        }
    }

    if (effectiveLength >= width) {
        return text.substr(0, width);
    }
    
    size_t leftPadding = (width - effectiveLength) / 2;
    size_t rightPadding = width - effectiveLength - leftPadding;
    
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}
/**
 * @brief Left-aligns text with padding.
 * @param text Text to align.
 * @param width Total width for alignment.
 * @param fill char to use for padding.
 * @return Left-aligned text string.
 */

std::string leftAlign(const std::string& text, size_t width, char fill) {
    if (text.length() >= width) {
        return text.substr(0, width);
    }
    return text + std::string(width - text.length(), fill);
}
