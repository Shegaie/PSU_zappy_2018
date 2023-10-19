/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/parse.h"
#include "server/init.h"
#include "unit_test.h"

Test(init, create_socket, .init=redirect_all_stdout)
{
    cr_assert(create_socket() != ERROR, "Create socket");
}

Test(init, bind_socket, .init=redirect_all_stdout)
{
    int fd = create_socket();

    cr_assert(bind_socket(100, 0) == ERROR, "Invalid port");
    cr_assert(bind_socket(4242, 0) == ERROR, "Invalid socket fd");
    cr_assert(bind_socket(4242, fd) == SUCCESS, "Bind socket");
}

Test(init, init_listen, .init=redirect_all_stdout)
{
    int fd = create_socket();

    cr_assert(init_listen(0, 0) == ERROR, "Invalid socket fs");
    cr_assert(init_listen(fd, -42) == SUCCESS, "Try list with negative number");
    cr_assert(init_listen(fd, 5) == SUCCESS, "Listen");
}

Test(init, init_socket, .init=redirect_all_stdout)
{
    socket_t socket = NULL;

    cr_assert(init_socket(80, 0) == NULL, "Invalid port");
    socket = init_socket(4242, 0);
    cr_assert(socket != NULL, "Create socket");
}