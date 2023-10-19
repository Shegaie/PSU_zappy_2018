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

int sst(UNUSED socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    int new_freq;

    if (command_parser(args, client, true, 1) == ERROR)
        return (SUCCESS);
    new_freq = get_nbr(args[0]);
    if (new_freq >= 2 && new_freq <= 10000) {
        game_info->freq = new_freq;
        dprintf(client->fd, "sst %d\n", game_info->freq);
    } else
        dprintf(client->fd, "sbp\n");
    return (SUCCESS);
}