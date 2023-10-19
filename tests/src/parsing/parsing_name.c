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

Test(parsing, team_name, .init=redirect_all_stdout)
{
    const char *args[4] = {"-n"};
    struct parse_arg_s parse_arg = {0};

    cr_assert(fill_param(args, &parse_arg) == ERROR, "Missing parameter");
    args[1] = "Name1";
    args[2] = NULL;
    cr_assert(fill_param(args, &parse_arg) == SUCCESS, "Valid name");
    free(parse_arg.team);
    args[2] = "-Name2";
    args[3] = NULL;
    cr_assert(fill_param(args, &parse_arg) == SUCCESS, "Arg name");
    free(parse_arg.team);
}