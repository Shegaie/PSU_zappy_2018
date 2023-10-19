/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

void send_graph_plv(socket_t socket, client_t *player)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "plv %d %d\n", player->fd,
                player->game_info.level);
    }
}

void send_graph_pie(socket_t socket, client_t *player, bool result)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "pie %d %d %d\n", player->game_info.x,
                player->game_info.y, result);
    }
}

void send_graph_seg(socket_t socket, char *team)
{
    for (client_t *client = socket->client_list.next; client;
        client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "seg %s\n", team);
    }
}

void inc_levels(socket_t socket, client_t *client)
{
    for (client_t *player = socket->client_list.next; player;
    player = player->next) {
        if (player->game_info.team_name &&
            player->game_info.level == client->game_info.level &&
            player->game_info.x == client->game_info.x &&
            player->game_info.y == client->game_info.y)
            player->game_info.level++;
    }
}

int incantation(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    if (client->game_info.elevation_ok == true &&
        allow_elevation(socket, game_info, client) == true) {
        inc_levels(socket, client);
        dprintf(client->fd, "Current level: %d\n", client->game_info.level);
        send_graph_plv(socket, client);
        send_graph_pie(socket, client, true);
        if (client->game_info.level == 8) {
            send_graph_seg(socket, client->game_info.team_name);
            socket->running = false;
        }
    } else {
        dprintf(client->fd, "ko\n");
        send_graph_pie(socket, client, false);
    }
    client->game_info.elevation_ok = false;
    return (SUCCESS);
}