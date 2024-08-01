//
// Created by samuel on 7/24/24.
//

#include <core/console_log.h>
#include <iostream>

#define CONSOLE_RED "\033[31m"
#define CONSOLE_WHITE "\033[0m"
#define CONSOLE_YELLOW "\033[33m"

ConsoleLogger::ConsoleLogger(const std::string &prefix): _prefix(prefix)
{

}

void ConsoleLogger::info(const std::string &msg) const {
    std::cout << CONSOLE_WHITE << "[" << _prefix << " - INFO] " << msg << std::endl;
}



void ConsoleLogger::warn(const std::string &msg) const {
    std::cout << CONSOLE_YELLOW << "[" << _prefix << " - WARNING] " << msg << std::endl;
}

void ConsoleLogger::error(const std::string &msg) const {
    std::cout << CONSOLE_RED << "[" << _prefix << " - ERROR] " << msg << std::endl;
}


