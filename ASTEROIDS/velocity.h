#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
#include "point.h"

class Velocity
{
private:
   float dx;
   float dy;
   
public:
   Velocity()
   {
      dx = 0.0;
      dy = 0.0;
   }
   
   Velocity(float dx, float dy)
   {
      this->dx = dx;
      this->dy = dy;
   }
   
   float getDx() const { return dx; }
   float getDy() const { return dy; }
   
   void setDx(float dx) { this->dx = dx; }
   void setDy(float dy) { this->dy = dy; }
   
   void add(const Velocity & other);

   void advancePoint(Point & point);
   
};

#endif /* velocity_h */
