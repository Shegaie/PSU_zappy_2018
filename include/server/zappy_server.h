/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#pragma once

/* Includes */
#include <arpa/inet.h>
#include "map.h"
#include "client.h"

/* Return values */
#define ERROR (-1)
#define SUCCESS 0
#define EXIT_ERROR 84

/* Useful */
#define UNUSED __attribute__((unused))
#define MAX(x, y) (((x) >= (y)) ? (x) : (y))
#define MIN(x, y) (((x) <= (y)) ? (x) : (y))

typedef struct socket_s *socket_t;

struct socket_s {
    int socket_fd;
    client_t client_list;
    fd_set clients_fd;
    int max_fd;
    bool running;
};