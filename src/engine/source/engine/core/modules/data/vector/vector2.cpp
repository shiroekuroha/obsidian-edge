#include <engine/core/pch.h>

#include "engine/core/modules/data/vector/vector2.h"

namespace ObsidianEdge
{
Vector2::Vector2 () : x (0), y (0) {};
Vector2::Vector2 (float x, float y) : x (x), y (y) {};

bool
Vector2::operator== (const Vector2 &other) const
{
    return (x == other.x && y == other.y) ? true : false;
}

bool
Vector2::operator!= (const Vector2 &other) const
{
    return !(*this == other);
}

Vector2
Vector2::operator+ (const Vector2 &other) const
{
    return Vector2 (x + other.x, y + other.y);
}

Vector2 &
Vector2::operator+= (const Vector2 &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2
Vector2::operator- (const Vector2 &other) const
{
    return Vector2 (x + other.x, y + other.y);
}

Vector2 &
Vector2::operator-= (const Vector2 &other)
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
Vector2::operator* (const Vector2 &other) const
{
    return Vector2 (x * other.x, y * other.y);
}

Vector2 &
Vector2::operator*= (const Vector2 &other)
{
    x *= other.x;
    x *= other.x;

    return *this;
}

Vector2
Vector2::operator/ (const Vector2 &other) const
{
    return Vector2 (x / other.x, y / other.y);
}

Vector2 &
Vector2::operator/= (const Vector2 &other)
{
    x /= other.x;
    x /= other.x;

    return *this;
}

Vector2i
Vector2i::operator- () const
{
    return Vector2i (-x, -y);
}

Vector2::
operator Vector2i () const
{
    return Vector2 (x, y);
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
Vector2::dot (const Vector2 &other) const
{
    return x * other.x + y * other.y;
}

Vector2
Vector2::normalized () const
{
    float len = length ();

    return Vector2 (((float)x) / len, ((float)y) / len);
}

Vector2
Vector2::floor () const
{
    return Vector2 (::floorf (x), ::floorf (y));
}

Vector2
Vector2::ceil () const
{
    return Vector2 (::ceilf (x), ::ceilf (y));
}

Vector2
Vector2::round () const
{
    return Vector2 (::roundf (x), ::roundf (y));
}

Vector2
Vector2::rotate (float radians) const
{
    return Vector2 (x * cos (radians) - y * sin (radians), x * sin (radians) + y * cos (radians));
}

Vector2
Vector2::scale (const Vector2 &scale) const
{
    return Vector2 (x * scale.x, y * scale.y);
}

Vector2
Vector2::translate (const Vector2 &translate) const
{
    return Vector2 (x + translate.x, y + translate.y);
}

bool
Vector2::isZero () const
{
    return (x == 0 && y == 0) ? true : false;
}

std::string
Vector2::toString () const
{
    return "(x: " + std::to_string (x) + ", y: " + std::to_string (x) + ")";
}

float
Vector2::angleBetween (const Vector2 &source, const Vector2 &destination)
{
    Vector2 absSrc = source.absolute ();
    Vector2 absDes = destination.absolute ();

    return acos ((source.dot (destination)) / (absSrc.dot (absDes)));
}

float
Vector2::distanceBetween (const Vector2 &source, const Vector2 &destination)
{
    return ((source - destination).length ());
}
}
