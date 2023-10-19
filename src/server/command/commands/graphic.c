/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"

void get_players(socket_t socket, client_t *new_graph_client)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->game_info.team_name != NULL)
            send_pnw(new_graph_client, client);
    }
}

void send_eggs_info(game_info_t game_info, client_t *client)
{
    for (int i = 0; i < game_info->nb_teams; i++) {
        for (egg_t *egg = game_info->teams[i].eggs; egg; egg = egg->next) {
            send_enw(client, egg);
        }
    }
}

int graphic(socket_t socket, game_info_t game_info, client_t *client,
    UNUSED char **args)
{
    if (client->graphic || client->game_info.team_name)
        dprintf(client->fd, "ko\n");
    else {
        client->graphic = true;
        msz(socket, game_info, client, (char **){NULL});
        sgt(socket, game_info, client, (char **){NULL});
        mct(socket, game_info, client, (char **){NULL});
        tna(socket, game_info, client, (char **){NULL});
        get_players(socket, client);
        send_eggs_info(game_info, client);
    }
    return (SUCCESS);
}