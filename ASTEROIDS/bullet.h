#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40



// Put your Bullet class here
#include "flyingObject.h"
#include "uiDraw.h"

class Bullet : public Flying
{
private:
    float angle;
    float dx;
    float dy;
    int bullettLife;
    
public:
    Bullet() : Flying()
    {
        angle = 0;
        dx = 0;
        dy = 0;
        bullettLife = BULLET_LIFE;
    };

    void fire(Point point, float angle);
    virtual void draw() { drawDot(point); }
    int getBulletLife() { return bullettLife; }
    void setBulletLife(int life) {bullettLife = life; }
};

#endif /* bullet_h */
