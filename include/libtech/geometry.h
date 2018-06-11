#pragma once

#include "libtech.h"

LIBTECH_API double deg2rad(double deg);

LIBTECH_API double rad2deg(double deg);

struct LIBTECH_CLASS FPosition
{
    float X;
    float Y;

    FPosition()
    {
        X = 0;
        Y = 0;
    }

    FPosition(float x, float y)
    {
        X = x;
        Y = y;
    }
};

struct LIBTECH_CLASS FSize
{
    float Width;
    float Height;

    FSize()
    {
        Width = 0;
        Height = 0;
    }

    FSize(float w, float h)
    {
        Width = w;
        Height = h;
    }
};