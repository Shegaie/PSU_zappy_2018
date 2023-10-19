/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <zconf.h>
#include <stdio.h>
#include "server/zappy_server.h"
#include "server/command.h"
#include "server/parse.h"
#include "server/core.h"

int connect_new_clients(socket_t socket)
{
    int new_client;

    new_client = accept(socket->socket_fd, NULL, NULL);
    if (new_client == -1) {
        perror("accept");
        return (ERROR);
    }
    if (!add_client(&socket->client_list, new_client))
        return (ERROR);
    FD_SET(new_client, &socket->clients_fd);
    socket->max_fd = MAX(socket->max_fd, new_client);
    dprintf(new_client, "WELCOME\n");
    return (SUCCESS);
}

void kill_player(socket_t socket, int player_nb)
{
    for (client_t *client = socket->client_list.next; client;
    client = client->next) {
        if (client->graphic)
            dprintf(client->fd, "pdi %d\n", player_nb);
    }
}

int check_client_status(socket_t socket, client_t **client, fd_set *reader)
{
    int status = SUCCESS;
    client_t *temp = *client;

    if (FD_ISSET((*client)->fd, reader))
        status = handle_command(*client);
    if (status == ERROR)
        return (ERROR);
    *client = (*client)->next;
    if (status == DISCONNECT) {
        kill_player(socket, temp->fd);
        FD_CLR(temp->fd, &socket->clients_fd);
        remove_client(&socket->client_list, temp->fd);
    }
    return (SUCCESS);
}

int handle_requests(socket_t socket, fd_set reader, game_info_t game_info)
{
    if (FD_ISSET(socket->socket_fd, &reader) &&
        connect_new_clients(socket) == ERROR)
        return (ERROR);
    for (client_t *client = socket->client_list.next; client != NULL;) {
        if (check_client_status(socket, &client, &reader) == ERROR)
            return (ERROR);
    }
    for (client_t *client = socket->client_list.next;
        client != NULL; client = client->next) {
        if (find_command(socket, client, game_info) == ERROR)
            return (ERROR);
    }
    return (SUCCESS);
}

int zappy_loop(game_info_t game_info, socket_t socket)
{
    fd_set reader;
    struct timeval tv = {0, 0};

    init_client(&socket->client_list, 0);
    socket->max_fd = socket->socket_fd;
    FD_ZERO(&socket->clients_fd);
    FD_SET(socket->socket_fd, &socket->clients_fd);
    socket->running = true;
    while (socket->running) {
        update_game(socket, game_info);
        reader = socket->clients_fd;
        tv.tv_usec = 20;
        if (select(socket->max_fd + 1, &reader, NULL, NULL, &tv) < 0) {
            perror("select");
            return (ERROR);
        }
        if (handle_requests(socket, reader, game_info) == ERROR)
            return (ERROR);
    }
    return (SUCCESS);
}