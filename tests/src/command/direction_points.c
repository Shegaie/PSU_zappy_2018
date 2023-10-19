/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "unit_test.h"
#include "direction.h"

bool test_real_pos(vector_2d_t emitter_pos, vector_2d_t player_pos,
    vector_2d_t expected)
{
    client_t emitter =
        {.game_info.x = emitter_pos.x, .game_info.y = emitter_pos.y};
    client_t player =
        {.game_info.x = player_pos.x, .game_info.y = player_pos.y};
    vector_2d_t real_pos;

    real_pos = get_nearest_pos(10, 10, &emitter, &player);
    return (real_pos.x == expected.x && real_pos.y == expected.y);
}

Test(direction, get_nearest_pos, .init=redirect_all_stdout)
{
    cr_assert(test_real_pos((vector_2d_t){2, 3}, (vector_2d_t){5, 7},
        (vector_2d_t){2, 3}), "nearest pos : Normal");
    cr_assert(test_real_pos((vector_2d_t){2, 6}, (vector_2d_t){8, 4},
        (vector_2d_t){12, 6}), "nearest pos : Around x");
    cr_assert(test_real_pos((vector_2d_t){2, 9}, (vector_2d_t){6, 1},
        (vector_2d_t){2, -1}), "nearest pos : Around y");
    cr_assert(test_real_pos((vector_2d_t){8, 3}, (vector_2d_t){2, 9},
        (vector_2d_t){-2, 13}), "nearest pos : Around x and y");
}

bool test_third_point(vector_2d_t pos, orientation_t orientation,
    vector_2d_t expected)
{
    client_t player = {.game_info.x = pos.x, .game_info.y = pos.y,
        .game_info.orientation = orientation};
    vector_2d_t point = get_third_point(&player);

    return (point.x == expected.x && point.y == expected.y);
}

Test(direction, get_third_point, .init=redirect_all_stdout)
{
    cr_assert(test_third_point((vector_2d_t){2, 3}, NORTH, (vector_2d_t){2, 4}),
        "nearest pos : Normal");
    cr_assert(test_third_point((vector_2d_t){9, 6}, EAST, (vector_2d_t){10, 6}),
        "nearest pos : Around x");
    cr_assert(test_third_point((vector_2d_t){3, 0}, SOUTH,
        (vector_2d_t){3, -1}), "nearest pos : Around y");
    cr_assert(test_third_point((vector_2d_t){9, 9}, WEST, (vector_2d_t){8, 9}),
        "nearest pos : Around x and y");
}