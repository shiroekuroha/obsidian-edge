#include <engine/core/pch.h>

#include "engine/core/data/vector/vector2i.h"

namespace ObsidianEdge
{
Vector2i::Vector2i () : x (0), y (0) {};
Vector2i::Vector2i (int x, int y) : x (x), y (y) {};

bool
Vector2i::operator== (const Vector2i &other) const
{
    return (x == other.x && y == other.y) ? true : false;
}

bool
Vector2i::operator!= (const Vector2i &other) const
{
    return !(*this == other);
}

Vector2i
Vector2i::operator+ (const Vector2i &other) const
{
    return Vector2i (x + other.x, y + other.y);
}

Vector2i &
Vector2i::operator+= (const Vector2i &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2i
Vector2i::operator- (const Vector2i &other) const
{
    return Vector2i (x + other.x, y + other.y);
}

Vector2i &
Vector2i::operator-= (const Vector2i &other)
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
Vector2i::operator* (const Vector2i &other) const
{
    return Vector2i (x * other.x, y * other.y);
}

Vector2i &
Vector2i::operator*= (const Vector2i &other)
{
    x *= other.x;
    x *= other.x;

    return *this;
}

Vector2i
Vector2i::operator/ (const Vector2i &other) const
{
    return Vector2i (x / other.x, y / other.y);
}

Vector2i &
Vector2i::operator/= (const Vector2i &other)
{
    x /= other.x;
    x /= other.x;

    return *this;
}

Vector2
Vector2::operator- () const
{
    return Vector2 (-x, -y);
}

Vector2i::
operator Vector2 () const
{
    return Vector2i ((int)x, (int)y);
}

Vector2i
Vector2i::absolute () const
{
    return Vector2i (abs (x), abs (y));
}

float
Vector2i::length () const
{
    return sqrt (x * x + y * y);
}

float
Vector2i::dot (const Vector2 &other) const
{
    return x * other.x + y * other.y;
}

Vector2
Vector2i::normalized () const
{
    float len = length ();

    return Vector2 (((float)x) / len, ((float)y) / len);
}

bool
Vector2i::isZero () const
{
    return (x | y) ? false : true;
}

std::string
Vector2i::toString () const
{
    return "(x: " + std::to_string (x) + ", y: " + std::to_string (x) + ")";
}
}
