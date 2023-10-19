/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

int tna(UNUSED socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, true, 0) == ERROR)
        return (SUCCESS);
    for (int i = 0; i < game_info->nb_teams; i++)
        dprintf(client->fd, "tna %s\n", game_info->teams[i].name);
    return (SUCCESS);
}