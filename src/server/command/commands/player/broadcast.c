/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

int broadcast(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, false, 1) == ERROR)
        return (SUCCESS);
    for (client_t *player = socket->client_list.next; player;
    player = player->next) {
        if (player->graphic)
            dprintf(player->fd, "pbc %d %s\n", client->fd, args[0]);
        else if (player->fd != client->fd && player->game_info.team_name)
            dprintf(player->fd, "message %d, %s\n",
                get_direction(game_info, client, player), args[0]);
    }
    dprintf(client->fd, "ok\n");
    return (SUCCESS);
}