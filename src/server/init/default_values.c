/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdlib.h>
#include <string.h>
#include "server/parse.h"

void zappy_set_default(parse_arg parg)
{
    parg->port = 4242;
    parg->width = 10;
    parg->height = 10;
    parg->team_size = 3;
    parg->freq = 100;
    parg->team = NULL;
}

char **default_team_name(void)
{
    char **default_team_name = NULL;

    default_team_name = malloc(sizeof(char *) * 5);
    default_team_name[0] = strdup("Team1");
    default_team_name[1] = strdup("Team2");
    default_team_name[2] = strdup("Team3");
    default_team_name[3] = strdup("Team4");
    default_team_name[4] = NULL;
    return (default_team_name);
}
