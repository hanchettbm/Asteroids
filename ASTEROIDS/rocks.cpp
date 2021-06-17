#include "rocks.h"
#include "uiDraw.h"

// Put your Rock methods here
//Detects a hit and kills Rocks. 
int BigRock::hit()
{
    numHits = 3;
     kill();
    return numHits;
}

int MediumRock::hit()
{
    numHits = 2;
     kill();
    return numHits;
}

int SmallRock::hit()
{
    numHits = 1;
     kill();
    return numHits;
}
