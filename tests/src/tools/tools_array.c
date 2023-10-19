/*
** EPITECH PROJECT, 2022
** PSU_zappy_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include "server/zappy_server.h"
#include "server/tools.h"
#include "unit_test.h"

Test(tools, array_contain_same, .init=redirect_all_stdout)
{
    char *args[5] = {"1", "2", "3", NULL, NULL};

    cr_assert(contain_same_str(args) == false, "Doesn't contain same str");
    cr_assert(contain_same_str(NULL) == false, "NULL arg");
    args[3] = "1";
    cr_assert(contain_same_str(args) == true, "Contain same str");
}

Test(tools, free_arr_content, .init=redirect_all_stdout)
{
    char *args[6] = {NULL};

    for (int i = 0; i < 5; i++) {
        args[i] = strdup("Hello");
        if (args[i] == NULL)
            return;
    }
    args[5] = NULL;
    free_arr_content((void **)args);
    free_arr_content(NULL);
}

Test(tools, arr_len, .init=redirect_all_stdout)
{
    char *args[5] = {"1", "2", "3", "4", NULL};
    char *arg[2] = {"1", NULL};

    cr_assert(arr_len(NULL) == 0, "NULL");
    cr_assert(arr_len((void *)arg) == 1, "Array of size 1");
    cr_assert(arr_len((void *)args) == 4, "Array of size 4");
}

Test(tools, array_occurs, .init=redirect_all_stdout)
{
    char *args[5] = {"1", "2", "2", "4", NULL};
    char *arg[2] = {"1", NULL};

    cr_assert(array_occurs(NULL, NULL) == ERROR, "NULL array and NULL str");
    cr_assert(array_occurs(arg, NULL) == ERROR, "NULL str");
    cr_assert(array_occurs(NULL, "1") == ERROR, "NULL array");
    cr_assert(array_occurs(args, "1") == 1, "Contain 1");
    cr_assert(array_occurs(args, "2") == 2, "Contain 2");
    cr_assert(array_occurs(args, "ZAPPO") == 0, "Doesn't contain");
    cr_assert(array_occurs(arg, "1") == 1, "Array of size 1");
}
