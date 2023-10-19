/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "server/zappy_server.h"

int create_socket(void)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM,
        getprotobyname("TCP")->p_proto);

    if (socket_fd == ERROR) {
        perror("Socket Init ");
        return (ERROR);
    }
    return (socket_fd);
}

int bind_socket(const int port, const int socket_fd)
{
    int bind_ret = 0;
    struct sockaddr_in sin = {0};
    int yes = 1;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) ==
        ERROR) {
        return (ERROR);
    }
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    bind_ret = bind(socket_fd, (struct sockaddr *)&sin,
        sizeof(struct sockaddr_in));
    if (bind_ret == -1) {
        perror("Socket Bind ");
        return (ERROR);
    }
    return (SUCCESS);
}

int init_listen(const int socket_fd, const int max_players)
{
    if (listen(socket_fd, max_players) == ERROR) {
        perror("Listen ");
        return (ERROR);
    }
    return (SUCCESS);
}

socket_t init_socket(const int port, const int max_players)
{
    socket_t socket = NULL;

    socket = malloc(sizeof(struct socket_s));
    if (socket == NULL)
        return (NULL);
    socket->socket_fd = create_socket();
    if (socket->socket_fd == ERROR) {
        free(socket);
        return (NULL);
    }
    if (bind_socket(port, socket->socket_fd) == ERROR) {
        free(socket);
        return (NULL);
    }
    if (init_listen(socket->socket_fd, max_players) == ERROR) {
        free(socket);
        return (NULL);
    }
    printf("Port : %d\n", port);
    return (socket);
}