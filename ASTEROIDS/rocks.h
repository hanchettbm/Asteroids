#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "uiDraw.h"

// Define the following classes here:
//   Rock
class Rock  : public Flying
{
protected:
    int angle;
    int numHits;
    int radius;
    
public:
   Rock() : Flying()
    {
        angle = random(0,360);
        radius = 0;
        numHits = 1;
    }
    Rock(Point p, int newRadius, int hits) :Flying()
    {
        point = p;
        radius = newRadius;
        numHits = hits;
        
    };
    virtual int hit() = 0;
    int getRadius() { return radius;}
    void setRadius(int radius) {this->radius = radius; }
};
//   BigRock
class BigRock  : public Rock
{
private:
    
public:
    BigRock() : Rock()
    {
        radius =  16;
    }
    virtual void draw()
    { drawLargeAsteroid(point, angle);
      angle = angle + 2;
    }
     virtual int hit();
};

//   MediumRock
class MediumRock  : public Rock
{
private:
    
    
public:
    MediumRock() : Rock()
    {
       radius =  8;
    }
    virtual void draw()
    {
        drawMediumAsteroid(point, angle);
        angle = angle + 5;
        
    }
     virtual int hit();
};

//   SmallRock
class SmallRock  : public Rock
{
private:
    
    
public:
    SmallRock() : Rock()
    {
        radius =  4;
    }
    virtual void draw()
    {
        drawSmallAsteroid(point, angle);
        angle = angle + 10;
    }
     virtual int hit();
};

#endif /* rocks_h */
