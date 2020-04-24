#include "libtech/functions.h"

#include <assert.h>
#include <math.h>

#include <string>

#include "libtech/tgafile.h"

int avg(int one, int two)
{
    return (one + two) / 2;
}

float favg(float one, float two)
{
    return (one + two) / 2;
}

TgaFile* PlotSequenceToImage(float* curve, int curveLength)
{
    assert(curveLength >= 0);

    int highestPoint = 0;
    int lowestPoint = 0;
    int imageHeight;

    // Find the highest and lowest point on the curve, round the number up to
    // make sure we have +1 pixel
    for(int i = 0; i < curveLength; i++)
    {
        int pt = (int)ceil(curve[i] * -1);

        if(pt > highestPoint)
            highestPoint = pt;

        if(pt < lowestPoint)
            lowestPoint = pt;
    }

    imageHeight = abs(highestPoint) + abs(lowestPoint);

    assert(imageHeight > 0);  // Curve is probably malformed

    TgaFile* image = new TgaFile();
    image->Init(curveLength, imageHeight);

    for(int i = 0; i < curveLength; i++)
    {
        int pt = (int)curve[i] * -1;
        // int baseLine = i + (curveLength * imageHeight / 2);

        TgaPix* px = image->Get(i, (imageHeight / 2) + pt);
        px->a = 255;
        px->r = 255;
        px->g = 0;
        px->b = 255;
    }

    return image;
}
