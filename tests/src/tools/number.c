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

Test(tools, increment_number, .init=redirect_all_stdout)
{
    cr_assert(increment_number(10, 1, 20, 1) == 11, "Basic increment");
    cr_assert(increment_number(20, 1, 20, 1) == 1, "Increment interval");
    cr_assert(increment_number(14, 14, 20, -1) == 19, "Decrement interval");
}

Test(tools, intlen, .init=redirect_all_stdout)
{
    cr_assert(intlen(-1) == 2, "Negative number");
    cr_assert(intlen(0) == 1, "Null number");
    cr_assert(intlen(10) == 2, "Basic number");
    cr_assert(intlen(100000000) == 9, "Len of 9");
}