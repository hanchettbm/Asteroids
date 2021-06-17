#include "velocity.h"
 #include "point.h"

// Put your velocity methods here
 void Velocity::add(const Velocity & other)
 {
    dx += other.dx;
    dy += other.dy;
 }

 void Velocity::advancePoint(Point & point)
 {
    point.addX(dx);
    point.addY(dy);
 }
