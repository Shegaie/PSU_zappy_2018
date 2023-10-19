/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "server/zappy_server.h"
#include "server/command.h"
#include "server/tools.h"
#include "server/incantation.h"

int add_player(char **players_string, client_t *client, client_t *player)
{
    char *copy = NULL;

    if (client->game_info.x == player->game_info.x &&
        client->game_info.y == player->game_info.y &&
        player->fd != client->fd) {
        *players_string = realloc(*players_string,
            (strlen(*players_string) + intlen(client->fd) + 2) * sizeof(char));
        if (*players_string == NULL)
            return (ERROR);
        copy = strdup(*players_string);
        if (copy == NULL)
            return (ERROR);
        sprintf(*players_string, "%s %d", copy, client->fd);
        free(copy);
    }
    return (SUCCESS);
}

int send_graphic_pic(socket_t socket, client_t *player)
{
    char *players_string = malloc((intlen(player->fd) + 1) * sizeof(char));

    if (players_string == NULL)
        return (ERROR);
    sprintf(players_string, "%d", player->fd);
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->game_info.team_name &&
            add_player(&players_string, client, player) == ERROR)
            return (ERROR);
    }
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "pic %d %d %d %s\n", player->game_info.x,
                player->game_info.y, player->game_info.level, players_string);
    }
    free(players_string);
    return (SUCCESS);
}

bool allow_elevation(socket_t socket, game_info_t game_info, client_t *client)
{
    elevation_params_t params = ELEVATION_PARAMS[client->game_info.level - 1];
    struct tile_s tile = game_info->map->tiles
        [client->game_info.y][client->game_info.x];
    int players = 0;

    if (client->game_info.level == 8)
        return (false);
    for (int i = 0; i < NB_RESSOURCES - 1; i++)
        if (tile.ressources[i + 1] < params.ressources[i])
            return (false);
    for (client_t *player = socket->client_list.next; player;
    player = player->next)
        if (player->game_info.team_name &&
            player->game_info.level == client->game_info.level &&
            player->game_info.x == client->game_info.x &&
            player->game_info.y == client->game_info.y)
            players++;
    if (players < params.nb_players)
        return (false);
    return (true);
}

void check_incant(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (client->graphic == false && timerisset(&client->timer) == 0 &&
        strcmp(args[0], "Incantation") == 0 &&
        command_parser(&args[1], client, false, 0) != ERROR) {
        if (allow_elevation(socket, game_info, client) == true) {
            dprintf(client->fd, "Elevation underway\n");
            client->game_info.elevation_ok = true;
        } else
            dprintf(client->fd, "ko\n");
        send_graphic_pic(socket, client);
    }
}