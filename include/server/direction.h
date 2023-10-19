/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

#define NB_DIRECTIONS 9

typedef struct direction_s {
    double beginning;
    double end;
    int direction;
} direction_t;

static const direction_t DIRECTIONS[] = {
    {0, 22.5, 1}, {22.5, 67.5, 2}, {67.5, 112.5, 3},
    {112.5, 157.5, 4}, {157.5, 202.5, 5}, {202.5, 247.5, 6},
    {247.5, 292.5, 7}, {292.5, 337.5, 8}, {337.5, 360, 1}
};