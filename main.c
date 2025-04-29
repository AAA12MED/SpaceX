#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
int main()
{
    srand(time(NULL));
    readIntro();
    getGameDifficulty(&spaceGame); //call game difficulty
    createSpaceShip(&space , &spaceGame);
    createAsteroids(&spaceGame);
    distibuteJunks(&spaceGame);
    generateMap(&spaceGame);
    printHeader(&spaceGame);
    printMap(&spaceGame);
    startGame(&spaceGame);
    return 0;
}


