#include "bullet.h"


// Put your bullet methods here
#include <cmath>

//Fires the Bullet.
void Bullet::fire(Point point, float angle)
{
    float dx = BULLET_SPEED * (-cos(M_PI / 180.0 * angle));
    float dy = BULLET_SPEED * (sin(M_PI / 180.0 * angle));
    
    this->point = point;
    
    this->velocity.setDx(dx);
    this->velocity.setDy(dy);
}


