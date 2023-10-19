/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <math.h>
#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "unit_test.h"

Test(tools, distance, .init=redirect_all_stdout)
{
    cr_assert(distance((vector_2d_t){0, 0}, (vector_2d_t){0, 0}) == 0,
        "Same origin point");
    cr_assert(distance((vector_2d_t){3, -2}, (vector_2d_t){3, -2}) == 0,
        "Same point");
    cr_assert(distance((vector_2d_t){1, 1}, (vector_2d_t){1, 3}) == 2,
        "same x");
    cr_assert(distance((vector_2d_t){1, 1}, (vector_2d_t){-3, 1}) == 4,
        "same y");
    cr_assert(distance((vector_2d_t){1, 1}, (vector_2d_t){3, 3}) == sqrt(8),
        "basic test");
}

Test(tools, compute_angle, .init=redirect_all_stdout)
{
    double angle;

    angle = compute_angle((vector_2d_t){0, 0}, (vector_2d_t){1, 0},
        (vector_2d_t){0, 1});
    cr_assert(angle > 89.999 && angle < 90.001, "basic angle");
    angle = compute_angle((vector_2d_t){0, 0}, (vector_2d_t){1, 0},
        (vector_2d_t){-1, 0});
    cr_assert(angle == 180, "flat angle");
    angle = compute_angle((vector_2d_t){0, 0}, (vector_2d_t){-1, 0},
        (vector_2d_t){-1, 0});
    cr_assert(angle == 0, "null angle");
    angle = compute_angle((vector_2d_t){0, 0}, (vector_2d_t){0, 0},
        (vector_2d_t){0, 0});
    cr_assert(angle == 0, "same points");
}