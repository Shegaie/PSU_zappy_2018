/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

void add_food_randomly(socket_t socket, game_info_t game_info, int x, int y)
{
    if (add_ressource_randomly(&game_info->map->tiles[y][x], FOOD, 40))
        send_bct_graphic(socket, game_info, x, y);
}

void add_food(socket_t socket, game_info_t game_info)
{
    map_t map;

    if (socket == NULL || game_info == NULL)
        return;
    map = game_info->map;
    for (int i = 0; map->tiles[i] != NULL; i++) {
        for (int j = 0; j < map->width; j++) {
            add_food_randomly(socket, game_info, j, i);
        }
    }
}