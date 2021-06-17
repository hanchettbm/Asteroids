/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H
#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"


class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);
    
   
private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   
   int score;
   int shipLives;
   std::vector<Bullet> bullets;
   std::vector<Rock*> rock;
   Ship ship;

    
   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/
   bool isOnScreen(const Point & point);
   void advanceBullets();
   void advanceRock();
   void createRock(int rockType, Point position, int nDX, int nDY);
   void advanceShip();
   void handleCollisions();
   void cleanUpZombies();
   float getClosestDistance(const Flying &obj1, const Flying &obj2) const;
};

#endif /* GAME_H */
