/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/core.h"

int main(UNUSED int an, const char **arg)
{
    if (zappy_server(&arg[1]) == ERROR)
        return (EXIT_ERROR);
    return (SUCCESS);
}