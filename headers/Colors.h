#ifndef COLORS_H
#define COLORS_H

#include <string>

namespace Color {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BGRED = "\033[41m";
    const std::string BGGREEN = "\033[42m";
    const std::string BGYELLOW = "\033[43m";
    const std::string BGBLUE = "\033[44m";
    const std::string BGMAGENTA = "\033[45m";
    const std::string BGCYAN = "\033[46m";
    const std::string BGWHITE = "\033[47m";
    const std::string RESET = "\033[0m";
}

#endif