/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#pragma once

typedef struct vector_2d_s {
    int x;
    int y;
} vector_2d_t;

int add_tile_content(socket_t socket, game_info_t game_info, vector_2d_t tile,
    char **line);

/* HELP */

int display_help(const char *help);

bool arg_is_null(const char **args);

/* ARRAY */

bool contain_same_str(char **arr);

void free_arr_content(void **arr);

int arr_len(const void **arr);

int array_occurs(char **arr, char *to_find);

/* NUMBER */

int get_nbr(const char *nbr_str);

int increment_number(int number, int start, int end, int inc);

int intlen(int nb);

/* STRING */

int get_nb_words(char *str, char *delims);

char **str_split(char *str, char *delims);

char *concat_str(char **dest, char *src);

/* MATH */

double distance(vector_2d_t a, vector_2d_t b);

double compute_angle(vector_2d_t a, vector_2d_t b, vector_2d_t c);