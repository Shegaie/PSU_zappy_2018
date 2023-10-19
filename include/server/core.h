/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#pragma once

int zappy_server(const char **arg);

int zappy_loop(game_info_t parg, socket_t socket);

game_info_t generate_game(parse_arg parg);

void check_players_death(socket_t socket, int freq);

void update_game(socket_t socket, game_info_t game_info);

void kill_player(socket_t socket, int fd);