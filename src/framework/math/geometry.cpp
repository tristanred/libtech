#include "libtech/geometry.h"

#define _USE_MATH_DEFINES
#include <libtech/filelogger.h>
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

float FRectangle::Left() const
{
    return this->X;
}

float FRectangle::Top() const
{
    return this->Y;
}

float FRectangle::Right() const
{
    return this->X + this->Width;
}

float FRectangle::Bottom() const
{
    return this->Y + this->Height;
}

FPosition FRectangle::GetCenter() const
{
    return FPosition(this->X + (this->Width / 2), this->Y + (this->Height / 2));
}

FPosition FRectangle::GetPosition() const
{
    return FPosition(this->X, this->Y);
}

void FRectangle::AlignCenterOn(const FRectangle* target)
{
    FPosition centerPos = target->GetCenter();
    FPosition myCenter = this->GetCenter();

    float diffX = centerPos.X - myCenter.X;
    float diffY = centerPos.Y - myCenter.Y;

    this->X += diffX;
    this->Y += diffY;
}

void FRectangle::PushInside(const FRectangle* bounds)
{
    if(this->Width > bounds->Width || this->Height > bounds->Height)
        return;  // Current rect does not fit inside the bounds

    if(this->Left() < bounds->Left())
        this->X = bounds->X;

    if(this->Top() < bounds->Top())
        this->Y = bounds->Y;

    if(this->Right() > bounds->Right())
        this->X = this->X - (this->Right() - bounds->Right());

    if(this->Bottom() > bounds->Bottom())
        this->Y = this->Y - (this->Bottom() - bounds->Bottom());
}

bool FRectangle::PointIsInside(FPosition point) const
{
    return point_in_rect(*this, point);
}

bool FRectangle::PointIsInside(vec2 point) const
{
    FPosition pos = FPosition(point);

    return point_in_rect(*this, pos);
}

bool FRectangle::Intersect(const FRectangle* other) const
{
    if(this->Left() < other->Right() && this->Right() > other->Left() &&
       this->Top() < other->Bottom() && this->Bottom() > other->Top())
    {
        return true;
    }

    return false;
}

FSize FRectangle::GetSize() const
{
    return FSize(this->Width, this->Height);
}

FPolygon FRectangle::AsPolygon() const
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

    this->Offset = vec2(0, 0);
}

FPolygon::FPolygon(const FPolygon& copy)
{
    this->vertCount = copy.vertCount;
    this->vertices = new vec2*[this->vertCount];
    this->Offset = copy.Offset;

    for(int i = 0; i < this->vertCount; i++)
    {
        this->vertices[i] = new vec2();
        *this->vertices[i] = *copy.vertices[i];
    }
}

FPolygon::~FPolygon()
{
    for(int i = 0; i < this->vertCount; i++)
    {
        delete(this->vertices[i]);
    }
    delete(this->vertices);
}

void FPolygon::Set(int vertexCount, vec2* one, vec2* two, vec2* three...)
{
    if(vertexCount < 3)
    {
        LogWarning("Trying to create a polygon with less than 3 vertex.");

        return;
    }

    // TODO : Currently taking vec pointers and adding them to the list
    // but they are not managed properly. FIX !!!!!!!!!!!!!!!!!!!!!!!!!

    this->Clear();

    this->vertCount = vertexCount;
    this->vertices = new vec2*[vertexCount];
    this->vertices[0] = new vec2(*one);
    this->vertices[1] = new vec2(*two);
    this->vertices[2] = new vec2(*three);

    va_list vecs;
    va_start(vecs, three);

    int vectexToAdd = vertexCount - 3;
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

FRectangle FPolygon::GetRectBounds() const
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

    result.X += this->Offset.x;
    result.Y += this->Offset.y;
    return result;
}

FPolygon FPolygon::ZeroOffset() const
{
    FPolygon result = FPolygon(*this);

    float xMin = result.vertices[0]->x;
    float yMin = result.vertices[0]->y;

    for(int i = 1; i < result.vertCount; i++)
    {
        if(result.vertices[i]->x < xMin)
        {
            xMin = result.vertices[i]->x;
        }
        if(result.vertices[i]->y < yMin)
        {
            yMin = result.vertices[i]->y;
        }
    }

    for(int i = 0; i < result.vertCount; i++)
    {
        result.vertices[i]->x -= xMin;
        result.vertices[i]->y -= yMin;
    }

    return result;
}

vec2** FPolygon::GetVertices(int* length) const
{
    *length = this->vertCount;

    vec2** vertsCopy = new vec2*[this->vertCount];

    for(int i = 0; i < this->vertCount; i++)
    {
        vertsCopy[i] = this->vertices[i] + this->Offset;
    }

    return vertsCopy;
}

vec2** FPolygon::GetEdges(int* length) const
{
    *length = this->vertCount;

    vec2** edgesList = new vec2*[*length];

    for(int i = 1; i < this->vertCount; i++)
    {
        vec2 previous = this->vertices[i - 1]->Add(&this->Offset);
        vec2 current = this->vertices[i]->Add(&this->Offset);

        vec2* edge = new vec2();
        *edge = Sub_Vectors(&current, &previous);

        edgesList[i - 1] = edge;
    }

    vec2 previous = this->vertices[this->vertCount - 1]->Add(&this->Offset);
    vec2 current = this->vertices[0]->Add(&this->Offset);

    vec2* edge = new vec2();
    *edge = Sub_Vectors(&current, &previous);

    edgesList[(*length) - 1] = edge;

    return edgesList;
}

bool FPolygon::IsCollision(const FPolygon* other) const
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
        if(thisPoly_Projected.first < otherPoly_Projected.first)
        {
            intervalDistance =
                otherPoly_Projected.first - thisPoly_Projected.second;
        }
        else
        {
            intervalDistance =
                thisPoly_Projected.first - otherPoly_Projected.second;
        }

        if(intervalDistance > 0)
        {
            return false;  // No collision is possible
        }
    }

    return true;
}

std::pair<float, float> FPolygon::Project(vec2* axis) const
{
    std::pair<float, float> res;

    vec2 v = this->vertices[0]->Add(&this->Offset);
    float initialValue = axis->DotProduct(&v);
    res.first = initialValue;
    res.second = initialValue;

    for(int i = 0; i < this->vertCount; i++)
    {
        float test = this->vertices[i]->Add(&this->Offset).DotProduct(axis);

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
    if(point.X >= rect.Left() && point.Y >= rect.Top() &&
       point.X <= rect.Right() && point.Y <= rect.Bottom())
    {
        return true;
    }
    else
    {
        return false;
    }
}
