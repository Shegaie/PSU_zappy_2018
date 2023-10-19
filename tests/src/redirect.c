/*
** EPITECH PROJECT, 2022
** NWP_myftp_2018
** File description:
** Created by Steeven Regnault
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}