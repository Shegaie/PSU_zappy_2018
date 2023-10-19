/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

int graphic(socket_t, game_info_t, client_t *, char **);
int msz(socket_t, game_info_t, client_t *, char **);
int bct(socket_t, game_info_t, client_t *, char **);
int mct(socket_t, game_info_t, client_t *, char **);
int tna(socket_t, game_info_t, client_t *, char **);
int sgt(socket_t, game_info_t, client_t *, char **);
int sst(socket_t, game_info_t, client_t *, char **);
int ppo(socket_t, game_info_t, client_t *, char **);
int plv(socket_t, game_info_t, client_t *, char **);
int pin(socket_t, game_info_t, client_t *, char **);

int inventory(socket_t, game_info_t, client_t *, char **);
int broadcast(socket_t, game_info_t, client_t *, char **);
int connect_nbr(socket_t, game_info_t, client_t *, char **);
int left(socket_t, game_info_t, client_t *, char **);
int right(socket_t, game_info_t, client_t *, char **);
int forward(socket_t, game_info_t, client_t *, char **);
int look(socket_t, game_info_t, client_t *, char **);
int take(socket_t, game_info_t, client_t *, char **);
int set(socket_t, game_info_t, client_t *, char **);
int eject(socket_t, game_info_t, client_t *, char **);
int lay_egg(socket_t, game_info_t, client_t *, char **);
int incantation(socket_t, game_info_t, client_t *, char **);

typedef struct command_s {
    const char *command;
    int (*const ptr)(socket_t, game_info_t, client_t *, char **);
} command_t;

static const command_t COMMAND_FUNCTIONS[] = {
    {"GRAPHIC", graphic},
    {"msz", msz},
    {"bct", bct},
    {"mct", mct},
    {"tna", tna},
    {"sgt", sgt},
    {"sst", sst},
    {"ppo", ppo},
    {"plv", plv},
    {"pin", pin},
    {"Inventory", inventory},
    {"Broadcast", broadcast},
    {"Connect_nbr", connect_nbr},
    {"Left", left},
    {"Right", right},
    {"Forward", forward},
    {"Look", look},
    {"Take", take},
    {"Set", set},
    {"Eject", eject},
    {"Fork", lay_egg},
    {"Incantation", incantation},
    {NULL, NULL}
};