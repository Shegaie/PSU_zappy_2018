/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/

#include <iostream>
#include <utility>
#include <zconf.h>
#include <sstream>
#include <time.h>
#include <fstream>
#include "ZappyGraphic/ZappyGraphic.hpp"
#include "ZappyGraphic.hpp"

std::vector<std::string> parseCommandAndArg(std::string command)
{
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    std::vector<std::string> parsedCommand;

    while ((pos = command.find(delimiter)) != std::string::npos) {
        token = command.substr(0, pos);
        parsedCommand.push_back(token);
        command.erase(0, pos + delimiter.length());
    }
    parsedCommand.push_back(command);
    return parsedCommand;
}

void ZappyGraphic::start(std::string serverIp, uint16_t port)
{
    std::vector<std::string> fullCommand;

    client.connectTo(std::move(serverIp), port);
    std::cout << client.getMessage();
    client.sendMessage("GRAPHIC\n");
    commandThread = std::thread(&ZappyGraphic::getCommand, this);
    while ((mapSize.x == 0 && mapSize.y == 0) || timeUnit == 0)
        executeCommand();
    initGraphic();
    while (libData.window.isOpen()) {
        if (mapSize.x - mapSize.y != 0) {
            std::cerr << "Sorry, graphic can only handle square map." << std::endl;
            break;
        }
        manageEvent();
        executeCommand();
        drawElement();
        libData.window.display();
        libData.window.clear(sf::Color::Black);
    }
    unlockThread();
}

void ZappyGraphic::getCommand()
{
    while (_isRunning) {
        cmdHdl.parseCommand(client.getMessage(), "\n");
    }
}


void ZappyGraphic::executeCommand()
{
    std::vector<std::string> &tmpStack = *cmdHdl.getStack();
    std::vector<std::string> command;

    if (tmpStack.empty())
        return;
    command = parseCommandAndArg(tmpStack[0]);
    auto iter = cmdDic.find(command[FUNC]);
    if (iter == cmdDic.end())
        return;
    (iter->second)(command, this);
    cmdHdl.popStack();
}

void ZappyGraphic::loadTexture(sf::Texture &texture, std::string path)
{
    try {
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Failed to load : " + path);
    } catch (std::runtime_error &e) {
        exit(84);
    }
}

void ZappyGraphic::initGraphic()
{
    sf::Texture tmpQ;
    float xWindow = TILE_SIZE * mapSize.x + (TILE_SIZE * mapSize.x * 1);
    float yWindow = static_cast<float>(TILE_SIZE * mapSize.y + (TILE_SIZE * mapSize.y * 0.3 * 1));
    sf::IntRect groundRect = {0, 0, TILE_SIZE, TILE_SIZE};

    srand(static_cast<unsigned int>(time(nullptr)));
    libData.window.create(sf::VideoMode(1920, 1080), "Zappy (SFML)");
    if (!libData.font.loadFromFile("./assets/zappy.TTF"))
        exit(84);
    loadTexture(libData.groundTexture, "./assets/grassBold.jpg");
    loadTexture(libData.backgroundTexture, "./assets/background.jpg");
    loadTexture(libData.incantationTexture, "./assets/incantation.png");
    loadTexture(libData.eggTexture, "./assets/egg.png");
    loadTexture(libData.respawnTexture, "./assets/flag.png");
    loadTexture(libData.levelTexture, "./assets/level.png");
    loadTexture(libData.expulsionTexture, "./assets/expulsion.png");
    loadTexture(libData.playerTexture, "./assets/thanos.png");
    loadTexture(libData.broadcastTexture, "./assets/broadcast.png");
    loadTexture(libData.modifTimeUnitTexture[0], "./assets/arrowLeft.png");
    loadTexture(libData.modifTimeUnitTexture[1], "./assets/arrowRight.png");
    modifTimeUnit[0].pos.x = static_cast<int>(xWindow / 2 + xWindow / 20);
    modifTimeUnit[0].pos.y = static_cast<int>(yWindow / 20);
    modifTimeUnit[1].pos.x = static_cast<int>(xWindow / 2 + xWindow / 10);
    modifTimeUnit[1].pos.y = static_cast<int>(yWindow / 20);
    libData.backgroundSprite.setTexture(libData.backgroundTexture);
    libData.backgroundSprite.scale(xWindow / 1920, yWindow / 1080);
    loadTexture(tmpQ, "./assets/q0.png");
    libData.qTexture.push_back(tmpQ);
    loadTexture(tmpQ, "./assets/q1.png");
    libData.qTexture.push_back(tmpQ);
    loadTexture(tmpQ, "./assets/q2.png");
    libData.qTexture.push_back(tmpQ);
    loadTexture(tmpQ, "./assets/q3.png");
    libData.qTexture.push_back(tmpQ);
    loadTexture(tmpQ, "./assets/q4.png");
    libData.qTexture.push_back(tmpQ);
    loadTexture(tmpQ, "./assets/q5.png");
    libData.qTexture.push_back(tmpQ);
    loadTexture(tmpQ, "./assets/q6.png");
    libData.qTexture.push_back(tmpQ);
    libData.camera = sf::View(sf::FloatRect(0, 0, xWindow, yWindow));
    libData.window.setView(libData.camera);
    for (int x = 0; x < mapSize.x; x++) {
        for (int y = 0; y < mapSize.y; y++) {
            tiles.push_back((tile_t){
                (vector2i){x, y},
                sf::Sprite(libData.groundTexture, groundRect),
                {}
            });
            tiles[(mapSize.x * x) + y].tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

tile_t ZappyGraphic::getClickedTile()
{
    sf::Vector2f mouse = libData.window.mapPixelToCoords(sf::Mouse::getPosition(libData.window));

    for (auto tile : getTiles()) {
        sf::FloatRect bounds = tile.tileSprite.getGlobalBounds();
        if (bounds.contains(mouse))
            return tile;
    }
    return (tile_t){(vector2i){-1, -1}, sf::Sprite(), {}};
}


void ZappyGraphic::verifyButtonClicked()
{
    sf::Vector2f mouse = libData.window.mapPixelToCoords(sf::Mouse::getPosition(libData.window));
    int i = 0;

    for (auto &button : modifTimeUnit) {
        sf::FloatRect bounds = button.sprite.getGlobalBounds();
        if (bounds.contains(mouse)) {
            button.state = CLICKED;
            timeUnit = (i == 0 ? timeUnit - 100 : timeUnit + 100);
            if (timeUnit < 0)
                timeUnit = 0;
            client.sendMessage("sst " + std::to_string(timeUnit) + "\n");
        }
        i++;
    }
}


void ZappyGraphic::verifyButtonHover()
{
    sf::Vector2f mouse = libData.window.mapPixelToCoords(sf::Mouse::getPosition(libData.window));

    for (auto &button : modifTimeUnit) {
        sf::FloatRect bounds = button.sprite.getGlobalBounds();
        if (bounds.contains(mouse))
            button.state = HOVER;
        else
            button.state = NONE;
    }
}

void ZappyGraphic::manageEvent()
{
    sf::Event event{};

    while (libData.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            libData.window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            tileToDisplay = getClickedTile();
            verifyButtonClicked();
        }
        if (event.type == sf::Event::MouseMoved)
            verifyButtonHover();
        if (event.type == sf::Event::MouseButtonReleased)
            for (auto &button : modifTimeUnit)
                button.state = NONE;
    }
}

void ZappyGraphic::drawResource(tile_t tile)
{
    for (unsigned int i = 0; i < tile.resource.size(); i++) {
        if (!tile.resource[i].empty()) {
            for (const auto &sprite : tile.resource[i])
                libData.window.draw(sprite);
        }
    }
}

void ZappyGraphic::drawInformation()
{
    sf::Vector2f windowSize = libData.window.getView().getSize();
    sf::RectangleShape background(sf::Vector2f(windowSize.x / 3, windowSize.y));
    sf::Vector2f backgroundPos((windowSize.x / 3) * 2, 0);
    colorText_t toWriteTile[] = {
        {"Tile", sf::Color(0, 0, 0, 255)},
        {"Food : ", sf::Color::White},
        {"Linemate : ", sf::Color::Blue},
        {"Deraumere : ", sf::Color::Green},
        {"Sibur : ", sf::Color::Yellow},
        {"Mendiane : ", sf::Color(255, 165, 0, 255)},
        {"Phiras : ", sf::Color::Red},
        {"Thystame : ", sf::Color::Magenta}
    };
    colorText_t toWritePlayer[] = {
        {"Player", sf::Color(0, 0, 0, 255)},
        {"Id : ", sf::Color::Cyan},
        {"Level : ", sf::Color::Green},
        {"Food : ", sf::Color::White},
        {"Linemate : ", sf::Color::Blue},
        {"Deraumere : ", sf::Color::Green},
        {"Sibur : ", sf::Color::Yellow},
        {"Mendiane : ", sf::Color(255, 165, 0, 255)},
        {"Phiras : ", sf::Color::Red},
        {"Thystame : ", sf::Color::Magenta}
    };

    background.setPosition(backgroundPos.x + (background.getSize().x * libData.animateDrawBackground), backgroundPos.y);
    background.setFillColor(sf::Color(150, 150, 150, 170));
    libData.window.draw(background);
    for (unsigned int i = 0; i < (sizeof(toWriteTile)/sizeof(*toWriteTile)); i++) {
        sf::Text text(toWriteTile[i].content, libData.font, static_cast<unsigned int>(mapSize.x * 3));
        text.setFillColor(toWriteTile[i].color);
        if (i == 0) {
            text.setPosition(backgroundPos.x + (background.getSize().x / 10) + (background.getSize().x * libData.animateDrawBackground), background.getSize().y / 30 + i * (background.getSize().y / 30));
            text.setStyle(sf::Text::Bold);
        } else {
            text.setPosition(backgroundPos.x + (background.getSize().x / 5) + (background.getSize().x * libData.animateDrawBackground), background.getSize().y / 30 + i * (background.getSize().y / 30));
            text.setString(text.getString() + std::to_string(tileToDisplay.resource[i - 1].size()));
        }
        libData.window.draw(text);
    }
    player_t player = getPlayerOnTile(tileToDisplay);
    if (player.id != -1) {
        for (unsigned int i = 0; i < (sizeof(toWritePlayer)/sizeof(*toWritePlayer)); i++) {
            sf::Text text(toWritePlayer[i].content, libData.font, static_cast<unsigned int>(mapSize.x * 3));
            text.setFillColor(toWritePlayer[i].color);
            if (i == 0) {
                text.setPosition(backgroundPos.x + (background.getSize().x / 10) + (background.getSize().x * libData.animateDrawBackground),background.getSize().y / 2 + background.getSize().y / 30 + i * (background.getSize().y / 30));
                text.setStyle(sf::Text::Bold);
            } else {
                text.setPosition(backgroundPos.x + (background.getSize().x / 5) + (background.getSize().x * libData.animateDrawBackground),background.getSize().y / 2 + background.getSize().y / 30 + i * (background.getSize().y / 30));
                if (i == 1)
                    text.setString(text.getString() + std::to_string(player.id));
                else if (i == 2)
                    text.setString(text.getString() + std::to_string(player.level));
                else
                    text.setString(text.getString() + std::to_string(player.resource[i - 3].size()));
            }
            libData.window.draw(text);
        }
    }
    if (tileToDisplay.pos.x == -1 && tileToDisplay.pos.y == -1 && libData.animateDrawBackground < 1)
        libData.animateDrawBackground += 0.05;
    else if (libData.animateDrawBackground > 0 && tileToDisplay.pos.x != - 1)
        libData.animateDrawBackground -= 0.05;
}

void ZappyGraphic::drawBanner()
{
    sf::Vector2f windowSize = libData.window.getView().getSize();
    sf::RectangleShape banner(sf::Vector2f(windowSize.x, windowSize.y / 5));
    sf::Vector2f bannerPos(0, windowSize.y - windowSize.y / 5);
    colorText_t toWriteTeam[teams.size()];
    int playerNumber = getPlayerNumber();
    colorText_t toWritePlayer[playerNumber];

    banner.setPosition(bannerPos);
    banner.setFillColor(sf::Color(150, 50, 0, 230));
    libData.window.draw(banner);
    for (unsigned int i = 0; i < teams.size(); i++) {
        toWriteTeam[i].content = teams[i].name;
        toWriteTeam[i].color = teams[i].color;
        sf::Text text(toWriteTeam[i].content, libData.font, static_cast<unsigned int>(mapSize.x * 4));
        text.setPosition(
            windowSize.x / 10 + (i * (windowSize.x / (teams.size() * 2))),
            bannerPos.y + banner.getSize().y / 10);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(toWriteTeam[i].color);
        libData.window.draw(text);
        for (unsigned int a = 0; a < teams[i].players.size(); a++) {
            toWritePlayer[a].content = "Player : " + std::to_string(teams[i].players[a].id);
            toWritePlayer[a].color = sf::Color::White;
            sf::Text textPlayer(toWritePlayer[a].content, libData.font, static_cast<unsigned int>(mapSize.x * 3 - teams[i].players.size()));
            textPlayer.setPosition(text.getPosition().x, banner.getSize().y / 4 + text.getPosition().y + a * (banner.getSize().y / (playerNumber + 1)));
            textPlayer.setFillColor(toWritePlayer[a].color);
            libData.window.draw(textPlayer);
        }
    }
}

void ZappyGraphic::drawPlayer()
{
    for (auto &team : teams) {
        for (auto egg : team.eggs) {
            sf::Sprite eggSprite(libData.eggTexture);
            sf::Vector2f eggPos(egg.pos.x * TILE_SIZE + 57, egg.pos.y * TILE_SIZE + 32);

            eggSprite.setPosition(eggPos.x, eggPos.y);
            eggSprite.setColor(team.color);
            libData.window.draw(eggSprite);
        }
        for (auto &respawn : team.respawns) {
            sf::Sprite respawnSprite(libData.respawnTexture);
            sf::Vector2f respawnPos(respawn.pos.x * TILE_SIZE + TILE_SIZE / 2, respawn.pos.y * TILE_SIZE - TILE_SIZE / 2 + 25);

            respawnSprite.setPosition(respawnPos.x, respawnPos.y);
            respawnSprite.setColor(team.color);
            libData.window.draw(respawnSprite);
        }
        for (auto &player : team.players) {
            sf::Sprite playerSprite(libData.playerTexture);
            sf::Vector2f playerPos(player.pos.x * TILE_SIZE, player.pos.y * TILE_SIZE);

            if (player.incantation)
                updateIncantation(player);
            playerSprite.setPosition(playerPos.x + libData.playerTexture.getSize().x / 2, playerPos.y + libData.playerTexture.getSize().y / 2);
            playerSprite.setOrigin(libData.playerTexture.getSize().x / 2, libData.playerTexture.getSize().y / 2);
            playerSprite.setRotation(player.orientation * 90);
            playerSprite.setColor(team.color);
            drawExpulsion(player);
            libData.window.draw(playerSprite);
            drawLevel(player);
        }
    }
}

void ZappyGraphic::drawTimeModification()
{
    sf::Text textTitle("Time unit", libData.font, static_cast<unsigned int>(
        mapSize.x * 3.5));
    textTitle.setFillColor(sf::Color::Black);
    textTitle.setPosition(
        modifTimeUnit[0].pos.x, modifTimeUnit[0].pos.y - libData.window.getView().getSize().y / 40);
    libData.window.draw(textTitle);
    for (int i = 0; i < 2 ; i++) {
        modifTimeUnit[i].sprite = sf::Sprite(
            libData.modifTimeUnitTexture[i], sf::IntRect(0, ARROW_HEIGHT / 3 * modifTimeUnit[i].state, ARROW_WIDTH, ARROW_HEIGHT / 3));
        modifTimeUnit[i].sprite.setPosition(modifTimeUnit[i].pos.x, modifTimeUnit[i].pos.y);
        libData.window.draw(modifTimeUnit[i].sprite);
    }
    sf::Text text(std::__cxx11::to_string(timeUnit), libData.font, static_cast<unsigned int>(
        mapSize.x * 3));
    text.setFillColor(sf::Color::Black);
    text.setPosition(
        modifTimeUnit[0].pos.x + libData.window.getView().getSize().x / 48, modifTimeUnit[0].pos.y + libData.window.getView().getSize().y / 200);
    libData.window.draw(text);
}

void ZappyGraphic::drawBroadcast()
{
    int i = 0;

    for (auto broadcast : broadcasts) {
        sf::Sprite broadcastSprite(libData.broadcastTexture);

        libData.broadcastScale += 0.05;
        broadcastSprite.scale(libData.broadcastScale, libData.broadcastScale);
        broadcastSprite.setPosition(broadcast.pos.x * TILE_SIZE + TILE_SIZE / 2, broadcast.pos.y * TILE_SIZE + TILE_SIZE / 2);
        broadcastSprite.setOrigin(225 / 2, 225 / 2);
        if (libData.broadcastScale > 3)
            libData.broadcastScale = 1;
        libData.window.draw(broadcastSprite);
        if (broadcast.clock.getElapsedTime().asSeconds() > 1)
            broadcasts.erase(broadcasts.begin() + i);
        i++;
    }
}

void ZappyGraphic::drawElement()
{
    libData.window.draw(libData.backgroundSprite);
    drawBanner();
    for (auto tile : tiles) {
        libData.window.draw(tile.tileSprite);
        drawResource(tile);
    }
    drawBroadcast();
    drawPlayer();
    drawInformation();
    drawTimeModification();
}


const vector2i &ZappyGraphic::getMapSize() const
{
    return mapSize;
}

void ZappyGraphic::setMapSize(const vector2i &mapSize)
{
    ZappyGraphic::mapSize = mapSize;
}

const std::vector<tile_t> &ZappyGraphic::getTiles() const
{
    return tiles;
}

void ZappyGraphic::setTiles(const std::vector<tile_t> &tiles)
{
    ZappyGraphic::tiles = tiles;
}

const std::vector<team_t> &ZappyGraphic::getTeams() const
{
    return teams;
}

void ZappyGraphic::setTeams(const std::vector<team_t> &teams)
{
    ZappyGraphic::teams = teams;
}

tile_t ZappyGraphic::getTile(int x, int y)
{
    tile_t defaultTile;

    for (auto &tile : tiles) {
        if (tile.pos.x == x && tile.pos.y == y)
            return (tile);
    }
    return defaultTile;
}

void ZappyGraphic::setTile(int xTarget, int yTarget, tile_t content)
{
    for (auto &tile : tiles) {
        if (tile.pos.x == xTarget && tile.pos.y == yTarget)
            tile = content;
    }
}

void ZappyGraphic::setTimeUnit(int timeUnit)
{
    ZappyGraphic::timeUnit = timeUnit;
}

const libData_t &ZappyGraphic::getLibData() const
{
    return libData;
}

void ZappyGraphic::addPlayer(std::string teamName, player_t newPlayer)
{
    for (auto &team : teams) {
        if (team.name == teamName) {
            team.players.push_back(newPlayer);
        }
    }
}

void ZappyGraphic::setPlayer(int id, player_t playerData)
{
    for (auto &team : teams) {
        for (auto &player : team.players)
            if (player.id == id)
                player = playerData;
    }
}

int ZappyGraphic::getPlayerNumber() const
{
    int playerNumber = 0;

    for (auto team : teams) {
        for (auto player : team.players) {
            playerNumber++;
        }
    }
    return playerNumber;
}

void ZappyGraphic::removePlayer(int id)
{
    for (auto &team : teams) {
        int i = 0;
        for (auto &player : team.players) {
            if (player.id == id)
                team.players.erase(team.players.begin() + i);
            i++;
        }
    }
}

player_t ZappyGraphic::getPlayer(int id)
{
    player_t defaultPlayer = player_t();

    for (auto &team : teams) {
        for (auto &player : team.players)
            if (player.id == id)
                return (player);
    }
    return defaultPlayer;
}

player_t ZappyGraphic::getPlayerOnTile(tile_t tileToDisplay)
{
    for (auto &team : teams) {
        for (auto &player : team.players)
            if (player.pos.x == tileToDisplay.pos.x && player.pos.y == tileToDisplay.pos.y)
                return (player);
    }
    return player_t();
}

void ZappyGraphic::updateIncantation(player_t player)
{
    if (player.incantation > -1) {
        std::vector<sf::Color> Colors = {{}, {100, 250, 100}, {50, 100, 150}, {200, 200, 100}, {100, 150, 200}, {0, 150, 100}, {0, 0, 0}, {250, 250, 250}, {150, 150, 150}};
        sf::Sprite incantationSprite(libData.incantationTexture);

        incantationSprite.setPosition(player.pos.x * TILE_SIZE + TILE_SIZE / 2, player.pos.y * TILE_SIZE + TILE_SIZE / 2);
        incantationSprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
        incantationSprite.setRotation(libData.incantationRotation);
        libData.incantationRotation += 2;
        incantationSprite.setColor(Colors[player.incantation]);
        libData.window.draw(incantationSprite);
    }
}

void ZappyGraphic::addEgg(std::string teamName, egg_t newEgg)
{
    for (auto &team : teams) {
        if (team.name == teamName) {
            team.eggs.push_back(newEgg);
        }
    }
}

std::string ZappyGraphic::getTeam(int id)
{
    for (auto &team : teams) {
        for (auto &playerTmp : team.players) {
            if (id == playerTmp.id)
                return team.name;
        }
    }
    return {};
}

void ZappyGraphic::removeEgg(int id)
{
    for (auto &team : teams) {
        int i = 0;
        for (auto &egg : team.eggs) {
            if (egg.id == id)
                team.eggs.erase(team.eggs.begin() + i);
            i++;
        }
    }
}


void ZappyGraphic::addBroadcast(broadcast_t _broadcast)
{
    broadcasts.push_back(_broadcast);
}

void ZappyGraphic::unlockThread()
{
    _isRunning = false;
    client.sendMessage("msz\n");
    commandThread.join();
}

player_t ZappyGraphic::getPlayer(int x, int y)
{
    for (auto &team : teams) {
        for (auto &player : team.players)
            if (player.pos.x == x && player.pos.y == y)
                return player;
    }
    return player_t();
}

egg_t ZappyGraphic::getEgg(int id)
{
    for (auto &team : teams) {
        for (auto &egg : team.eggs)
            if (egg.id == id)
                return egg;
    }
    return egg_t();
}

void ZappyGraphic::addRespawn(std::string teamName, respawn_t newRespawn)
{
    for (auto &team : teams) {
        if (team.name == teamName) {
            team.respawns.push_back(newRespawn);
        }
    }
}

void ZappyGraphic::removeRespawn(int id)
{
    for (auto &team : teams) {
        int i = 0;
        for (auto &respawn : team.respawns) {
            if (respawn.id == id)
                team.respawns.erase(team.respawns.begin() + i);
            i++;
        }
    }
}

void ZappyGraphic::drawLevel(player_t &player)
{
    if (player.levelShow) {
        if (!player.clockIsStarted) {
            player.clock.restart();
            player.clockIsStarted = true;
        }
        sf::IntRect rect = {(player.level - 1) * 125, 0, 125, 125};
        sf::Sprite levelSprite(libData.levelTexture);
        sf::Int32 time = player.clock.getElapsedTime().asMilliseconds();
        levelSprite.setPosition(player.pos.x * TILE_SIZE, player.pos.y * TILE_SIZE - 20);
        levelSprite.setTextureRect(rect);
        if (time > 3000) {
            player.levelShow = false;
            player.clockIsStarted = false;
        } else if (time < 50)
            levelSprite.scale(0.1, 0.1);
        else if (time < 100)
            levelSprite.scale(0.2, 0.2);
        else if (time < 150)
            levelSprite.scale(0.3, 0.3);
        else if (time < 200)
            levelSprite.scale(0.4, 0.4);
        else if (time < 250)
            levelSprite.scale(0.6, 0.6);
        else if (time < 300)
            levelSprite.scale(0.8, 0.8);
        else
            levelSprite.scale(1, 1);
        libData.window.draw(levelSprite);
    }
}

void ZappyGraphic::drawExpulsion(player_t &player)
{
    if (player.expulsionShow) {
        if (!player.clockExpulsionIsStarted) {
            player.expulsionClock.restart();
            player.clockExpulsionIsStarted = true;
        }
        sf::IntRect rect = libData.expulsionRect;
        sf::Sprite expulsionSprite(libData.expulsionTexture);
        expulsionSprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
        expulsionSprite.setPosition(player.pos.x * TILE_SIZE + TILE_SIZE / 2, player.pos.y * TILE_SIZE + TILE_SIZE / 2);
        expulsionSprite.setRotation(player.orientation * 90 + 270);
        sf::Int32 time = player.expulsionClock.getElapsedTime().asMilliseconds();
        if (time >= 67) {
            rect.left += 225;
            libData.expulsionRect = rect;
            player.expulsionClock.restart();
        }
        expulsionSprite.setTextureRect(rect);
        libData.window.draw(expulsionSprite);
        if (rect.left >= 3100) {
            player.expulsionShow = false;
            player.clockExpulsionIsStarted = false;
            libData.expulsionRect.left = 0;
        }
    }
}