/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdlib.h>
#include <stdio.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/tools.h"

bool add_ressource_randomly(tile_t tile, RESSOURCES resource, int chance)
{
    int random_nbr = (rand() % 100) + 1;

    if (random_nbr <= chance && resource == FOOD)
        tile->ressources[resource] += (rand() % (2)) + 1;
    else if (random_nbr <= chance)
        tile->ressources[resource] += 1;
    else
        return (false);
    return (true);
}

struct tile_s random_tile(void)
{
    static const int probabilities[] = {80, 70, 60, 50, 40, 30, 20};
    struct tile_s tile = {0};

    for (int j = 0; j < NB_RESSOURCES; j++) {
        tile.ressources[j] = 0;
        add_ressource_randomly(&tile, j, probabilities[j]);
    }
    return (tile);
}

tile_t generate_tiles(int x)
{
    tile_t tiles;

    if (x <= 0)
        return (NULL);
    tiles = malloc(sizeof(struct tile_s) * (x + 1));
    if (tiles == NULL) {
        perror("malloc");
        return (NULL);
    }
    for (int i = 0; i < x; i++) {
        tiles[i] = random_tile();
    }
    return (tiles);
}

map_t init_map(int x, int y)
{
    map_t map = NULL;
    int i = 0;

    map = malloc(sizeof(struct map_s));
    if (map == NULL || y <= 0)
        return (NULL);
    map->width = x;
    map->height = y;
    map->tiles = malloc(sizeof(tile_t *) * (y + 1));
    if (map->tiles == NULL)
        return (NULL);
    for (; i < y; i++) {
        map->tiles[i] = generate_tiles(x);
        if (map->tiles[i] == NULL) {
            free(map->tiles);
            return (NULL);
        }
    }
    map->tiles[i] = NULL;
    return (map);
}