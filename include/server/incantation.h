/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

typedef struct elevation_params_s {
    int nb_players;
    int ressources[NB_RESSOURCES - 1];
} elevation_params_t;

static const elevation_params_t ELEVATION_PARAMS[] = {
    {1, {1, 0, 0, 0, 0, 0}},
    {2, {1, 1, 1, 0, 0, 0}},
    {2, {2, 0, 1, 0, 2, 0}},
    {4, {1, 1, 2, 0, 1, 0}},
    {4, {1, 2, 1, 3, 0, 0}},
    {6, {1, 2, 3, 0, 1, 0}},
    {6, {2, 2, 2, 2, 2, 1}}
};