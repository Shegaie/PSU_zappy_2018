/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <stdlib.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "server/direction.h"

vector_2d_t get_nearest_pos(int width, int height, client_t *emitter,
    client_t *player)
{
    vector_2d_t real_pos = {emitter->game_info.x, emitter->game_info.y};

    if (MIN(emitter->game_info.x, player->game_info.x) + width -
        MAX(emitter->game_info.x, player->game_info.x) <
        abs(emitter->game_info.x - player->game_info.x))
        real_pos.x = (emitter->game_info.x > player->game_info.x) ?
            -1 * (width - emitter->game_info.x) : width + emitter->game_info.x;
    if (MIN(emitter->game_info.y, player->game_info.y) + height -
        MAX(emitter->game_info.y, player->game_info.y) <
        abs(emitter->game_info.y - player->game_info.y))
        real_pos.y = (emitter->game_info.y > player->game_info.y) ?
            -1 * (height - emitter->game_info.y) :
            height + emitter->game_info.y;
    return (real_pos);
}

vector_2d_t get_third_point(client_t *player)
{
    vector_2d_t pos = {player->game_info.x, player->game_info.y};
    orientation_t orientation = player->game_info.orientation;

    if (orientation == NORTH || orientation == SOUTH)
        pos.y += (orientation == NORTH) ? 1 : -1;
    else
        pos.x += (orientation == EAST) ? 1 : -1;
    return (pos);
}

int get_direction_id(double angle)
{
    for (int i = 0; i < NB_DIRECTIONS; i++)
        if (angle >= DIRECTIONS[i].beginning && angle < DIRECTIONS[i].end)
            return (DIRECTIONS[i].direction);
    return (1);
}

double get_real_angle(double angle, vector_2d_t emitter_pos, client_t *player)
{
    if ((player->game_info.orientation == NORTH &&
        emitter_pos.x > player->game_info.x) ||
        (player->game_info.orientation == EAST &&
            emitter_pos.y < player->game_info.y))
        return (360 - angle);
    if ((player->game_info.orientation == SOUTH &&
        emitter_pos.x < player->game_info.x) ||
        (player->game_info.orientation == WEST &&
            emitter_pos.y > player->game_info.y))
        return (360 - angle);
    return (angle);
}

int get_direction(game_info_t game_info, client_t *emitter, client_t *player)
{
    vector_2d_t emitter_pos;
    double angle;

    if (emitter->game_info.x == player->game_info.x &&
        emitter->game_info.y == player->game_info.y)
        return (0);
    emitter_pos = get_nearest_pos(game_info->map->width, game_info->map->height,
        emitter, player);
    angle = compute_angle(
        (vector_2d_t){player->game_info.x, player->game_info.y},
        get_third_point(player), emitter_pos);
    angle = get_real_angle(angle, emitter_pos, player);
    return (get_direction_id(angle));
}
