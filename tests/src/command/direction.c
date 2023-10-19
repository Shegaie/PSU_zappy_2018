/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "server/command.h"
#include "unit_test.h"

bool test_get_direction(vector_2d_t emitter_pos, vector_2d_t player_pos,
    orientation_t orientation, int expected)
{
    struct game_info_s game_info = {.map = init_map(10, 10)};
    client_t emitter = {.game_info.x = emitter_pos.x,
        .game_info.y = emitter_pos.y};
    client_t player = {.game_info.x = player_pos.x, .game_info.y = player_pos.y,
        .game_info.orientation = orientation};
    bool ok = false;

    if (get_direction(&game_info, &emitter, &player) == expected)
        ok = true;
    free_arr_content((void **)game_info.map->tiles);
    free(game_info.map->tiles);
    free(game_info.map);
    return (ok);
}

Test(direction, get_direction, .init=redirect_all_stdout)
{
    cr_assert(test_get_direction((vector_2d_t){5, 5}, (vector_2d_t){5, 5},
        NORTH, 0), "same tile");
    cr_assert(test_get_direction((vector_2d_t){3, 3}, (vector_2d_t){7, 7},
        NORTH, 4), "basic broadcast");
    cr_assert(test_get_direction((vector_2d_t){3, 3}, (vector_2d_t){3, 7},
        WEST, 3), "line broadcast");
    cr_assert(test_get_direction((vector_2d_t){3, 3}, (vector_2d_t){9, 9},
        SOUTH, 4), "around broadcast");
    cr_assert(test_get_direction((vector_2d_t){8, 0}, (vector_2d_t){0, 0},
        NORTH, 3), "around broadcast");
}

Test(direction, eject_direction, .init=redirect_all_stdout)
{
    cr_assert(test_get_direction((vector_2d_t){5, 5}, (vector_2d_t){4, 5},
        NORTH, 7), "basic ejection");
    cr_assert(test_get_direction((vector_2d_t){5, 0}, (vector_2d_t){5, 9},
        SOUTH, 5), "around ejection");
}