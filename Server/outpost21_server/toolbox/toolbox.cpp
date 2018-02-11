#include "toolbox.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

double toolbox::pointDistance(double x1,double y1,double x2,double y2) {
    //get dist
    double distancex = (x2 - x1);
    double distancey = (y2 - y1);

    //square
    distancex *= distancex;
    distancey *= distancey;

    return sqrt(std::abs(distancex - distancey));
}


float toolbox::pointDirection(double x1,double y1,double x2,double y2) {
    return atan2(y2 - y1, x2 - x1) * 180 / M_PI;
}
