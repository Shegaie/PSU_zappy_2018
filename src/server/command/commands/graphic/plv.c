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

int plv(socket_t socket, UNUSED game_info_t game_info, client_t *client,
    char **args)
{
    client_t *player;
    int player_nb;

    if (command_parser(args, client, true, 1) == ERROR)
        return (SUCCESS);
    player_nb = get_nbr(args[0]);
    if (player_nb == ERROR) {
        dprintf(client->fd, "sbp\n");
        return (SUCCESS);
    }
    for (player = socket->client_list.next; player; player = player->next) {
        if (player->fd == player_nb) {
            dprintf(client->fd, "plv %d %d\n", player->fd,
                player->game_info.level);
            return (SUCCESS);
        }
    }
    dprintf(client->fd, "sbp\n");
    return (SUCCESS);
}