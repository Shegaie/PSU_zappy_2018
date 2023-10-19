/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"
#include "server/tools.h"

void move_player(client_t *client, int x, int y, game_info_t game_info)
{
    client->game_info.x = increment_number(client->game_info.x, 0,
        game_info->map->width, x);
    client->game_info.y = increment_number(client->game_info.y, 0,
        game_info->map->height, y);
}

void forward_player(client_t *client, game_info_t game_info)
{
    orientation_t orientation = client->game_info.orientation;

    move_player(client, (orientation == EAST || orientation == WEST) ?
            ((orientation == EAST) ? 1 : -1) : 0,
        (orientation == NORTH || orientation == SOUTH) ?
            ((orientation == NORTH) ? 1 : -1) : 0, game_info);
}

int forward(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    forward_player(client, game_info);
    send_player_pos(socket, client);
    dprintf(client->fd, "ok\n");
    return (SUCCESS);
}