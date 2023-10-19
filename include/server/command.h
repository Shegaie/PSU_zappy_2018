/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

#define DISCONNECT 2

int handle_command(client_t *client);

int find_command(socket_t socket, client_t *client, game_info_t game_info);

int join_team(socket_t socket, game_info_t game_info, client_t *client,
    char *team);

void send_tile_info(client_t *client, game_info_t game_info, int x, int y);

int command_parser(char **args, client_t *client, bool graphic, int nb_params);

bool check_timer(socket_t socket, char **args, client_t *client,
    game_info_t game_info);

void send_pnw(client_t *client, client_t *new_player);

void send_graph_pnw(socket_t socket, client_t *new_player);

int get_team_places(socket_t socket, game_info_t game_info, char *team);

int get_ressource_index(char *name);

void forward_player(client_t *client, game_info_t game_info);

void move_player(client_t *client, int x, int y, game_info_t game_info);

void send_player_pos(socket_t socket, client_t *player);

void send_ppo(client_t *client, client_t *player);

void send_bct_graphic(socket_t socket, game_info_t game_info, int x, int y);

void send_pin_graphic(socket_t socket, client_t *player);

int get_direction(game_info_t game_info, client_t *emitter, client_t *player);

void send_enw(client_t *client, egg_t *egg);

void check_incant(socket_t socket, game_info_t game_info, client_t *client,
    char **args);

bool is_time_elapsed(struct timeval *timer, float time);

bool allow_elevation(socket_t socket, game_info_t game_info, client_t *client);

void add_food(socket_t socket, game_info_t game_info);

int msz(socket_t, game_info_t, client_t *, char **);
int sgt(socket_t, game_info_t, client_t *, char **);
int mct(socket_t, game_info_t, client_t *, char **);
int tna(socket_t, game_info_t, client_t *, char **);