#ifndef ship_h
#define ship_h
#include "flyingObject.h"
#include "uiDraw.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5



// Put your Ship class here
class Ship : public Flying
{
private:
    bool thrust;
    float angle;
    int numHits;
    
public:
    Ship() : Flying()
    {

        thrust = false;
        angle = 0;
        numHits = -1;
    }
    //bool isAlive() { return alive; }
    int getThrust() { return thrust; }
    void setThrust(bool thrust) { this->thrust = thrust; }
    void applyGravity(float gravity);
    void applyThrustLeft();
    void applyThrustRight();
    void applyThrustBottom();
    void applyThrustTop();
    int hit();
    float getAngle() const { return angle; }
    Point getPoint() const { return point; }
    void advance();
    void draw();
    };

#endif /* ship_h */
