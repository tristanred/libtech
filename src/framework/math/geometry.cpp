#include "libtech/geometry.h"

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
