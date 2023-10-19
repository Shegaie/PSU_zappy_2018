/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include "server/zappy_server.h"
#include "server/command.h"

void add_command_to_buffer(char **commands_buffer, char *command)
{
    int i = 0;

    while (commands_buffer[i] != NULL && i < 10)
        i++;
    if (i < 10) {
        commands_buffer[i] = command;
        commands_buffer[i + 1] = NULL;
    }
}

int handle_command(client_t *client)
{
    FILE *sock = fdopen(client->fd, "r");
    char *command = NULL;
    size_t len = 0;
    ssize_t length = getline(&command, &len, sock);

    if (length < 0) {
        free(command);
        if (!command) {
            perror("getline");
            return (ERROR);
        } else
            return (DISCONNECT);
    }
    add_command_to_buffer(client->commands, command);
    return (SUCCESS);
}