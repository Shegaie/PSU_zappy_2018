/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/
#include <string>
#include <iostream>
#include "CommandHandler.hpp"

void CommandHandler::parseCommand(std::string command, std::string separator)
{
    size_t pos = 0;
    std::string token;

    std::cout << command;
    while ((pos = command.find(separator)) != std::string::npos) {
        token = command.substr(0, pos);
        mutex.lock();
        stack->push_back(token);
        mutex.unlock();
        command.erase(0, pos + separator.length());
    }
}

std::unique_ptr<std::vector<std::string>> &CommandHandler::getStack()
{
    return stack;
}

void CommandHandler::popStack()
{
    mutex.lock();
    stack->erase(stack->begin());
    mutex.unlock();
}
