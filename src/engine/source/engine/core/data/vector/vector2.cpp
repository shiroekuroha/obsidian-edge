#include "engine/core/data/vector/vector2.h"

namespace ObsidianEdge
{
Vector2::Vector2 () : x (0), y (0) {};
Vector2::Vector2 (float x, float y) : x (x), y (y) {};

Vector2
Vector2::operator+ (Vector2 &other) const
{
    return Vector2 (x + other.x, y + other.y);
}

Vector2 &
Vector2::operator+= (Vector2 &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2
Vector2::operator- (Vector2 &other) const
{
    return Vector2 (x + other.x, y + other.y);
}

Vector2 &
Vector2::operator-= (Vector2 &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2
Vector2::operator* (float mul) const
{
    return Vector2 (x * mul, y * mul);
}

Vector2 &
Vector2::operator*= (float mul)
{
    x *= mul;
    y *= mul;

    return *this;
}

Vector2
Vector2::operator/ (float mul) const
{
    return Vector2 (x / mul, y / mul);
}

Vector2 &
Vector2::operator/= (float mul)
{
    x /= mul;
    y /= mul;

    return *this;
}

Vector2
Vector2::absolute () const
{
    return Vector2 (abs (x), abs (y));
}

float
Vector2::length () const
{
    return sqrt (x * x + y * y);
}

float
Vector2::dot (Vector2 &other) const
{
    return x * other.x + y * other.y;
}

float
Vector2::angleBetween (Vector2 &source, Vector2 &destination)
{
    Vector2 absSrc = source.absolute ();
    Vector2 absDes = source.absolute ();

    return acos ((source.dot (destination)) / (absSrc.dot (absDes)));
}

float
Vector2::distanceBetween (Vector2 &source, Vector2 &destination)
{
    return ((source - destination).length ());
}
}