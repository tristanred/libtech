#include "libtech/Geometry.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "libtech/linkedlist.h"

double deg2rad(double deg)
{
    return (deg * M_PI) / 180;
}

double rad2deg(double rad)
{
    return (rad * 180) / M_PI;
}