/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "unit_test.h"

Test(tools, display_help, .init=redirect_all_stdout)
{
    cr_assert(display_help("-help") == SUCCESS, "Display Help");
    cr_assert(display_help("hello") == EXIT_ERROR, "Display Help wrong arg");
}

Test(tools, arg_is_null, .init=redirect_all_stdout)
{
    const char *arg[3] = {"hello", NULL, NULL};

    cr_assert(arg_is_null(NULL) == true, "Send NULL");
    cr_assert(arg_is_null(arg) == true, "Send arg 1 NULL");
    arg[1] = "world";
    cr_assert(arg_is_null(arg) == false, "Send valid arg");
}