/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/client.h"
#include "unit_test.h"

Test(client, init_client, .init=redirect_all_stdout)
{
    client_t client = {0};
    client_t *client_null = NULL;

    init_client(client_null, 0);
    init_client(&client, 0);
    cr_assert(client.next == NULL, "Client next to NULL");
    cr_assert(client.commands[0] == NULL, "Client commands to NULL");
    cr_assert(client.graphic == false, "Set client in player mode by defautlt");
    cr_assert(client.game_info.team_name == NULL, "Team name NULL");
    cr_assert(client.game_info.level == 1, "Level to 1");
    cr_assert(client.game_info.x == 0, "X pos to 0");
    cr_assert(client.game_info.y == 0, "Y pos to 0");
    cr_assert(client.game_info.orientation == NORTH, "Orientation to NORTH");
    cr_assert(client.game_info.inventory[FOOD] == 10, "Set 10 food");
}

Test(client, free_client, .init=redirect_all_stdout)
{
    client_t *client = malloc(sizeof(client_t));

    free_client(NULL);
    free_client(client);
}

Test(client, add_client, .init=redirect_all_stdout)
{
    client_t client;
    client_t *created_client = NULL;

    init_client(&client, 0);
    created_client = add_client(&client, 0);
    cr_assert(created_client != NULL, "Check if add client return client");
    cr_assert(client.next != NULL,
        "Check if the new client is added to the chained list");
    free_client(created_client);
    cr_assert(add_client(NULL, 0) == NULL, "Send Null chained list");
}

Test(client, remove_client, .init=redirect_all_stdout)
{
    client_t client;

    init_client(&client, 0);
    add_client(&client, 1);
    remove_client(&client, 1);
    cr_assert(client.next == NULL, "Check if client is remove");
    remove_client(NULL, 1);
}

Test(client, clear_list, .init=redirect_all_stdout)
{
    client_t client;

    init_client(&client, 0);
    add_client(&client, 1);
    clear_list(&client);
    cr_assert(client.next == NULL, "Check if clients are clear");
}