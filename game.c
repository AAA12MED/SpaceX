#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int map_raw , map_col ;
int target_junk , fuel_consumption ;
Game spaceGame;
Spaceship space;

void readIntro()
{
FILE *introFile = fopen("intro.txt", "r");
    char line[512];

    if (introFile == NULL) {
        printf("File not exist ERROR can't load the game.\n");
    }
    else
    {
       while (fgets(line, sizeof(line), introFile))
        printf("%s", line);

    }

    fclose(introFile);
    printf("\n press Enter key to start the game ");
    getchar();
    //system("cls");;
}

void getGameDifficulty(Game *spaceGame)
{
    printf("Choose game difficulty from 1 to 3 \n");
    scanf("%d",&spaceGame->gameDifficulty);
    if(spaceGame->gameDifficulty <1 || spaceGame->gameDifficulty >3)
    {
      printf("Invalid Input Try again\n");
      getGameDifficulty(spaceGame);
    }
    switch(spaceGame->gameDifficulty)
    {
        case 1 : map_raw=18 ; map_col=18 ; spaceGame->numberOfAsteroid =2; spaceGame->junk_count=15 ; ;target_junk=10; fuel_consumption=2  ;break;
        case 2 : map_raw=24 ; map_col=24 ; spaceGame->numberOfAsteroid =4; spaceGame->junk_count=25 ; target_junk=15 ; fuel_consumption=4   ;break;
        case 3 : map_raw=30 ; map_col=30 ; spaceGame->numberOfAsteroid =6; spaceGame->junk_count=35 ;target_junk=25  ; fuel_consumption=6  ;break;
    }

}
void createAsteroids(Game *spaceGame)
{

    for (int i = 0; i < 6; i++) {
    spaceGame->asteroid[i].AsteroidX = -1;
    spaceGame->asteroid[i].AsteroidY = -1;
}

    int numberOfAsteroid =spaceGame->numberOfAsteroid ;


    int midR = map_raw / 2;
    int midC = map_col / 2;


    if (spaceGame->numberOfAsteroid >= 2)
    {
        spaceGame->asteroid[0].AsteroidX = 0;
        spaceGame->asteroid[0].AsteroidY = 0;

        spaceGame->asteroid[1].AsteroidX = 0;
        spaceGame->asteroid[1].AsteroidY = map_col - 1;
    }

    if (spaceGame->numberOfAsteroid >= 4)
    {
        spaceGame->asteroid[2].AsteroidX = midR;
        spaceGame->asteroid[2].AsteroidY = 0;

        spaceGame->asteroid[3].AsteroidX = 0;
        spaceGame->asteroid[3].AsteroidY = midC;
    }

    if (spaceGame->numberOfAsteroid == 6)
    {
        spaceGame->asteroid[4].AsteroidX = 3;
        spaceGame->asteroid[4].AsteroidY = 0;

        spaceGame->asteroid[5].AsteroidX = map_raw - 3;
        spaceGame->asteroid[5].AsteroidY = 0;
    }

}
void createSpaceShip(Spaceship *space ,Game *spaceGame)
{
    space->junk_collected=0;
    space->space_fuel=100;
    int p_x = rand() % map_raw;
    int p_y = rand() % map_col;
    space->playerX=p_x;
    space->playerY=p_y;

    spaceGame->ship=*space; //check
}
void distibuteJunks(Game *spaceGame)
{
    for (int i =0 ; i < spaceGame->junk_count ; i++ )
    {
      int j_x = rand() % map_raw;
      int j_y = rand() % map_col;

      if (spaceGame->map[j_x][j_y] != 'S' || spaceGame->map[j_x][j_y] != 'A')
        spaceGame->map[j_x][j_y]='J';
    }

}
void generateMap(Game *spaceGame )
{
  for (int i =0 ; i < map_raw ; i++)
  {
      for (int j=0 ; j < map_col ; j++)
      {
         if( (i== spaceGame->ship.playerX && j== spaceGame->ship.playerY) )
         {
            if(spaceGame->map[i][j]=='J')
               {
                spaceGame->ship.junk_collected++;
                spaceGame->ship.space_fuel +=5;
               }
             spaceGame->map[i][j]='S';
         }
         else if ((i== spaceGame->asteroid[0].AsteroidX && j== spaceGame->asteroid[0].AsteroidY)
              || (i== spaceGame->asteroid[1].AsteroidX && j== spaceGame->asteroid[1].AsteroidY)
              || (i== spaceGame->asteroid[2].AsteroidX && j== spaceGame->asteroid[2].AsteroidY)
              || (i== spaceGame->asteroid[3].AsteroidX && j== spaceGame->asteroid[3].AsteroidY)
              || (i== spaceGame->asteroid[4].AsteroidX && j== spaceGame->asteroid[4].AsteroidY)
              || (i== spaceGame->asteroid[5].AsteroidX && j== spaceGame->asteroid[5].AsteroidY)
                   )
                   {
                     spaceGame->map[i][j]='A';
                   }

        else if(spaceGame->map[i][j]=='J')
        {

        }
        else
         spaceGame->map[i][j]='.';
      }
  }



}
void printHeader(Game *spaceGame )
{



    printf("**********************************************************************************************************************\n");
    printf("Fuel Crisis Adventure Game \n Difficulty is : %d - Size: %d x %d -- Target Junk : %d -- Collected Junk : %d -- Fuel Level : %d \n" ,spaceGame->gameDifficulty,map_raw,map_col ,target_junk ,spaceGame->ship.junk_collected, spaceGame->ship.space_fuel);
    printf("**********************************************************************************************************************\n");
}
void printMap(Game *spaceGame)
{
for (int i =0 ; i < map_raw ; i++)
  {
      for ( int j=0 ; j < map_col ; j++)
      {
        printf("%c ", spaceGame->map[i][j]);
      }
      printf("\n");
  }
}
void startGame(Game *spaceGame)
{
    while(1)
    {
        bool validLetter= true;
        char move;
        int ship_x=spaceGame->ship.playerX;
        int ship_y=spaceGame->ship.playerY;
        printf("Enter W / A / S / D : ");
        scanf(" %c", &move);

        switch(move)
        {
        case 'w':
        case 'W': ship_x--;break;
        case 'A':
        case 'a': ship_y--;break;
        case 'S':
        case 's': ship_x++;break;
        case 'D':
        case 'd': ship_y++;break;
        default : validLetter=false ; printf("invalid letter\n"); printMap(spaceGame) ;break;
        }

        bool isValid= isValidPos(ship_x,ship_y);
        if (isValid && validLetter)
        {
            //update fuel :
           spaceGame->ship.space_fuel-=fuel_consumption;
            if(spaceGame->ship.space_fuel<=0)
            {
             // system("cls");
              printf("You run out of fuel --GAME OVER \n");
              system("pause");
              return;
            }
            //move space
           spaceGame->ship.playerX=ship_x;
           spaceGame->ship.playerY=ship_y;

           //Move asteroids
            updateAsteroidLocations(spaceGame,spaceGame->numberOfAsteroid);

            //checkCollision
            bool collision = checkCollision(spaceGame);
            if( collision)
            {
              //system("cls");
              printf("Boom Asteroid hit you --GAME OVER \n");
              system("pause");
              return;
            }
            //

           generateMap(spaceGame);
           printHeader(spaceGame);
           printMap(spaceGame);

                       //check score :
            if ( spaceGame->ship.junk_collected == target_junk)
            {
              //system("cls");
              printf("Congratulations you WON  \n");
              system("pause");
              return;
            }


        }

    }
}
bool isValidPos(int x , int y)
{
    if(x<0 || x >= map_raw || y < 0 || y >= map_col )
        return false;
    else
        return true;
}
void updateAsteroidLocations(Game *spaceGame ,int numberOfAsteroids)
{
    if (spaceGame->numberOfAsteroid >= 2)
        {

       spaceGame->asteroid[0].AsteroidX++;
       spaceGame->asteroid[0].AsteroidY++;
       spaceGame->asteroid[1].AsteroidX++;
       spaceGame->asteroid[1].AsteroidY--;

        }

    if (spaceGame->numberOfAsteroid >= 4)
        {
       spaceGame->asteroid[2].AsteroidY++;
       spaceGame->asteroid[3].AsteroidX++;

        }

    if (spaceGame->numberOfAsteroid ==6)
        {
       spaceGame->asteroid[4].AsteroidY++;
       spaceGame->asteroid[5].AsteroidY++;
        }

          if(spaceGame->asteroid[0].AsteroidX >= map_raw)
       {
            createAsteroids(spaceGame);
       }
}
bool checkCollision(Game *spaceGame)
{
   for  (int i=0 ; i < spaceGame->numberOfAsteroid ; i++)
   {
       if(spaceGame->ship.playerX== spaceGame->asteroid[i].AsteroidX && spaceGame->ship.playerY== spaceGame->asteroid[i].AsteroidY  )
       {
        return true;
       }
   }
   return false;

}







