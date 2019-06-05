#include "libtech/geometry.h"

#define _USE_MATH_DEFINES
#include <math.h>
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
    if (this->Left() < other->Right() &&
        this->Right() > other->Left() &&
        this->Top() < other->Bottom() &&
        this->Bottom() > other->Top())
    {
        return true;
    }

    return false;
}

FPolygon FRectangle::AsPolygon()
{
    vec2 p1;
    vec2 p2;
    vec2 p3;
    vec2 p4;
    
    p1.x = this->GetPosition().X;
    p1.y = this->GetPosition().Y;
    
    p2.x = this->GetPosition().X + this->Width;
    p2.y = this->GetPosition().Y;
    
    p3.x = this->GetPosition().X + this->Width;
    p3.y = this->GetPosition().Y + this->Height;
    
    p4.x = this->GetPosition().X;
    p4.y = this->GetPosition().Y + this->Height;
    
    FPolygon poly;
    poly.Set(4, &p1, &p2, &p3, &p4);
    
    return poly;
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
    // TODO : Currently taking vec pointers and adding them to the list
    // but they are not managed properly. FIX !!!!!!!!!!!!!!!!!!!!!!!!!
    
    this->Clear();

    this->vertCount = polyCount;
    this->vertices = new vec2*[polyCount];
    this->vertices[0] = new vec2(*one);
    this->vertices[1] = new vec2(*two);
    this->vertices[2] = new vec2(*three);

    va_list vecs;
    va_start(vecs, three);

    int vectexToAdd = polyCount - 3;
    int index = 3;
    while(vectexToAdd > 0)
    {
        vec2* next = va_arg(vecs, vec2*);
        this->vertices[index] = new vec2(*next);
        index++;
        vectexToAdd--;
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

    return result;
}

vec2** FPolygon::GetVertices(int* length)
{
    *length = this->vertCount;

    vec2** vertsCopy = new vec2*[this->vertCount];

    for(int i = 0; i < this->vertCount; i++)
    {
        vertsCopy[i] = new vec2(*this->vertices[i]);
    }

    return this->vertices;
}

vec2** FPolygon::GetEdges(int* length)
{
    *length = this->vertCount;

    vec2** edgesList = new vec2*[*length];

    for(int i = 1; i < this->vertCount; i++)
    {
        vec2* previous = this->vertices[i - 1];
        vec2* current = this->vertices[i];

        vec2* edge = new vec2();
        *edge = Sub_Vectors(current, previous);

        edgesList[i - 1] = edge;
    }

    vec2* previous = this->vertices[this->vertCount - 1];
    vec2* current = this->vertices[0];

    vec2* edge = new vec2();
    *edge = Sub_Vectors(current, previous);

    edgesList[(*length) - 1] = edge;

    return edgesList;
}

bool FPolygon::IsCollision(FPolygon* other)
{
    int myEdgesCount = 0;
    vec2** myEdges = this->GetEdges(&myEdgesCount);

    int otherEdgesCount = 0;
    vec2** otherEdges = other->GetEdges(&otherEdgesCount);

    vec2* selectedEdge = NULL;
    for(int i = 0; i < myEdgesCount + otherEdgesCount; i++)
    {
        if(i < myEdgesCount)
        {
            selectedEdge = myEdges[i];
        }
        else
        {
            selectedEdge = otherEdges[i - myEdgesCount];
        }

        vec2 axis = selectedEdge->Perpendiculate();
        axis = axis.Normalize();

        std::pair<float, float> thisPoly_Projected = this->Project(&axis);
        std::pair<float, float> otherPoly_Projected = other->Project(&axis);

        float intervalDistance = 0;
        if (thisPoly_Projected.first < otherPoly_Projected.first) {
            intervalDistance =  otherPoly_Projected.first - thisPoly_Projected.second;
        } else {
            intervalDistance =  thisPoly_Projected.first - otherPoly_Projected.second;
        }

        if(intervalDistance > 0)
        {
            return false; // No collision is possible
        }
    }

    return true;
}

std::pair<float, float> FPolygon::Project(vec2* axis)
{
    std::pair<float, float> res;

    float initialValue = axis->DotProduct(this->vertices[0]);
    res.first = initialValue;
    res.second = initialValue;

    for(int i = 0; i < this->vertCount; i++)
    {
        float test = this->vertices[i]->DotProduct(axis);

        if(test < res.first)
        {
            res.first = test;
        }
        else if(test > res.second)
        {
            res.second = test;
        }
    }

    return res;
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
