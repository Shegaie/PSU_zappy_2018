/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <math.h>
#include "server/zappy_server.h"
#include "server/tools.h"

double distance(vector_2d_t a, vector_2d_t b)
{
    return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

double compute_angle(vector_2d_t a, vector_2d_t b, vector_2d_t c)
{
    double angle;

    if (distance(a, c) == 0 || distance(a, b) == 0)
        return (0);
    angle = acos((pow(distance(a, c), 2) + pow(distance(a, b), 2)
        - pow(distance(b, c), 2)) / (2 * distance(a, c) * distance(a, b)));
    return (angle * 180 / M_PI);
}