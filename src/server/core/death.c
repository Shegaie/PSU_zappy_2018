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

void manage_player_food(socket_t socket, client_t *client, int freq,
    client_t **clients)
{
    int fd;

    if (is_time_elapsed(&client->game_info.death_timer, 126.0f / (float)freq) ==
        true) {
        if (client->game_info.inventory[FOOD] == 0) {
            dprintf(client->fd, "dead\n");
            kill_player(socket, client->fd);
            FD_CLR(client->fd, &socket->clients_fd);
            fd = client->fd;
            *clients = client->next;
            remove_client(&socket->client_list, fd);
        } else {
            client->game_info.inventory[FOOD]--;
            gettimeofday(&client->game_info.death_timer, NULL);
            *clients = client->next;
        }
    } else
        *clients = client->next;
}

void check_players_death(socket_t socket, int freq)
{
    for (client_t *client = socket->client_list.next; client;) {
        if (client->game_info.team_name != NULL) {
            manage_player_food(socket, client, freq, &client);
        } else
            client = client->next;
    }
}