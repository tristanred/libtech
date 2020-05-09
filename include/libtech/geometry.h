#pragma once

#include <utility>

#include "libtech.h"
#include "vec.h"

class FPolygon;

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

    vec2 AsVec() { return vec2(this->X, this->Y); }

    bool operator==(const FPosition& other)
    {
        return this->X == other.X && this->Y == other.Y;
    }

    bool operator!=(const FPosition& other)
    {
        return (*this == other) == false;
    }

    FPosition operator+(const FPosition& other)
    {
        return FPosition(this->X + other.X, this->Y + other.Y);
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

    vec2 AsVec() { return vec2(this->Width, this->Height); }

    bool operator==(const FSize& other)
    {
        return this->Width == other.Width && this->Height == other.Height;
    }

    bool operator!=(const FSize& other) { return (*this == other) == false; }

    bool Zero() { return this->Width == 0 && this->Height == 0; }
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

    float Left() const;
    float Top() const;
    float Right() const;
    float Bottom() const;

    FPosition GetCenter() const;
    FPosition GetPosition() const;  // Get position of the origin
    FSize GetSize() const;

    void AlignCenterOn(const FRectangle* target);
    void PushInside(const FRectangle* bounds);

    bool PointIsInside(const FPosition point) const;
    bool PointIsInside(const vec2 point) const;

    bool Intersect(const FRectangle* other) const;

    FPolygon AsPolygon() const;

    bool operator==(const FRectangle& other)
    {
        return this->X == other.X && this->Y == other.Y &&
               this->Width == other.Width && this->Height == other.Height;
    }

    bool operator!=(const FRectangle& other)
    {
        return (*this == other) == false;
    }
};

class LIBTECH_CLASS FPolygon
{
public:
    FPolygon();
    FPolygon(const FPolygon& copy);
    ~FPolygon();

    vec2 Offset;

    void Set(int vertexCount, vec2* one, vec2* two, vec2* three...);

    void Clear();

    vec2** GetVertices(int* length) const;
    vec2** GetEdges(int* length) const;

    /**
     * \brief Get the bounds of the polygon in a rectangular bounding box
     * \return Rectangular box containing this polygon.
     */
    FRectangle GetRectBounds() const;

    /**
     * Return a copy of this polygon aligned to the coordinates (0, 0)
     */
    FPolygon ZeroOffset() const;

    bool IsCollision(const FPolygon* other) const;

    std::pair<float, float> Project(vec2* axis) const;

private:
    int vertCount;
    vec2** vertices;
};

// Angles
LIBTECH_API double deg2rad(double deg);
LIBTECH_API double rad2deg(double deg);

// Area
LIBTECH_API bool point_in_rect(FRectangle rect, FPosition point);
