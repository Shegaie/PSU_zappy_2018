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
#include "server/tools.h"
#include "server/command.h"

void remove_first_egg(team_t *team)
{
    egg_t *tmp;

    tmp = team->eggs;
    if (tmp) {
        team->eggs = tmp->next;
        free(tmp);
    }
}

void send_graphic_ebo(socket_t socket, int id)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "ebo %d\n", id);
    }
}

void init_player(client_t *client, game_info_t game_info, socket_t socket)
{
    int i = 0;

    while (strcmp(game_info->teams[i].name, client->game_info.team_name) != 0)
        i++;
    if (game_info->teams[i].eggs && game_info->teams[i].eggs->hatched) {
        client->game_info.x = game_info->teams[i].eggs->x;
        client->game_info.y = game_info->teams[i].eggs->y;
        client->game_info.orientation = game_info->teams[i].eggs->orientation;
        send_graphic_ebo(socket, game_info->teams[i].eggs->id);
        remove_first_egg(&game_info->teams[i]);
    } else {
        client->game_info.x = rand() % game_info->map->width;
        client->game_info.y = rand() % game_info->map->height;
        client->game_info.orientation = rand() % 4 + 1;
    }
    gettimeofday(&client->game_info.death_timer, NULL);
}

int join_team(socket_t socket, game_info_t game_info, client_t *client,
    char *team)
{
    int places = get_team_places(socket, game_info, team);

    if (places > 0) {
        client->game_info.team_name = strdup(team);
        if (client->game_info.team_name == NULL) {
            perror("malloc");
            return (ERROR);
        }
        init_player(client, game_info, socket);
        dprintf(client->fd, "%d\n%d %d\n", places - 1, game_info->map->width,
            game_info->map->height);
        send_graph_pnw(socket, client);
        add_food(socket, game_info);
    } else
        dprintf(client->fd, "ko\n");
    return (SUCCESS);
}