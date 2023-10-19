/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/
#ifndef GRAPHICAL_COMMANDHANDLER_HPP
#define GRAPHICAL_COMMANDHANDLER_HPP

#include <vector>
#include <memory>
#include <mutex>

class CommandHandler {
    public:
        void parseCommand(std::string command, std::string separator);
        std::unique_ptr<std::vector<std::string>> &getStack();
        void popStack();
    private:
        std::unique_ptr<std::vector<std::string>> stack = std::make_unique<std::vector<std::string>>();
        std::mutex mutex;
};

#endif //GRAPHICAL_COMMANDHANDLER_HPP
