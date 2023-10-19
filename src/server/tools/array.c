/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <string.h>
#include <stdlib.h>
#include "server/zappy_server.h"

int array_occurs(char **arr, char *to_find)
{
    int nb = 0;

    if (arr == NULL || to_find == NULL)
        return (ERROR);
    for (int i = 0; arr[i] != NULL; i++) {
        if (strcmp(arr[i], to_find) == 0)
            nb++;
    }
    return (nb);
}

bool contain_same_str(char **arr)
{
    if (arr == NULL)
        return false;
    for (int i = 0; arr[i] != NULL; i++) {
        if (array_occurs(arr, arr[i]) > 1)
            return true;
    }
    return false;
}

void free_arr_content(void **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
}

int arr_len(const void **arr)
{
    int i = 0;

    if (arr == NULL)
        return (0);
    for (; arr[i] != NULL; i++);
    return (i);
}