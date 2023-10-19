/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "server/zappy_server.h"
#include "server/command.h"
#include "server/tools.h"

vector_2d_t get_orientation_inc(orientation_t orientation)
{
    if (orientation == NORTH || orientation == SOUTH)
        return ((vector_2d_t){(orientation == NORTH) ? 1 : -1, 0});
    else
        return ((vector_2d_t){0, (orientation == EAST) ? -1 : 1});
}

vector_2d_t get_first_tile(game_info_t game_info, client_t *client, int level)
{
    int x = client->game_info.x;
    int y = client->game_info.y;
    orientation_t orientation = client->game_info.orientation;

    for (int i = 0; i < level; i++) {
        if (orientation == NORTH || orientation == SOUTH) {
            x = increment_number(x, 0, game_info->map->width,
                (orientation == NORTH) ? -1 : 1);
            y = increment_number(y, 0, game_info->map->height,
                (orientation == NORTH) ? 1 : -1);
        } else {
            x = increment_number(x, 0, game_info->map->width,
                (orientation == EAST) ? 1 : -1);
            y = increment_number(y, 0, game_info->map->height,
                (orientation == EAST) ? 1 : -1);
        }
    }
    return ((vector_2d_t){x, y});
}

char *add_line(socket_t socket, game_info_t game_info, client_t *client,
    int level)
{
    vector_2d_t inc = get_orientation_inc(client->game_info.orientation);
    vector_2d_t tile = get_first_tile(game_info, client, level);
    char *line = NULL;

    for (int i = 0; i < level * 2 + 1; i++) {
        if (concat_str(&line, (level == 0) ? "" : ",") == NULL)
            return (NULL);
        if (add_tile_content(socket, game_info, tile, &line) == ERROR) {
            free(line);
            return (NULL);
        }
        tile.x = increment_number(tile.x, 0, game_info->map->width, inc.x);
        tile.y = increment_number(tile.y, 0, game_info->map->height, inc.y);
    }
    return (line);
}

char *get_view(socket_t socket, game_info_t game_info, client_t *client)
{
    char *res = strdup("[");
    char *line = NULL;

    if (res == NULL)
        return (NULL);
    for (int i = 0; i < client->game_info.level + 1; i++) {
        line = add_line(socket, game_info, client, i);
        if (line == NULL) {
            free(res);
            return (NULL);
        }
        if (concat_str(&res, line) == NULL) {
            free(line);
            return (NULL);
        }
        free(line);
    }
    if (concat_str(&res, " ]") == NULL)
        return (NULL);
    return (res);
}

int look(socket_t socket, game_info_t game_info, client_t *client, char **args)
{
    char *res = NULL;

    if (command_parser(args, client, false, 0) == ERROR)
        return (SUCCESS);
    res = get_view(socket, game_info, client);
    if (res == NULL)
        return (ERROR);
    dprintf(client->fd, "%s\n", res);
    free(res);
    return (SUCCESS);
}