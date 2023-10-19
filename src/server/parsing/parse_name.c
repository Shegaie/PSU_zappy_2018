/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server/parse.h"
#include "server/zappy_server.h"

int parse_name(const char **args, parse_arg parg)
{
    char **names = NULL;
    int i = 0;

    for (; args[i + 1] != NULL; i++) {
        if (args[i + 1][0] == '-')
            break;
        names = realloc(names, sizeof(char *) * (i + 2));
        if (names == NULL)
            return (ERROR);
        names[i] = strdup(args[i + 1]);
        if (names[i] == NULL)
            return (ERROR);
    }
    if (i == 0) {
        fprintf(stderr, "%s '%s'\n\n", OPTION_REQ, args[0]);
        return (ERROR);
    }
    names[i] = NULL;
    parg->team = names;
    return (SUCCESS);
}