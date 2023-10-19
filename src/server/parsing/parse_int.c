/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdio.h>
#include "server/parse.h"
#include "server/zappy_server.h"
#include "server/tools.h"

int parse_port(const char **args, parse_arg parg)
{
    if (arg_is_null(args) == true)
        return (ERROR);
    parg->port = get_nbr(args[1]);
    if (parg->port == ERROR) {
        fprintf(stderr, "-p option only accepts valid ports\n\n");
        return (ERROR);
    }
    return (SUCCESS);
}

int parse_width(const char **args, parse_arg parg)
{
    if (arg_is_null(args) == true)
        return (ERROR);
    parg->width = get_nbr(args[1]);
    if (parg->width == ERROR || parg->width < 10 || parg->width > 30) {
        fprintf(stderr,
            "-x option only accepts integer values between 10 and 30\n\n");
        return (ERROR);
    }
    return (SUCCESS);
}

int parse_height(const char **args, parse_arg parg)
{
    if (arg_is_null(args) == true)
        return (ERROR);
    parg->height = get_nbr(args[1]);
    if (parg->height == ERROR || parg->height < 10 || parg->height > 30) {
        fprintf(stderr,
            "-y option only accepts integer values between 10 and 30\n\n");
        return (ERROR);
    }
    return (SUCCESS);
}

int parse_team_size(const char **args, parse_arg parg)
{
    if (arg_is_null(args) == true)
        return (ERROR);
    parg->team_size = get_nbr(args[1]);
    if (parg->team_size == ERROR || parg->team_size < 1) {
        fprintf(stderr,
            "-c option only accepts integer values greater or equal to 1\n\n");
        return (ERROR);
    }
    return (SUCCESS);
}

int parse_freq(const char **args, parse_arg parg)
{
    if (arg_is_null(args) == true)
        return (ERROR);
    parg->freq = get_nbr(args[1]);
    if (parg->freq == ERROR || parg->freq < 2 || parg->freq > 10000) {
        fprintf(stderr,
            "-f option only accepts integer values between 2 and 10000\n\n");
        return (ERROR);
    }
    return (SUCCESS);
}