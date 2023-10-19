/*
** EPITECH PROJECT, 2022
** NWP_myftp_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/init.h"
#include "unit_test.h"

Test(init, default_values_settings, .init=redirect_all_stdout)
{
    struct parse_arg_s arg = {0};

    zappy_set_default(&arg);
    cr_assert(arg.port == 4242, "Default value for port");
    cr_assert(arg.width == 10, "Default value for width");
    cr_assert(arg.height == 10, "Default value for height");
    cr_assert(arg.freq == 100, "Default value for freq");
    cr_assert(arg.team == NULL, "Default value for team");
}

Test(init, default_values_names, .init=redirect_all_stdout)
{
    char **team_names = default_team_name();

    cr_assert(team_names != NULL, "Default names array is NULL");
    cr_assert_str_eq(team_names[0], "Team1", "Team1");
    cr_assert_str_eq(team_names[1], "Team2", "Team2");
    cr_assert_str_eq(team_names[2], "Team3", "Team3");
    cr_assert_str_eq(team_names[3], "Team4", "Team4");
    free(team_names);
}