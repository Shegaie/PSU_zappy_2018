/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/time.h>
#include "server/zappy_server.h"
#include "server/commands_array.h"
#include "server/tools.h"
#include "server/command.h"

void remove_command(char **commands)
{
    int array_length = arr_len((void *)commands);

    if (commands[0] != NULL) {
        free(commands[0]);
        memmove(commands, &commands[1], array_length * sizeof(char *));
    }
}

int execute_function(socket_t socket, game_info_t game_info, client_t *client,
    char **args)
{
    int i = 0;

    if (strcmp(args[0], "STOP") == 0) {
        socket->running = false;
        return (SUCCESS);
    }
    if (client->game_info.team_name == NULL && client->graphic == false &&
        strcmp(args[0], "GRAPHIC") != 0)
        return ((join_team(socket, game_info, client, args[0]) == ERROR) ?
            ERROR : SUCCESS);
    for (i = 0; COMMAND_FUNCTIONS[i].command != NULL; i++)
        if (strcmp(args[0], COMMAND_FUNCTIONS[i].command) == 0 &&
            check_timer(socket, args, client, game_info))
            return (COMMAND_FUNCTIONS[i].ptr(socket, game_info, client,
                &args[1]));
        else if (strcmp(args[0], COMMAND_FUNCTIONS[i].command) == 0)
            break;
    if (COMMAND_FUNCTIONS[i].command == NULL)
        dprintf(client->fd, (client->graphic) ? "suc\n" : "ko\n");
    return (SUCCESS);
}

int find_command(socket_t socket, client_t *client, game_info_t game_info)
{
    char *command = client->commands[0];
    char **args = NULL;

    if (command) {
        args = str_split(command, " \t\n");
        if (!args)
            return (ERROR);
        if (args[0] &&
            execute_function(socket, game_info, client, args) == ERROR) {
            free_arr_content((void **)args);
            free(args);
            return (ERROR);
        }
        free_arr_content((void **)args);
        free(args);
        if (!timerisset(&client->timer))
            remove_command(client->commands);
    }
    return (SUCCESS);
}