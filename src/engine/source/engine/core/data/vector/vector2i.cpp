#include "engine/core/data/vector/vector2i.h"

namespace ObsidianEdge
{
Vector2i::Vector2i () : x (0), y (0) {};
Vector2i::Vector2i (int x, int y) : x (x), y (y) {};

Vector2i
Vector2i::operator+ (Vector2i &other) const
{
    return Vector2i (x + other.x, y + other.y);
}

Vector2i &
Vector2i::operator+= (Vector2i &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2i
Vector2i::operator- (Vector2i &other) const
{
    return Vector2i (x + other.x, y + other.y);
}

Vector2i &
Vector2i::operator-= (Vector2i &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2i
Vector2i::operator* (float mul) const
{
    return Vector2i (x * mul, y * mul);
}

Vector2i &
Vector2i::operator*= (float mul)
{
    x *= mul;
    y *= mul;

    return *this;
}

Vector2i
Vector2i::operator/ (float mul) const
{
    return Vector2i (x / mul, y / mul);
}

Vector2i &
Vector2i::operator/= (float mul)
{
    x /= mul;
    y /= mul;

    return *this;
}

Vector2i
Vector2i::absolute () const
{
    return Vector2i (abs (x), abs (y));
}

int
Vector2i::length () const
{
    return sqrt (x * x + y * y);
}

int
Vector2i::dot (Vector2i &other) const
{
    return x * other.x + y * other.y;
}

int
Vector2i::angleBetween (Vector2i &source, Vector2i &destination)
{
    Vector2i absSrc = source.absolute ();
    Vector2i absDes = source.absolute ();

    return acos ((source.dot (destination)) / (absSrc.dot (absDes)));
}

int
Vector2i::distanceBetween (Vector2i &source, Vector2i &destination)
{
    return ((source - destination).length ());
}
}