/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/tools.h"
#include "server/init.h"

int fill_param(const char **args, parse_arg parg)
{
    const char *flags[7] = {"-p", "-x", "-y", "-n", "-c", "-f", NULL};
    int (*fun_ptr_arr[])(const char **, parse_arg) = {parse_port, parse_width,
        parse_height, parse_name, parse_team_size, parse_freq};
    int ret = -2;

    for (int i = 0; flags[i] != NULL; i++) {
        if (args != NULL && args[0] != NULL && strcmp(flags[i], args[0]) == 0) {
            ret = (*fun_ptr_arr[i])(args, parg);
            break;
        }
    }
    if (ret != SUCCESS) {
        if (args && args[0])
            fprintf(stderr, "%s '%s'\n\n", OPTION_INV, args[0]);
        display_help(HELP);
        return (ERROR);
    }
    return (SUCCESS);
}

int parse_default_args(const char **args, parse_arg parg)
{
    int ret = 0;

    if (args == NULL)
        return (ERROR);
    for (int i = 0; args[i] != NULL; i++) {
        ret = 0;
        if (args[i][0] == '-')
            ret = fill_param(&args[i], parg);
        if (ret != 0) {
            free(parg);
            return (ERROR);
        }
    }
    return (SUCCESS);
}

parse_arg parse_init_arg(const char **args)
{
    parse_arg parg = NULL;

    parg = malloc(sizeof(struct parse_arg_s));
    if (parg == NULL)
        return (NULL);
    zappy_set_default(parg);
    if (parse_default_args(args, parg) == ERROR)
        return (NULL);
    if (parg->team == NULL) {
        parg->team = default_team_name();
    } else if (contain_same_str(parg->team) == true) {
        fprintf(stderr, "-n option only accepts unique team names\n\n");
        display_help(HELP);
        free(parg);
        return (NULL);
    }
    return (parg);
}