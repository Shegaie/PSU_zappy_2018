/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by lgregoire,
*/

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "ZappyGraphic/ZappyGraphic.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cout << "USAGE\n\t./graphical server_ip port" << std::endl;
        return 0;
    } else {
        ZappyGraphic graph;
        graph.start(av[1], static_cast<uint16_t>(std::stoi(av[2])));
    }
}