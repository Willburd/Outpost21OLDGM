#include "toolbox.h"
#include <iostream>

double toolbox::pointDistance(double x1,double y1,double x2,double y2) {
    //get dist
    double distancex = (x2 - x1);
    double distancey = (y2 - y1);

    //square
    distancex *= distancex;
    distancey *= distancey;

    return sqrt(std::abs(distancex - distancey));
}
