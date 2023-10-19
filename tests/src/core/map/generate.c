/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/map.h"
#include "server/command.h"
#include "unit_test.h"

Test(init, random_tile, .init=redirect_all_stdout)
{
    struct tile_s tile = random_tile();
    (void) tile;
}

Test(init, generate_tiles, .init=redirect_all_stdout)
{
    tile_t tiles = generate_tiles(0);

    cr_assert(tiles == NULL, "Generate line of tiles of size 0");
    tiles = generate_tiles(-1);
    cr_assert(tiles == NULL, "Generate line of tiles of size -1");
    tiles = generate_tiles(100);
    cr_assert(tiles != NULL, "Generate line of tiles of size 100");
    free(tiles);
}

Test(init, init_map, .init=redirect_all_stdout)
{
    map_t map = init_map(0, 0);

    cr_assert(map == NULL, "Generate line of tiles of size 0");
    map = init_map(-1, 30);
    cr_assert(map == NULL, "Generate line of tiles of size -1");
    map = init_map(100, 100);
    cr_assert(map != NULL, "Generate line of tiles of size 100");
    for (int i = 0; map->tiles[i] != NULL; i++)
        free(map->tiles[i]);
    free(map);
}

Test(init, add_ressource_randomly, .init=redirect_all_stdout)
{
    static const int probabilities[] = {100, 100, 100, 100, 100, 100, 100};
    struct tile_s tile = {0};

    for (int j = 0; j < NB_RESSOURCES; j++) {
        add_ressource_randomly(&tile, j, probabilities[j]);
    }
}

Test(init, add_food, .init=redirect_all_stdout)
{
    add_food(NULL, NULL);
}