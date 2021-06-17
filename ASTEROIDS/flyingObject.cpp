#include "flyingObject.h"


// Put your FlyingObject method bodies here
//Checks which objects are alive.
bool Flying::isAlive()
{
    return alive;
}

//Kills objects.
void Flying::kill()
{
    alive = false;
}

//Moves flying objects with velocity. 
void Flying::advance()
{
    point.addX(velocity.getDx());
    point.addY(velocity.getDy());
}
// Wraps all objects.
void Flying::wrap()
{
   if (point.getX() > 200)
   {
       point.setX(-200);
   }
   if (point.getX()< -200)
   {
       point.setX(200);
   }
   if (point.getY() > 200)
   {
       point.setY(-200);
   }
   if (point.getY() < -200)
   {
       point.setY(200);
   }
}
