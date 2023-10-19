/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

#include <stdbool.h>

#define NB_RESSOURCES 7

typedef struct egg_s egg_t;

struct egg_s {
    int id;
    int player;
    int x;
    int y;
    int orientation;
    struct timeval timer;
    bool hatched;
    egg_t *next;
};

typedef struct team_s team_t;

struct team_s {
    char *name;
    int team_size;
    egg_t *eggs;
};

typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
} RESSOURCES;

typedef struct tile_s *tile_t;

struct tile_s {
    int ressources[7];
};

typedef struct map_s *map_t;

struct map_s {
    int width;
    int height;
    tile_t *tiles;
};

typedef struct game_info_s *game_info_t;

struct game_info_s {
    team_t *teams;
    int nb_teams;
    int freq;
    map_t map;
    int nb_eggs;
};

map_t init_map(int x, int y);

struct tile_s random_tile(void);

tile_t generate_tiles(int x);

bool add_ressource_randomly(tile_t tile, RESSOURCES resource, int chance);