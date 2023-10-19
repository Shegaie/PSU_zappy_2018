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

int left(socket_t socket, UNUSED game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    client->game_info.orientation = increment_number(
        client->game_info.orientation, NORTH, WEST + 1, -1);
    send_player_pos(socket, client);
    dprintf(client->fd, "ok\n");
    return (SUCCESS);
}