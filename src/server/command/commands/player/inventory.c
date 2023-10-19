/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"
#include "server/ressources.h"

int inventory(UNUSED socket_t socket, UNUSED game_info_t game_info,
    client_t *client, char **args)
{
    int *inventory = client->game_info.inventory;

    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    dprintf(client->fd, "[ %s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d ]\n",
        RESSOURCES_NAME[FOOD], inventory[FOOD],
        RESSOURCES_NAME[LINEMATE], inventory[LINEMATE],
        RESSOURCES_NAME[DERAUMERE], inventory[DERAUMERE],
        RESSOURCES_NAME[SIBUR], inventory[SIBUR],
        RESSOURCES_NAME[MENDIANE], inventory[MENDIANE],
        RESSOURCES_NAME[PHIRAS], inventory[PHIRAS],
        RESSOURCES_NAME[THYSTAME], inventory[THYSTAME]);
    return (SUCCESS);
}