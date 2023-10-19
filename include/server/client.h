/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

#include <stdbool.h>

#define MAX_COMMANDS 11

typedef enum orientation_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
} orientation_t;

typedef struct client_game_s client_game_t;

struct client_game_s {
    int inventory[NB_RESSOURCES];
    char *team_name;
    int level;
    int x;
    int y;
    orientation_t orientation;
    bool elevation_ok;
    struct timeval death_timer;
};

typedef struct client_s client_t;

struct client_s {
    int fd;
    char *commands[MAX_COMMANDS];
    struct timeval timer;
    bool graphic;
    client_game_t game_info;
    client_t *next;
};

client_t *add_client(client_t *clients, int fd);

void remove_client(client_t *clients, int fd);

void clear_list(client_t *clients);

void init_client(client_t *client, int fd);

void free_client(client_t *client);