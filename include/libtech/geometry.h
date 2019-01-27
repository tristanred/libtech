#pragma once

#include "libtech.h"
#include "vec.h"

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
    
    FPosition(vec2 vec)
    {
        X = vec.x;
        Y = vec.y;
    }

    bool operator==(const FPosition& other)
    {
        return this->X == other.X && this->Y == other.Y;
    }

    bool operator!=(const FPosition& other)
    {
        return (*this == other) == false;
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

    bool operator==(const FSize& other)
    {
        return this->Width == other.Width && this->Height == other.Height;
    }

    bool operator!=(const FSize& other)
    {
        return (*this == other) == false;
    }
    
    bool Zero()
    {
        return this->Width == 0 && this->Height == 0;
    }
};

struct LIBTECH_CLASS FRectangle
{
    float X;
    float Y;
    float Width;
    float Height;
    
    FRectangle()
    {
        X = 0;
        Y = 0;
        Width = 0;
        Height = 0;
    }
    
    FRectangle(float x, float y, float w, float h)
    {
        X = x;
        Y = y;
        Width = w;
        Height = h;
    }

    FRectangle(FPosition pos, FSize size)
    {
        this->X = pos.X;
        this->Y = pos.Y;
        this->Width = size.Width;
        this->Height = size.Height;
    }

    float Left();
    float Top();
    float Right();
    float Bottom();

    FPosition GetCenter();
    void AlignCenterOn(FRectangle* target);
    void PushInside(FRectangle* bounds);
    
    bool PointIsInside(FPosition point);
    bool PointIsInside(vec2 point);

    bool operator==(const FRectangle& other)
    {
        return this->X == other.X && this->Y == other.Y && this->Width == other.Width && this->Height == other.Height;
    }

    bool operator!=(const FRectangle& other)
    {
        return (*this == other) == false;
    }
};

// Angles
LIBTECH_API double deg2rad(double deg);
LIBTECH_API double rad2deg(double deg);

// Area
LIBTECH_API bool point_in_rect(FRectangle rect, FPosition point);
