#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <stdbool.h>


typedef struct {
    int playerX, playerY;
    int space_fuel;
    int junk_collected;
} Spaceship;

typedef struct {
    int AsteroidX, AsteroidY;
} Asteroid;

typedef struct {
    char map[30][30];
    Spaceship ship;
    Asteroid asteroid[6];
    int junk_count;
    int gameDifficulty;
    int numberOfAsteroid;
} Game;

extern int map_raw , map_col;
extern int target_junk , fuel_consumption;
extern Game spaceGame;
extern Spaceship space;

void getGameDifficulty(Game *spaceGame);
void printHeader(Game *spaceGame);
void readIntro();
void generateMap(Game *spaceGame );
void createSpaceShip(Spaceship *space ,Game *spaceGame);
void createAsteroids(Game *spaceGame);
bool isValidPos(int x , int y);
void distibuteJunks(Game *spaceGame);
void printMap(Game *spaceGame);
void startGame(Game *spaceGame);
bool checkCollision(Game *spaceGame);
void updateAsteroidLocations(Game *spaceGame ,int numberOfAsteroids);


#endif // GAME_H_INCLUDED
