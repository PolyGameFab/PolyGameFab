//
// Created by lapor on 7/26/2024.
//
#include <core/console_log.h>

#include <iostream>
#include <windows.h>


void setColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

ConsoleLogger::ConsoleLogger(const std::string &prefix): _prefix(prefix)
{

}

void ConsoleLogger::info(const std::string &msg) const {
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "[" << _prefix << " - INFO] " << msg << std::endl;
}



void ConsoleLogger::warn(const std::string &msg) const {
    setColor(FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout << "[" << _prefix << " - WARNING] " << msg << std::endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ConsoleLogger::error(const std::string &msg) const {
    setColor(FOREGROUND_RED);
    std::cout << "[" << _prefix << " - ERROR] " << msg << std::endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
