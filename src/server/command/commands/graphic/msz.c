/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

int msz(UNUSED socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, true, 0) == ERROR)
        return (SUCCESS);
    dprintf(client->fd, "msz %d %d\n", game_info->map->width,
        game_info->map->height);
    return (SUCCESS);
}