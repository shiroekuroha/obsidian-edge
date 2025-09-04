#pragma once

struct Vector2i;

#include "engine/core/data/vector/vector2.h"

namespace ObsidianEdge
{
struct Vector2i
{
    Vector2i ();
    Vector2i (int x, int y);

    ~Vector2i () = default;

    bool operator== (const Vector2i &other) const;
    bool operator!= (const Vector2i &other) const;

    Vector2i operator+ (const Vector2i &other) const;
    Vector2i &operator+= (const Vector2i &other);

    Vector2i operator- (const Vector2i &other) const;
    Vector2i &operator-= (const Vector2i &other);

    Vector2i operator* (float mul) const;
    Vector2i &operator*= (float mul);

    Vector2i operator/ (float mul) const;
    Vector2i &operator/= (float mul);

    Vector2i operator* (const Vector2i &other) const;
    Vector2i &operator*= (const Vector2i &other);

    Vector2i operator/ (const Vector2i &other) const;
    Vector2i &operator/= (const Vector2i &other);

    Vector2i operator- () const;

    operator Vector2 () const;
    Vector2i absolute () const;

    float length () const;
    float dot (const Vector2 &other) const;
    float cross (const Vector2 &other) const;
    Vector2 normalized () const;

    bool isZero () const;

    int x = 0, y = 0;
    std::string toString () const;
};
}
