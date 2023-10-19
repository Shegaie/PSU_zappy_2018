/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#pragma once

/* Project settings */
#define HELP "-help"
#define HELP_FILE "server_help"

/* Project errors */
#define OPTION_REQ "./zappy_server: option requires an argument --"
#define OPTION_INV "./zappy_server: invalid option --"

typedef struct parse_arg_s *parse_arg;

struct parse_arg_s {
    int port;
    int width;
    int height;
    char **team;
    int team_size;
    int freq;
};

parse_arg parse_init_arg(const char **args);

int parse_freq(const char **args, parse_arg parg);

int parse_team_size(const char **args, parse_arg parg);

int parse_height(const char **args, parse_arg parg);

int parse_width(const char **args, parse_arg parg);

int parse_port(const char **args, parse_arg parg);

int parse_name(const char **args, parse_arg parg);

int fill_param(const char **args, parse_arg parg);

int parse_default_args(const char **args, parse_arg parg);