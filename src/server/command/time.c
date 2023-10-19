/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#include <memory.h>
#include <sys/time.h>
#include "server/zappy_server.h"
#include "server/time.h"
#include "server/command.h"

int get_command_time(char *command)
{
    for (int i = 0; COMMAND_TIMES[i].command != NULL; i++) {
        if (strcmp(command, COMMAND_TIMES[i].command) == 0)
            return (COMMAND_TIMES[i].time);
    }
    return (0);
}

bool is_time_elapsed(struct timeval *timer, float time)
{
    struct timeval now;
    struct timeval res;

    gettimeofday(&now, NULL);
    timersub(&now, timer, &res);
    if ((float)res.tv_sec + (float)res.tv_usec / 1000000.0f >= time)
        return (true);
    return (false);
}

bool check_timer(socket_t socket, char **args, client_t *client,
    game_info_t game_info)
{
    check_incant(socket, game_info, client, args);
    if (client->graphic || (strcmp("GRAPHIC", args[0]) == 0 &&
        client->game_info.team_name == NULL))
        return (true);
    if (!timerisset(&client->timer)) {
        if (get_command_time(args[0]) == 0)
            return (true);
        gettimeofday(&client->timer, NULL);
    } else {
        if (is_time_elapsed(&client->timer,
            (float)(get_command_time(args[0])) / game_info->freq) == true) {
            timerclear(&client->timer);
            return (true);
        }
    }
    return (false);
}