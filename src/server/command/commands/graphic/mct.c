/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include "server/zappy_server.h"
#include "server/command.h"

int mct(UNUSED socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, true, 0) == ERROR)
        return (SUCCESS);
    for (int y = 0; y < game_info->map->height; y++)
        for (int x = 0; x < game_info->map->width; x++)
            send_tile_info(client, game_info, x, y);
    return (SUCCESS);
}