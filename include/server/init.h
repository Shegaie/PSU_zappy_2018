/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#pragma once

char **default_team_name(void);

void zappy_set_default(parse_arg parg);

socket_t init_socket(int port, int max_players);

int init_listen(int socket_fd, int max_players);

int bind_socket(int port, int socket_fd);

int create_socket(void);

game_info_t generate_game(parse_arg parg);

team_t *fill_teams(parse_arg parg, int nb_teams, int team_size);