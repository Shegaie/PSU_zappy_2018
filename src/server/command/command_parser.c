/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include "server/zappy_server.h"
#include "server/tools.h"

int command_parser(char **args, client_t *client, bool graphic, int nb_params)
{
    int nb_args;

    if (graphic != client->graphic) {
        if (client->graphic)
            dprintf(client->fd, "suc\n");
        else
            dprintf(client->fd, "ko\n");
        return (ERROR);
    }
    nb_args = arr_len((void *)args);
    if (nb_args != nb_params) {
        if (client->graphic)
            dprintf(client->fd, "sbp\n");
        else
            dprintf(client->fd, "ko\n");
        return (ERROR);
    }
    return (SUCCESS);
}