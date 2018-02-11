#ifndef TOOLBOX_H
#define TOOLBOX_H
//=================================
// forward declared dependencies

//=================================
// included dependencies
#include <cmath>
#include <algorithm>

namespace toolbox {

    template<class T>
    constexpr const T& clamp( const T& v, const T& lo, const T& hi )
    {
        return std::min(std::max(v, lo), hi);
    }

    double pointDistance(double x1,double y1,double x2,double y2);
    float pointDirection(double x1,double y1,double x2,double y2);
}

#endif
