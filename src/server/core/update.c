/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include <sys/time.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/core.h"
#include "server/command.h"

void send_graphic_eht(socket_t socket, int id)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "eht %d\n", id);
    }
}

void check_egg_hatch(egg_t *egg, int freq, socket_t socket)
{
    if (!egg->hatched &&
        is_time_elapsed(&egg->timer, 600.0f / (float)freq) == true) {
        egg->hatched = true;
        send_graphic_eht(socket, egg->id);
    }
}

void check_eggs(game_info_t game_info, socket_t socket)
{
    for (int i = 0; i < game_info->nb_teams; i++) {
        for (egg_t *egg = game_info->teams[i].eggs; egg; egg = egg->next) {
            check_egg_hatch(egg, game_info->freq, socket);
        }
    }
}

void update_game(socket_t socket, game_info_t game_info)
{
    check_players_death(socket, game_info->freq);
    check_eggs(game_info, socket);
}