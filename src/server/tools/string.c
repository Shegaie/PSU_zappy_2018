/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "server/zappy_server.h"
#include "server/tools.h"

int skip_word(char *str, int i, char *delims)
{
    while (str[i + 1] && strchr(delims, str[i + 1]) == NULL)
        i++;
    return (i);
}

int get_nb_words(char *str, char *delims)
{
    int nb = 0;

    for (int i = 0; str[i]; i++) {
        if (strchr(delims, str[i]) == NULL) {
            nb++;
            i = skip_word(str, i, delims);
        }
    }
    return (nb);
}

int fill_word_array(char **array, char *copy, char *delims)
{
    char *ptr = NULL;

    ptr = strtok(copy, delims);
    array[0] = (ptr) ? strdup(ptr) : NULL;
    if (ptr && array[0] == NULL) {
        perror("strdup");
        return (ERROR);
    }
    for (int i = 1; ptr != NULL; i++) {
        ptr = strtok(NULL, delims);
        array[i] = (ptr) ? strdup(ptr) : NULL;
        if (ptr && array[i] == NULL) {
            free_arr_content((void **)array);
            perror("strdup");
            return (ERROR);
        }
    }
    return (SUCCESS);
}

char **str_split(char *str, char *delims)
{
    char *copy = strdup(str);
    char **array = NULL;

    if (!copy) {
        perror("strdup");
        return (NULL);
    }
    array = malloc((get_nb_words(str, delims) + 1) * sizeof(char *));
    if (!array) {
        free(copy);
        perror("malloc");
        return (NULL);
    }
    if (fill_word_array(array, copy, delims) == ERROR) {
        free(array);
        free(copy);
        return (NULL);
    }
    free(copy);
    return (array);
}

char *concat_str(char **dest, char *src)
{
    size_t destlen = (*dest) ? strlen(*dest) : 0;
    size_t srclen = (src) ? strlen(src) : 0;
    char *temp = *dest;

    *dest = realloc(*dest, destlen + srclen + 1);
    if (*dest == NULL) {
        perror("realloc");
        return (NULL);
    }
    if (temp == NULL)
        *dest[0] = '\0';
    if (src)
        strcat(*dest, src);
    return (*dest);
}