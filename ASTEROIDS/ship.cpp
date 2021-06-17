#include "ship.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"
// Put your ship methods here
// Moves Ship Left.
void Ship::applyThrustLeft()
{

    angle -= ROTATE_AMOUNT;
}

// Moves Ship Right.
void Ship::applyThrustRight()
{
    angle += ROTATE_AMOUNT;
}

// Moves Ship up.
void Ship::applyThrustBottom()
{
    float dx = velocity.getDx() + THRUST_AMOUNT * (cos(M_PI / 180.0 * (angle + 90)));
    float dy = velocity.getDy() + THRUST_AMOUNT * (sin(M_PI / 180.0 * (angle + 90)));

    this->point = point;
    this->velocity.setDx(dx);
    this->velocity.setDy(dy);
}

// Moves Ship Down.
void Ship::applyThrustTop()
{
       float dx = velocity.getDx() + THRUST_AMOUNT * (-cos(M_PI / 180.0 * (angle + 90)));
       float dy = velocity.getDy() + THRUST_AMOUNT * (-sin(M_PI / 180.0 * (angle + 90)));
           
           this->point = point;
           
           this->velocity.setDx(dx);
           this->velocity.setDy(dy);
}

int Ship::hit()
{
    return numHits;
}

//Moves Ship with Velocity.
void Ship::advance()
{
    point.addX(velocity.getDx());
    point.addY(velocity.getDy());
}

//Calls DrawShip from UI draw to put ship on screen. 
void Ship::draw()
{
    drawShip(point, angle, thrust);
}

