/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdlib.h>
#include <time.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/tools.h"
#include "server/init.h"
#include "server/core.h"

void free_parg(parse_arg parg)
{
    free_arr_content((void *)parg->team);
    free(parg->team);
    free(parg);
}

void free_socket(socket_t socket)
{
    clear_list(&socket->client_list);
    free(socket);
}

void free_game_info(game_info_t game_info)
{
    egg_t *tmp;

    for (int i = 0; i < game_info->nb_teams; i++) {
        for (egg_t *egg = game_info->teams[i].eggs; egg;) {
            tmp = egg;
            egg = egg->next;
            free(tmp);
        }
    }
    free(game_info->teams);
    free_arr_content((void **)game_info->map->tiles);
    free(game_info->map->tiles);
    free(game_info->map);
    free(game_info);
}

int create_elements(parse_arg *parg, socket_t *socket, const char **arg)
{
    int max_players = 0;

    srand(time(NULL));
    *parg = parse_init_arg(arg);
    if (*parg == NULL)
        return (ERROR);
    max_players = arr_len((void *)(*parg)->team) * (*parg)->team_size;
    *socket = init_socket((*parg)->port, max_players);
    if (*socket == NULL) {
        free_parg(*parg);
        return (ERROR);
    }
    return (SUCCESS);
}

int zappy_server(const char **arg)
{
    parse_arg parg = NULL;
    socket_t socket = NULL;
    game_info_t game_info = NULL;
    int ret = 0;

    if (create_elements(&parg, &socket, arg) == ERROR)
        return (ERROR);
    game_info = generate_game(parg);
    if (game_info == NULL) {
        free_socket(socket);
        free_parg(parg);
        return (ERROR);
    }
    ret = zappy_loop(game_info, socket);
    free_socket(socket);
    free_parg(parg);
    free_game_info(game_info);
    return (ret);
}