/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "server/ressources.h"

int add_ressource(int nb, RESSOURCES ressource, char **ressources)
{
    while (nb > 0) {
        if (concat_str(ressources, " ") == NULL ||
            concat_str(ressources, (char *)RESSOURCES_NAME[ressource]) == NULL)
            return (ERROR);
        nb--;
    }
    return (SUCCESS);
}

char *get_tile_ressources(game_info_t game_info, vector_2d_t tile)
{
    char *ressources = strdup("");

    if (ressources == NULL) {
        perror("strdup");
        return (NULL);
    }
    for (int i = 0; i < NB_RESSOURCES; i++) {
        if (game_info->map->tiles[tile.y][tile.x].ressources[i] > 0 &&
            add_ressource(game_info->map->tiles[tile.y][tile.x].ressources[i],
                i, &ressources) == ERROR) {
            return (NULL);
        }
    }
    return (ressources);
}

int get_tile_nb_players(socket_t socket, vector_2d_t tile)
{
    int nb = 0;

    for (client_t *player = socket->client_list.next; player;
    player = player->next) {
        if (player->game_info.x == tile.x && player->game_info.y == tile.y)
            nb++;
    }
    return (nb);
}

char *get_tile_players(socket_t socket, vector_2d_t tile)
{
    int nb_players = get_tile_nb_players(socket, tile);
    char *players = strdup("");

    if (players == NULL) {
        perror("strdup");
        return (NULL);
    }
    for (int i = 0; i < nb_players; i++) {
        if (concat_str(&players, " player") == NULL)
            return (NULL);
    }
    return (players);
}

int add_tile_content(socket_t socket, game_info_t game_info, vector_2d_t tile,
    char **line)
{
    char *content = NULL;

    content = get_tile_players(socket, tile);
    if (content == NULL)
        return (ERROR);
    if (concat_str(line, content) == NULL) {
        free(content);
        return (ERROR);
    }
    free(content);
    content = get_tile_ressources(game_info, tile);
    if (content == NULL)
        return (ERROR);
    if (concat_str(line, content) == NULL) {
        free(content);
        return (ERROR);
    }
    free(content);
    return (SUCCESS);
}