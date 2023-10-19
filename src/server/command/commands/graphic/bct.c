/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "server/command.h"

static int check_args(char **args, int *x, int *y, game_info_t game_info)
{
    *x = get_nbr(args[0]);
    *y = get_nbr(args[1]);
    if (*x == ERROR || *y == ERROR)
        return (ERROR);
    if (*x < 0 || *x >= game_info->map->width || *y < 0 ||
        *y >= game_info->map->height)
        return (ERROR);
    return (SUCCESS);
}

void send_tile_info(client_t *client, game_info_t game_info, int x, int y)
{
    int *ressources = game_info->map->tiles[y][x].ressources;

    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        ressources[FOOD], ressources[LINEMATE], ressources[DERAUMERE],
        ressources[SIBUR], ressources[MENDIANE], ressources[PHIRAS],
        ressources[THYSTAME]);
}

void send_bct_graphic(socket_t socket, game_info_t game_info, int x, int y)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            send_tile_info(client, game_info, x, y);
    }
}

int bct(UNUSED socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    int x;
    int y;

    if (command_parser(args, client, true, 2) == ERROR)
        return (SUCCESS);
    if (check_args(args, &x, &y, game_info) == ERROR)
        dprintf(client->fd, "sbp\n");
    else
        send_tile_info(client, game_info, x, y);
    return (SUCCESS);
}