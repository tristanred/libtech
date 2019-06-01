#include "libtech/geometry.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdarg>

#include "libtech/linkedlist.h"

double deg2rad(double deg)
{
    return (deg * M_PI) / 180;
}

double rad2deg(double rad)
{
    return (rad * 180) / M_PI;
}

float FRectangle::Left()
{
    return this->X;
}

float FRectangle::Top()
{
    return this->Y;
}

float FRectangle::Right()
{
    return this->X + this->Width;
}

float FRectangle::Bottom()
{
    return this->Y + this->Height;
}

FPosition FRectangle::GetCenter()
{
    return FPosition(this->X + (this->Width / 2), this->Y + (this->Height / 2));
}

FPosition FRectangle::GetPosition()
{
    return FPosition(this->X, this->Y);
}

void FRectangle::AlignCenterOn(FRectangle* target)
{
    FPosition centerPos = target->GetCenter();
    FPosition myCenter = this->GetCenter();

    float diffX = centerPos.X - myCenter.X;
    float diffY = centerPos.Y - myCenter.Y;

    this->X += diffX;
    this->Y += diffY;
}

void FRectangle::PushInside(FRectangle* bounds)
{
    if (this->Width > bounds->Width || this->Height > bounds->Height)
        return; // Current rect does not fit inside the bounds

    if (this->Left() < bounds->Left())
        this->X = bounds->X;

    if (this->Top() < bounds->Top())
        this->Y = bounds->Y;

    if (this->Right() > bounds->Right())
        this->X = this->X - (this->Right() - bounds->Right());

    if (this->Bottom() > bounds->Bottom())
        this->Y = this->Y - (this->Bottom() - bounds->Bottom());
}

bool FRectangle::PointIsInside(FPosition point)
{
    return point_in_rect(*this, point);
}

bool FRectangle::PointIsInside(vec2 point)
{
    FPosition pos = FPosition(point);

    return point_in_rect(*this, pos);
}

bool FRectangle::Intersect(FRectangle* other)
{
    FPosition top_left = FPosition(other->Left(), other->Top());
    FPosition top_right = FPosition(other->Right(), other->Top());
    FPosition bottom_right = FPosition(other->Right(), other->Bottom());
    FPosition bottom_left = FPosition(other->Left(), other->Bottom());

    if (this->Left() < other->Right() &&
        this->Right() > other->Left() &&
        this->Top() < other->Bottom() &&
        this->Bottom() > other->Top())
    {
        return true;
    }

    return false;
}

FPolygon::FPolygon()
{
    this->vertices = NULL;
    this->vertCount = 0;
}

FPolygon::~FPolygon()
{

}

void FPolygon::Set(int polyCount, vec2* one, vec2* two, vec2* three...)
{
    this->Clear();

    this->vertices = new struct vec2*[polyCount];
    this->vertices[0] = one;
    this->vertices[1] = two;
    this->vertices[2] = three;

    va_list vecs;
    va_start(vecs, three);

    int vectexToAdd = polyCount - 3;
    int index = 3;
    while(vectexToAdd > 0)
    {
        vec2* next = va_arg(vecs, vec2*);
        this->vertices[index] = next;
        index++;
    }

    va_end(vecs);
}

void FPolygon::Clear()
{
    if(vertices != NULL)
    {
        for(int i = 0; i < vertCount; i++)
        {
            delete(vertices[i]);
        }

        delete(vertices);
    }
}

FRectangle FPolygon::GetRectBounds()
{
    FRectangle result;

    for(int i = 0; i < this->vertCount; i++)
    {
        if(this->vertices[i]->x < result.X)
        {
            result.X = this->vertices[i]->x;
        }
        if(this->vertices[i]->y < result.Y)
        {
            result.Y = this->vertices[i]->y;
        }
        if(this->vertices[i]->x > result.X + result.Width)
        {
            result.Width = this->vertices[i]->x;
        }
        if(this->vertices[i]->y > result.Y + result.Height)
        {
            result.Height = this->vertices[i]->y;
        }
    }
}

bool point_in_rect(FRectangle rect, FPosition point)
{
    if(point.X >= rect.Left() &&
       point.Y >= rect.Top() &&
       point.X <= rect.Right() &&
       point.Y <= rect.Bottom())
    {
        return true;
    }
    else
    {
        return false;
    }
}
