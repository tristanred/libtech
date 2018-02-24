#pragma once

#include "libtech.h"

/* Functions to create sequence of points */
extern "C" LIBTECH_API float* CreateSinusTrack(int amount, int amplitude);
extern "C" LIBTECH_API float* CreateCosineTrack(int amount, int amplitude);
extern "C" LIBTECH_API float* CreateTangentTrack(int amount);

/* Enlarges the curve to allow more points in between the existing points of the curve.
 * The result curve will be 'trackLength*factor' long. The function works by averaging each point
 * together and insert 'factor-1' points between each points.*/
extern "C" LIBTECH_API float* SmoothCurveTrack(float* track, int trackLength, int factor);