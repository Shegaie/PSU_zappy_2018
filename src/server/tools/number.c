/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdlib.h>
#include <math.h>
#include "server/zappy_server.h"

int get_nbr(const char *nbr_str)
{
    int result = 0;
    char *end_ptr = NULL;

    result = strtol(nbr_str, &end_ptr, 10);
    if (nbr_str == end_ptr)
        return (ERROR);
    return (result);
}

int increment_number(int number, int start, int end, int inc)
{
    if (number + inc >= end)
        return (start);
    else if (number + inc <= start - 1)
        return (end - 1);
    return (number + inc);
}

int intlen(int nb)
{
    int length;

    if (nb == 0)
        return (1);
    length = floor(log10(abs(nb))) + 1;
    if (nb < 0)
        length++;
    return (length);
}