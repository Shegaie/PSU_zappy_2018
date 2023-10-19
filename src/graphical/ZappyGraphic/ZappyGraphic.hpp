/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/
#ifndef GRAPHICAL_ZAPPYGRAPHIC_HPP
#define GRAPHICAL_ZAPPYGRAPHIC_HPP

#include <vector>
#include <thread>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <mutex>
#include "Network/TCPClient.hpp"
#include "Command/CommandHandler.hpp"
#include "Command/cmdFunction.hpp"

#define UNUSED __attribute__((unused))
#define FUNC 0
#define WIDTH_WINDOW 1920
#define HEIGHT_WINDOW 1080
#define ORIGIN_X WIDTH_WINDOW / 2
#define ORIGIN_Y HEIGHT_WINDOW / 2
#define TILE_SIZE 225
#define RESOURCE_SIZE TILE_SIZE / 7
#define NONE 0
#define HOVER 1
#define CLICKED 2
#define ARROW_WIDTH 44
#define ARROW_HEIGHT 192

struct colorText_t {
    std::string content;
    sf::Color color;
};

struct vector2i {
    int x;
    int y;
};

struct tile_t {
    vector2i pos = {0, 0};
    sf::Sprite tileSprite;
    std::unordered_map<int, std::vector<sf::Sprite>> resource;
};

struct player_t {
    int id = -1;
    vector2i pos;
    int orientation;
    int incantation = -1;
    int level;
    std::unordered_map<int, std::vector<sf::Sprite>> resource;
    bool levelShow = false;
    bool expulsionShow = false;
    bool clockIsStarted = false;
    bool clockExpulsionIsStarted = false;
    sf::Clock clock;
    sf::Clock expulsionClock;
};

struct respawn_t {
    int id;
    vector2i pos;
};

struct broadcast_t {
    vector2i pos;
    sf::Clock clock;
};

struct egg_t {
    int id;
    int playerId;
    vector2i pos;
};

struct button_t {
    int state = NONE;
    vector2i pos = {0, 0};
    sf::Sprite sprite;
};

struct team_t {
    std::string name;
    std::vector<player_t> players;
    std::vector<egg_t> eggs;
    std::vector<respawn_t> respawns;
    sf::Color color = sf::Color(
        static_cast<sf::Uint8>(std::rand() % 255),
        static_cast<sf::Uint8>(std::rand() % 255),
        static_cast<sf::Uint8>(std::rand() % 255));
};

struct libData_t {
    sf::RenderWindow window;
    sf::Font font;
    sf::View camera;
    sf::Texture groundTexture;
    sf::Texture backgroundTexture;
    sf::Texture incantationTexture;
    sf::Texture playerTexture;
    sf::Texture broadcastTexture;
    sf::Texture eggTexture;
    sf::Texture respawnTexture;
    sf::Texture levelTexture;
    sf::Texture modifTimeUnitTexture[2];
    sf::Texture expulsionTexture;
    sf::Sprite backgroundSprite;
    float animateDrawBackground = 1;
    int incantationRotation = 0;
    float broadcastScale = 0;
    sf::IntRect expulsionRect = {0, 0, 225, 212};
    std::vector<sf::Texture> qTexture;
};

class ZappyGraphic {
    public:
        void start(std::string serverIp, uint16_t port);
        void getCommand();
        void unlockThread();
        void executeCommand();
        void initGraphic();
        void loadTexture(sf::Texture &texture, std::string path);
        void drawElement();
        void drawResource(tile_t tile);
        void drawInformation();
        void drawBanner();
        void drawPlayer();
        void drawBroadcast();
        void drawLevel(player_t &player);
        void drawExpulsion(player_t &player);
        void drawTimeModification();

        //Event method
        void manageEvent();
        tile_t getClickedTile();
        player_t getPlayerOnTile(tile_t tileToDisplay);
        void verifyButtonClicked();
        void verifyButtonHover();
        //Getter and Setter
        const vector2i &getMapSize() const;
        void setMapSize(const vector2i &mapSize);
        const std::vector<tile_t> &getTiles() const;
        tile_t getTile(int x, int y);
        void setTiles(const std::vector<tile_t> &tiles);
        void setTile(int xTarget, int yTarget, tile_t content);
        const std::vector<team_t> &getTeams() const;
        void setTeams(const std::vector<team_t> &teams);
        void setTimeUnit(int timeUnit);
        void addPlayer(std::string teamName, player_t newPlayer);
        void addBroadcast(broadcast_t _broadcast);
        void setPlayer(int id, player_t playerData);
        void addEgg(std::string teamName, egg_t newEgg);
        void addRespawn(std::string teamName, respawn_t newRespawn);
        egg_t getEgg(int id);
        void removePlayer(int id);
        void removeEgg(int id);
        void removeRespawn(int id);
        player_t getPlayer(int id);
        player_t getPlayer(int x, int y);
        const libData_t &getLibData() const;
        int getPlayerNumber() const;
        void updateIncantation(player_t player);
        std::string getTeam(int id);

    private:
        TCPClient client;
        CommandHandler cmdHdl;
        std::thread commandThread;
        libData_t libData;
        bool _isRunning = true;

        //Graphic
        vector2i mapSize = {0, 0};
        std::vector<tile_t> tiles;
        std::vector<team_t> teams;
        std::vector<broadcast_t> broadcasts;
        button_t modifTimeUnit[2];
        tile_t tileToDisplay = {(vector2i){-1, -1}, sf::Sprite(), {}};
        int timeUnit = 0;
};

typedef void (*cmdFunction)(std::vector<std::string>, ZappyGraphic *);

const std::unordered_map<std::string, cmdFunction> cmdDic({
        {"msz", &msz}, {"bct", &bct}, {"tna", &tna}, {"pnw", &pnw},
        {"ppo", &ppo}, {"plv", &plv}, {"pin", &pin}, {"pex", &pex},
        {"pbc", &pbc}, {"pic", &pic}, {"pie", &pie}, {"pfk", &pfk},
        {"pdr", &pdr}, {"pgt", &pgt}, {"pdi", &pdi}, {"enw", &enw},
        {"eht", &eht}, {"ebo", &ebo}, {"edi", &edi}, {"sgt", &sgt},
        {"sst", &sst}, {"seg", &seg}, {"smg", &smg}, {"suc", &suc},
        {"sbp", &sbp}
});


#endif //GRAPHICAL_ZAPPYGRAPHIC_HPP
