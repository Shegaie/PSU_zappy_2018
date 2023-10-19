/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/

#include <iostream>
#include <stdlib.h>
#include "ZappyGraphic/ZappyGraphic.hpp"
#include "cmdFunction.hpp"

bool isNumber(std::string basic_string)
{
    for (char c : basic_string) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

void msz(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 3 ||
        (!isNumber(fullCommand[1]) || !isNumber(fullCommand[2])))
        return;
    zappy->setMapSize(
        (vector2i){std::stoi(fullCommand[1]), std::stoi(fullCommand[2])});
}

void bct(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 10)
        return;
    for (unsigned int i = 0; i < fullCommand.size(); i++) {
        if (!isNumber(fullCommand[i]) && i != 0)
            return;
    }
    sf::IntRect resourcesRect = {0, 0, RESOURCE_SIZE, RESOURCE_SIZE};
    tile_t tile = zappy->getTile(std::stoi(fullCommand[1]),
        std::stoi(fullCommand[2]));
    for (int j = 3; j < 10; j++) {
        std::vector<sf::Sprite> tmpQ;
        for (int i = 0; i < std::stoi(fullCommand[j]); i++) {
            tmpQ.emplace_back(zappy->getLibData().qTexture[j - 3], resourcesRect);
            tmpQ[i].setPosition(
                TILE_SIZE * tile.pos.x + (std::rand() % (TILE_SIZE - RESOURCE_SIZE)),
                TILE_SIZE * tile.pos.y +
                    (std::rand() % (TILE_SIZE - RESOURCE_SIZE)));
            tile.resource[j - 3] = tmpQ;
        }
    }
    zappy->setTile(std::stoi(fullCommand[1]), std::stoi(fullCommand[2]), tile);
}

void tna(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    std::vector<team_t> teams = zappy->getTeams();

    if (fullCommand.size() != 2)
        return;
    teams.push_back((team_t){fullCommand[1],
        std::vector<player_t>(),
        std::vector<egg_t>(),
        std::vector<respawn_t>()});
    zappy->setTeams(teams);
}

void pnw(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 7)
        return;
    player_t player;
    player.id = std::stoi(fullCommand[1]);
    player.pos = (vector2i){
        std::stoi(fullCommand[2]),
        std::stoi(fullCommand[3])
    };
    player.orientation = std::stoi(fullCommand[4]);
    if (player.orientation == 1)
        player.orientation = 0;
    else if (player.orientation == 2)
        player.orientation = 3;
    else if (player.orientation == 3)
        player.orientation = 2;
    else if (player.orientation == 4)
        player.orientation = 1;
    player.level = std::stoi(fullCommand[5]);
    zappy->addPlayer(fullCommand[6], player);
}

void ppo(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 5)
        return;
    player_t player = zappy->getPlayer(std::stoi(fullCommand[1]));
    player.pos = (vector2i){std::stoi(fullCommand[2]), std::stoi(fullCommand[3])};
    player.orientation = std::stoi(fullCommand[4]);
    if (player.orientation == 1)
        player.orientation = 0;
    else if (player.orientation == 2)
        player.orientation = 3;
    else if (player.orientation == 3)
        player.orientation = 2;
    else if (player.orientation == 4)
        player.orientation = 1;
    zappy->setPlayer(player.id, player);
}

void plv(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 3)
        return;
    player_t player = zappy->getPlayer(std::stoi(fullCommand[1]));
    player.level = std::stoi(fullCommand[2]);
    zappy->setPlayer(player.id, player);
}

void pin(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 11)
        return;
    player_t player = zappy->getPlayer(std::stoi(fullCommand[1]));
    for (int i = 0; i < 7; i++) {
        player.resource[i].clear();
        for (int j = 0; j < std::stoi(fullCommand[i + 4]); j++) {
            player.resource[i].push_back(
                sf::Sprite(zappy->getLibData().qTexture[i]));
        }
    }
    zappy->setPlayer(player.id, player);
}

void pex(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    player_t player = zappy->getPlayer(std::stoi(fullCommand[1]));
    player.expulsionShow = true;
    zappy->setPlayer(player.id, player);
}

void pbc(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    player_t player = zappy->getPlayer(std::stoi(fullCommand[1]));
    broadcast_t broadcast = {player.pos, sf::Clock()};

    broadcast.clock.restart();
    zappy->addBroadcast(broadcast);
}

void pic(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    player_t player = zappy->getPlayer(std::stoi(fullCommand[4]));
    player.incantation = std::stoi(fullCommand[3]);
    zappy->setPlayer(player.id, player);
}

void pie(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    player_t player = zappy->getPlayer(std::stoi(fullCommand[1]), std::stoi(fullCommand[2]));
    player.incantation = -1;
    if (std::stoi(fullCommand[3]) == 1)
        player.levelShow = true;
    zappy->setPlayer(player.id, player);
}

void pfk(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void pdr(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void pgt(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void pdi(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 2)
        return;
    zappy->removePlayer(std::stoi(fullCommand[1]));
}

void enw(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    egg_t egg;
    player_t playerTmp = zappy->getPlayer(std::stoi(fullCommand[2]));
    std::string teamString = zappy->getTeam(playerTmp.id);

    if (teamString.size() != 0) {
        egg.id = std::stoi(fullCommand[1]);
        egg.playerId = std::stoi(fullCommand[2]);
        egg.pos.x = playerTmp.pos.x;
        egg.pos.y = playerTmp.pos.y;
        zappy->addEgg(teamString, egg);
    }
}

void eht(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    respawn_t respawn;
    player_t playerTmp = zappy->getPlayer(zappy->getEgg(std::stoi(fullCommand[1])).playerId);

    respawn.id = zappy->getEgg(std::stoi(fullCommand[1])).id;
    respawn.pos = zappy->getEgg(std::stoi(fullCommand[1])).pos;
    zappy->addRespawn(zappy->getTeam(playerTmp.id), respawn);
    zappy->removeEgg(std::stoi(fullCommand[1]));
}

void ebo(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    zappy->removeRespawn(std::stoi(fullCommand[1]));
}

void edi(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
    zappy->removeEgg(std::stoi(fullCommand[1]));
}

void sgt(std::vector<std::string> fullCommand, ZappyGraphic *zappy)
{
    if (fullCommand.size() != 2)
        return;
    if (!isNumber(fullCommand[1]))
        return;
    zappy->setTimeUnit(std::stoi(fullCommand[1]));
}

void sst(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void seg(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void smg(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void suc(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}

void sbp(UNUSED std::vector<std::string> fullCommand, UNUSED ZappyGraphic *zappy)
{
}
