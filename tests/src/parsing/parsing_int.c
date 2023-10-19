/*
** EPITECH PROJECT, 2022
** NWP_myftp_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "unit_test.h"

Test(parsing, fill_param_port, .init=redirect_all_stdout)
{
    const char *args[2] = {"-t", "4242"};
    struct parse_arg_s parse_arg = {0};

    cr_assert(fill_param(NULL, &parse_arg) == ERROR, "Port, Arg NULL");
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Port, Invalid Flag");
    args[0] = "-p";
    fill_param(args, &parse_arg);
    cr_assert(parse_arg.port == 4242, "Valid port");
    args[1] = "Hello";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Wrong port value");
    cr_assert(parse_port(NULL, NULL) == ERROR, "NULL port");
}

Test(parsing, fill_param_width, .init=redirect_all_stdout)
{
    const char *args[2] = {"-x", "9"};
    struct parse_arg_s parse_arg = {0};

    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid width (9)");
    args[1] = "10";
    fill_param(args, &parse_arg);
    cr_assert(parse_arg.width == 10, "Valid width");
    args[1] = "hello world";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid width (Hello)");
    args[1] = "101";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid width (101)");
    cr_assert(parse_width(NULL, NULL) == ERROR, "NULL width");
}

Test(parsing, fill_param_height, .init=redirect_all_stdout)
{
    const char *args[2] = {"-y", "9"};
    struct parse_arg_s parse_arg = {0};

    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid height (9)");
    args[1] = "10";
    fill_param(args, &parse_arg);
    cr_assert(parse_arg.height == 10, "Valid height");
    args[1] = "hello world";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid height (Hello)");
    args[1] = "101";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid height (101)");
    cr_assert(parse_height(NULL, NULL) == ERROR, "NULL height");
}

Test(parsing, fill_param_team_size, .init=redirect_all_stdout)
{
    const char *args[2] = {"-c", "-1"};
    struct parse_arg_s parse_arg = {0};

    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid team size (-1)");
    args[1] = "1";
    fill_param(args, &parse_arg);
    cr_assert(parse_arg.team_size == 1, "Valid team size");
    args[1] = "hello world";
    cr_assert(fill_param(args, &parse_arg) == ERROR,
        "Invalid team size (Hello)");
    args[1] = "9999";
    fill_param(args, &parse_arg);
    cr_assert(parse_arg.team_size == 9999, "Valid team size (big)");
    cr_assert(parse_team_size(NULL, NULL) == ERROR, "NULL team size");
}

Test(parsing, frequence, .init=redirect_all_stdout)
{
    const char *args[2] = {"-f", "0"};
    struct parse_arg_s parse_arg = {0};

    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid freq (0)");
    args[1] = "2";
    fill_param(args, &parse_arg);
    cr_assert(parse_arg.freq == 2, "Valid freq");
    args[1] = "hello world";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid freq (Hello)");
    args[1] = "10001";
    cr_assert(fill_param(args, &parse_arg) == ERROR, "Invalid freq (10001)");
    cr_assert(parse_freq(NULL, NULL) == ERROR, "NULL freq");
}