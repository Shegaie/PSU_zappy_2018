/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>
#include "server/zappy_server.h"
#include "server/command.h"

void send_enw(client_t *client, egg_t *egg)
{
    dprintf(client->fd, "enw %d %d %d %d\n", egg->id, egg->player, egg->x,
        egg->y);
}

void send_graphic_enw(socket_t socket, egg_t *egg)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            send_enw(client, egg);
    }
}

int add_egg(team_t *team, client_t *player, game_info_t game_info,
    socket_t socket)
{
    egg_t *new_egg = malloc(sizeof(egg_t));
    egg_t *egg = NULL;

    if (new_egg == NULL)
        return (ERROR);
    *new_egg = (egg_t){game_info->nb_eggs, player->fd, player->game_info.x,
        player->game_info.y, rand() % 4 + 1, {0, 0}, false, NULL};
    game_info->nb_eggs++;
    gettimeofday(&new_egg->timer, NULL);
    if (team->eggs == NULL)
        team->eggs = new_egg;
    else {
        for (egg = team->eggs; egg->next; egg = egg->next);
        egg->next = new_egg;
    }
    send_graphic_enw(socket, new_egg);
    return (SUCCESS);
}

void send_pfk(socket_t socket, int player_fd)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "pfk %d\n", player_fd);
    }
}

int lay_egg(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    int i = 0;

    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    while (strcmp(game_info->teams[i].name, client->game_info.team_name) != 0)
        i++;
    if (add_egg(&game_info->teams[i], client, game_info, socket) == ERROR)
        return (ERROR);
    dprintf(client->fd, "ok\n");
    send_pfk(socket, client->fd);
    return (SUCCESS);
}