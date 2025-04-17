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



#endif // GAME_H_INCLUDED
