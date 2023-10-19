/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Pierre Chaudron
*/

#pragma once

typedef struct command_time_s {
    const char *command;
    const int time;
} command_time_t;

static const command_time_t COMMAND_TIMES[] = {
    {"Inventory", 1},
    {"Broadcast", 7},
    {"Connect_nbr", 0},
    {"Left", 7},
    {"Right", 7},
    {"Forward", 7},
    {"Look", 7},
    {"Set", 7},
    {"Take", 7},
    {"Eject", 7},
    {"Fork", 42},
    {"Incantation", 300},
    {NULL, 0}
};