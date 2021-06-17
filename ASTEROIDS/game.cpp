/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include "uiDraw.h"
#include <algorithm>
#include "uiInteract.h"
#include "point.h"
#include "ship.h"

#include <vector>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5

// Game Constructor used to make the first big rock and set the values
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   // Set up the initial conditions of the game
    score = 0;
    shipLives = 10;
    for(int i = 0; i < 5; i++)
    {
        createRock(1, Point(), Velocity().getDx(),Velocity().getDy());
    }
        
}

//Advance method used to call all the moving parts and clean up hit pieces.
void Game :: advance()
{
   advanceBullets();
   advanceRock();
   handleCollisions();
   advanceShip();
   cleanUpZombies();
}

//Method in charge of moving the bullets at the angle they were fired.
void Game :: advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();
         bullets[i].setBulletLife(bullets[i].getBulletLife() -1);
          
         if (bullets[i].getBulletLife() <= 0)
         {
             bullets[i].kill();
         }
         
         if (!isOnScreen(bullets[i].getPoint()))
         {
            // the bullet has left the screen
            bullets[i].wrap();
             
         }
         
      }
   }
}

//Moves the ship forward and wraps it.
void Game ::advanceShip()
{
    ship.advance();
    
    if (!isOnScreen(ship.getPoint()))
    {
       ship.wrap();
    }
}

//Moves Rock forward and wraps it.
void Game :: advanceRock()
{
    // we have a rock, make sure it's alive
    for (int i = 0; i < rock.size(); i++)
    {
        if (rock[i]->isAlive())
        {
            // move it forward
            rock[i]->advance();
            // check if the rock has gone off the screen then wrap.
            if (!isOnScreen(rock[i]->getPoint()))
            {
               rock[i]->wrap();
            }
        }
    }
}

//Creates the different rocks needed from the vector.
void Game :: createRock(int rockType, Point position, int nDX, int nDY)
{
    //Makes new reock from vector and checks it's type.
    Rock* newRock = NULL;
    if (rockType == 1)
    {
        //Create big rock and randomize velocity and point.
        newRock = new BigRock();
        int yNumber = random(-100, 101);
        int xNumber = random(-100, 101);
        if (yNumber != 0 || xNumber != 0)
        {
        newRock->setPoint(Point(yNumber,xNumber));
        }
        int yVelocity = 0;
        int xVelocity = 0;
        
        while ((yVelocity ==0) && (xVelocity ==0))
        {
            yVelocity = random(-1,2);
            xVelocity = random(-1,2);
         }
         newRock->setVelocity(Velocity(xVelocity,yVelocity));
         rock.push_back(newRock);
    }
    //Create Medium Rock using info from killed big rock.
    if (rockType == 2)
    {
        newRock = new MediumRock();
        newRock->setPoint(position);
        newRock->setVelocity(Velocity(nDX,nDY));
        rock.push_back(newRock);
    }
    //Create Small Rock using info from killed medium rock.
    if (rockType == 3)
    {
        newRock = new SmallRock();
        newRock->setPoint(position);
        newRock->setVelocity(Velocity(nDX,nDY));
        rock.push_back(newRock);
    }
    
   }

//Sets the boarders of the game window.
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
    for (int p = 0; p < rock.size(); p++)
    {
        if (rock[p] != NULL && rock[p]->isAlive())
        {
            if (ship.isAlive())
            {
               //Check for Ship Colision of Rock.
               if (getClosestDistance(*rock[p], ship) < rock[p]->getRadius() || getClosestDistance(*rock[p], ship) < 10)
               {
                   int points = ship.hit();
                   if (points <= 0)
                   {
                       points = 0;
                       ship.setPoint(Point());
                       shipLives = shipLives -1;
                   }
                   if (shipLives  <= 0)
                   {
                       shipLives = 0;
                       ship.kill();
                   }
               }
            }
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].isAlive())
        {
            //Check impact of Big Rocks.
            int rockRadius = 16;
            if (getClosestDistance(bullets[i], *rock[p]) < rockRadius)
            {
                //we have a bigRockhit!
                if (rock[p]->getRadius() == 16)
                {
                    createRock(2, rock[p]->getPoint(), rock[p]->getVelocity().getDx(), rock[p]->getVelocity().getDy()+1);
                    createRock(2, rock[p]->getPoint(), rock[p]->getVelocity().getDx(), rock[p]->getVelocity().getDy()-1);
                    createRock(3, rock[p]->getPoint(), rock[p]->getVelocity().getDx()+2, rock[p]->getVelocity().getDy());

                    bullets[i].kill();
                    int points = rock[p]->hit();
                    score += points;
                }
            }
            
            //Check impact of Medium Rocks.
            rockRadius = 8;
            if (getClosestDistance(bullets[i], *rock[p]) < rockRadius)
            {
                if (rock[p]->getRadius() == 8)
                {
                    createRock(3, rock[p]->getPoint(), rock[p]->getVelocity().getDx()+3, rock[p]->getVelocity().getDy());
                    createRock(3, rock[p]->getPoint(), rock[p]->getVelocity().getDx()-3, rock[p]->getVelocity().getDy());
                        bullets[i].kill();
                    int points = rock[p]->hit();
                    score += points;
                }
            }
            
            //Check impact of Small Rocks.
            rockRadius = 4;
            if (getClosestDistance(bullets[i], *rock[p]) < rockRadius)
            {
                if (rock[p]->getRadius() == 4)
                {
                    bullets[i].kill();
                    int points = rock[p]->hit();
                    score += points;
                }
            }
        }
        }
        }
    }
}

//Clears memory of the bullet and rock vecors.
void Game :: cleanUpZombies()
{
    vector<Rock*>::iterator rockIt = rock.begin();
    while (rockIt != rock.end())
    {
        Rock* pRock = *rockIt;
           
        if (!pRock->isAlive())
        {
           // remove from list and advance
           rockIt = rock.erase(rockIt);
        }
        
        else
        {
            rockIt++; // advance
        }
    }

    vector<Bullet>::iterator bulletIt = bullets.begin();
    while (bulletIt != bullets.end())
    {
       Bullet bullet = *bulletIt;
       
       if (!bullet.isAlive())
       {
          // remove from list and advance
          bulletIt = bullets.erase(bulletIt);
       }
        
       else
       {
          bulletIt++; // advance
       }
    }
}

//Handles the input from the keys from the user and applies thrust.
void Game :: handleInput(const Interface & ui)
{
 
   if (ui.isDown())
   {
       ship.applyThrustBottom();
       ship.setThrust(true);
   }
   else
   {
        ship.setThrust(false);
   }
   if (ui.isLeft())
   {
       ship.applyThrustLeft();
   }
   
   if (ui.isRight())
   {
       ship.applyThrustRight();
   }
   
   if (ui.isUp())
    {
       ship.applyThrustTop();
    }
    
   // Check for "Spacebar
   if (ship.isAlive())
   {
      if (ui.isSpace())
      {
         Bullet newBullet;
         newBullet.fire(ship.getPoint(), 90-ship.getAngle());
         bullets.push_back(newBullet);
      }
   }
}

//Draws the objects.
void Game :: draw(const Interface & ui)
{
    //Draw Ship if Alive.
    if (ship.isAlive())
    {
       ship.draw();
    }
    
    //Draw Rocks if Alive.
    for (int i = 0; i < rock.size(); i++)
    {
        if (rock[i]->isAlive())
        {
            rock[i]->draw();
        }
    }

   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         bullets[i].draw();
         
      }
   }
    
    // Put the score on the screen
      Point scoreText;
      scoreText.setX(topLeft.getX() + 4);
      scoreText.setY(topLeft.getY() - 12);
      drawText(scoreText, "Asteroid Kill Count:");
    
      Point shipText;
      shipText.setX(topLeft.getX() + 4);
      shipText.setY(topLeft.getY() - 50);
      drawText(shipText, "Ship Lives:");
    
      Point scoreLocation;
      scoreLocation.setX(topLeft.getX() + 5);
      scoreLocation.setY(topLeft.getY() - 20);
      drawNumber(scoreLocation, score);
    
      Point shipLifeCount;
      shipLifeCount.setX(topLeft.getX() + 5);
      shipLifeCount.setY(topLeft.getY() - 60);
      drawNumber(shipLifeCount, shipLives);
    
      if (shipLives == 0)
      {
          drawText(Point(), "Ship Dead: Game Over :(");
      }
    
      if (score == 60)
      {
          drawText(Point(), "You Won!");
          ship.kill();
      }
}


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const Flying &obj1, const Flying &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}
