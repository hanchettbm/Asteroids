#ifndef flyingObject_h
#define flyingObject_h

// Put your FlyingObject class here

#include "point.h"
#include "velocity.h"

class Flying
{
protected:
   Point point;
   Velocity velocity;
   bool alive;

public:
    Flying() : point(0,0), velocity(0,0)
    {
        alive = true;
    }
    Point getPoint() const {return point; }
    Velocity getVelocity() const { return velocity; }
    bool isAlive();
    void setPoint(Point point) { this-> point = point; }
    void setVelocity(Velocity velocity) { this-> velocity = velocity; }
    void kill();
    void advance();
    virtual void draw() = 0;
    void wrap();
    
};

#endif /* flyingObject_h */
