/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "unit_test.h"

Test(parsing, parse_init_arg, .init=redirect_all_stdout)
{
    const char *args1[3] = {"-p", "4242", NULL};
    const char *args2[7] = {"-p", "4242", "-n", "Team1", "Team2", "Team2",
        NULL};
    parse_arg pargs = NULL;

    cr_assert(parse_init_arg(NULL) == NULL, "Send NULL");
    pargs = parse_init_arg(args1);
    cr_assert(pargs != NULL, "Send valid args");
    free(pargs);
    cr_assert(parse_init_arg(args2) == NULL, "Same team name");
}