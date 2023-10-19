/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <stdlib.h>
#include <stdio.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/tools.h"

team_t *fill_teams(parse_arg parg, int nb_teams, int team_size)
{
    team_t *teams = malloc(nb_teams * sizeof(team_t));

    if (!teams) {
        perror("malloc");
        return (NULL);
    }
    for (int i = 0; parg->team[i]; i++)
        teams[i] = (team_t){parg->team[i], team_size, NULL};
    return (teams);
}

game_info_t generate_game(parse_arg parg)
{
    game_info_t game_info = malloc(sizeof(struct game_info_s));

    if (game_info == NULL) {
        perror("malloc");
        return (NULL);
    }
    game_info->nb_teams = arr_len((const void **)parg->team);
    game_info->teams = fill_teams(parg, game_info->nb_teams, parg->team_size);
    if (game_info->teams == NULL) {
        free(game_info);
        return (NULL);
    }
    game_info->freq = parg->freq;
    game_info->nb_eggs = 0;
    game_info->map = init_map(parg->width, parg->height);
    if (game_info->map == NULL) {
        free(game_info);
        return (NULL);
    }
    return (game_info);
}