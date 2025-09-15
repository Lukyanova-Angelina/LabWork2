/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
/**
 * @file Colors.h
 * @brief ANSI color codes for terminal UI styling.
 * 
 * Provides color constants for consistent UI presentation across
 * different game elements and visual feedback.
 */
#ifndef COLORS_H
#define COLORS_H

#include <string>

/**
 * @namespace Color
 * @brief ANSI color codes for terminal text formatting.
 * 
 * Contains foreground and background color codes for UI elements.
 * All codes include reset sequence to prevent color bleeding.
 */
namespace Color {
    // Foreground colors
    const std::string RED = "\033[31m";         ///< Red text
    const std::string GREEN = "\033[32m";       ///< Green text  
    const std::string YELLOW = "\033[33m";      ///< Yellow text
    const std::string BLUE = "\033[34m";        ///< Blue text
    const std::string MAGENTA = "\033[35m";     ///< Magenta text
    const std::string CYAN = "\033[36m";        ///< Cyan text
    const std::string WHITE = "\033[37m";       ///< White text
    
    // Background colors
    const std::string BGRED = "\033[41m";       ///< Red background
    const std::string BGGREEN = "\033[42m";     ///< Green background
    const std::string BGYELLOW = "\033[43m";    ///< Yellow background
    const std::string BGBLUE = "\033[44m";      ///< Blue background
    const std::string BGMAGENTA = "\033[45m";   ///< Magenta background
    const std::string BGCYAN = "\033[46m";      ///< Cyan background
    const std::string BGWHITE = "\033[47m";     ///< White background
    
    const std::string RESET = "\033[0m";        ///< Reset all formatting
}

#endif
