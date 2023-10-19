/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>
#include <sys/time.h>
#include "server/map.h"
#include "server/client.h"

void init_client(client_t *client, int fd)
{
    if (client == NULL)
        return;
    client->fd = fd;
    client->commands[0] = NULL;
    timerclear(&client->timer);
    client->graphic = false;
    client->game_info.team_name = NULL;
    client->game_info.level = 1;
    client->game_info.x = 0;
    client->game_info.y = 0;
    client->game_info.orientation = NORTH;
    for (int i = 1; i < NB_RESSOURCES; i++)
        client->game_info.inventory[i] = 0;
    client->game_info.inventory[FOOD] = 10;
    client->game_info.elevation_ok = false;
    timerclear(&client->game_info.death_timer);
    client->next = NULL;
}

void free_client(client_t *client)
{
    if (client == NULL)
        return;
    close(client->fd);
    for (int i = 0; client->commands[i] != NULL; i++)
        free(client->commands[i]);
    if (client->game_info.team_name)
        free(client->game_info.team_name);
    free(client);
}

client_t *add_client(client_t *clients, int fd)
{
    client_t *new_client = malloc(sizeof(client_t));

    if (clients == NULL)
        return (NULL);
    if (new_client == NULL) {
        perror("malloc");
        return (NULL);
    }
    init_client(new_client, fd);
    while (clients->next != NULL)
        clients = clients->next;
    clients->next = new_client;
    return (new_client);
}

void remove_client(client_t *clients, int fd)
{
    client_t *tmp;

    if (clients == NULL)
        return;
    while (clients->next && clients->next->fd != fd)
        clients = clients->next;
    if (clients->next) {
        tmp = clients->next;
        clients->next = clients->next->next;
        free_client(tmp);
    }
}

void clear_list(client_t *clients)
{
    client_t *tmp;

    if (clients == NULL)
        return;
    for (client_t *client = clients->next; client; client = tmp) {
        tmp = client->next;
        free_client(client);
    }
    clients->next = NULL;
}