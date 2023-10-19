/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"
#include "server/tools.h"

void send_inventory(client_t *client, client_t *player)
{
    int *inventory = player->game_info.inventory;

    dprintf(client->fd, "pin %d %d %d %d %d %d %d %d %d %d\n", player->fd,
        player->game_info.x, player->game_info.y, inventory[FOOD],
        inventory[LINEMATE], inventory[DERAUMERE], inventory[SIBUR],
        inventory[MENDIANE], inventory[PHIRAS], inventory[THYSTAME]);
}

void send_pin_graphic(socket_t socket, client_t *player)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            send_inventory(client, player);
    }
}

int pin(socket_t socket, UNUSED game_info_t game_info, client_t *client,
    char **args)
{
    client_t *player;
    int player_nb;

    if (command_parser(args, client, true, 1) == ERROR)
        return (SUCCESS);
    player_nb = get_nbr(args[0]);
    if (player_nb == ERROR) {
        dprintf(client->fd, "sbp\n");
        return (SUCCESS);
    }
    for (player = socket->client_list.next; player; player = player->next) {
        if (player->fd == player_nb) {
            send_inventory(client, player);
            return (SUCCESS);
        }
    }
    dprintf(client->fd, "sbp\n");
    return (SUCCESS);
}