/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"

void send_pnw(client_t *client, client_t *new_player)
{
    dprintf(client->fd, "pnw %d %d %d %d %d %s\n", new_player->fd,
        new_player->game_info.x, new_player->game_info.y,
        new_player->game_info.orientation, new_player->game_info.level,
        new_player->game_info.team_name);
}

void send_graph_pnw(socket_t socket, client_t *new_player)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            send_pnw(client, new_player);
    }
}