/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include <memory.h>
#include "server/zappy_server.h"
#include "server/command.h"

int get_team_places(socket_t socket, game_info_t game_info, char *team)
{
    int nb_players = 0;
    int nb_eggs = 0;
    int i = 0;

    for (i = 0; i < game_info->nb_teams; i++)
        if (strcmp(game_info->teams[i].name, team) == 0)
            break;
    if (i == game_info->nb_teams)
        return (ERROR);
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->game_info.team_name &&
            strcmp(client->game_info.team_name, team) == 0)
            nb_players++;
    }
    for (egg_t *egg = game_info->teams[i].eggs; egg; egg = egg->next)
        if (egg->hatched)
            nb_eggs++;
    return (((game_info->teams[i].team_size - nb_players < 0) ? 0 :
        game_info->teams[i].team_size - nb_players) + nb_eggs);
}

int connect_nbr(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    dprintf(client->fd, "%d\n",
        get_team_places(socket, game_info, client->game_info.team_name));
    return (SUCCESS);
}