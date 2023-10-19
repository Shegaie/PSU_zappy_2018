/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

void send_pex(socket_t socket, int fd)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "pex %d\n", fd);
    }
}

void eject_player(client_t *player, game_info_t game, orientation_t orientation)
{
    move_player(player, (orientation == EAST || orientation == WEST) ?
            ((orientation == EAST) ? 1 : -1) : 0,
        (orientation == NORTH || orientation == SOUTH) ?
            ((orientation == NORTH) ? 1 : -1) : 0, game);
}

int eject(socket_t socket, game_info_t game_info, client_t *client, char **args)
{
    bool ok = false;

    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    for (client_t *player = socket->client_list.next; player;
    player = player->next) {
        if (player->game_info.x == client->game_info.x &&
            player->game_info.y == client->game_info.y && player != client) {
            eject_player(player, game_info, client->game_info.orientation);
            send_player_pos(socket, player);
            dprintf(player->fd, "eject: %d\n",
                get_direction(game_info, client, player));
            ok = true;
        }
    }
    if (ok)
        send_pex(socket, client->fd);
    dprintf(client->fd, (ok) ? "ok\n" : "ko\n");
    return (SUCCESS);
}