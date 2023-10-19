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
#include "server/ressources.h"

int get_ressource_index(char *name)
{
    int i = 0;

    while (i < NB_RESSOURCES && strcmp(RESSOURCES_NAME[i], name) != 0)
        i++;
    if (i == NB_RESSOURCES)
        return (-1);
    return (i);
}

void send_pgt(socket_t socket, int fd, int ressource)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "pgt %d %d\n", fd, ressource);
    }
}

int take(socket_t socket, game_info_t game_info, client_t *client, char **args)
{
    int *ressources;
    int index;

    if (command_parser(args, client, false, 1) == ERROR)
        return (SUCCESS);
    ressources = game_info->map->tiles
        [client->game_info.y][client->game_info.x].ressources;
    index = get_ressource_index(args[0]);
    if (index == -1 || ressources[index] == 0)
        dprintf(client->fd, "ko\n");
    else {
        client->game_info.inventory[index]++;
        ressources[index]--;
        send_pgt(socket, client->fd, index);
        send_pin_graphic(socket, client);
        send_bct_graphic(socket, game_info, client->game_info.x,
            client->game_info.y);
        dprintf(client->fd, "ok\n");
    }
    return (SUCCESS);
}