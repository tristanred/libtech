#include "libtech/numbertracks.h"

#include <math.h>

float* CreateSinusTrack(int amount, int amplitude)
{
    float* ret = new float[amount];

    for(int i = 0; i < amount; i++)
    {
        ret[i] = (float)(sin(i) * amplitude);
    }

    return ret;
}

float* CreateCosineTrack(int amount, int amplitude)
{
    float* ret = new float[amount];

    for(int i = 0; i < amount; i++)
    {
        ret[i] = (float)(cos(i) * amplitude);
    }

    return ret;
}

float* CreateTangentTrack(int amount)
{
    float* ret = new float[amount];

    for(int i = 0; i < amount; i++)
    {
        ret[i] = (float)tan(i);
    }

    return ret;
}

float* SmoothCurveTrack(float* track, int trackLength, int factor)
{
    float* smoothedCurve = new float[trackLength * factor];

    // For each point, insert factor - 1 points between them. The new points are
    // equivalently spaced between each original points.
    int k = 0;
    for(int i = 0; i < trackLength - 1; i++)
    {
        float nbOne = track[i];
        float nbTwo = track[i + 1];

        float diff = nbTwo - nbOne;
        float increments = diff / factor;

        smoothedCurve[k++] = nbOne;
        for(int j = 1; j < factor; j++)
        {
            smoothedCurve[k++] = nbOne + (increments * j);
        }
    }

    return smoothedCurve;
}
