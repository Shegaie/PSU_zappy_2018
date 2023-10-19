/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <string.h>
#include <stdio.h>
#include "server/zappy_server.h"
#include "server/parse.h"

int display_help(const char *help)
{
    FILE *stream = NULL;
    char *buffer = NULL;
    size_t n = 0;

    if (strcmp(help, HELP) != 0)
        return (EXIT_ERROR);
    stream = fopen(HELP_FILE, "r");
    if (stream == NULL) {
        perror("fopen()");
        return (EXIT_ERROR);
    }
    while (getline(&buffer, &n, stream) > 0) {
        printf("%s", buffer);
    }
    putchar('\n');
    return (SUCCESS);
}

bool arg_is_null(const char **args)
{
    if (args == NULL || args[0] == NULL)
        return (true);
    if (args[1] == NULL) {
        fprintf(stderr, "%s '%s'\n\n", OPTION_REQ, args[0]);
        return (true);
    }
    return (false);
}