#pragma once

struct Vector2;

#include "engine/core/modules/data/vector/vector2i.h"

namespace ObsidianEdge
{
struct Vector2
{
    Vector2 ();
    Vector2 (float x, float y);

    ~Vector2 () = default;

    bool operator== (const Vector2 &other) const;
    bool operator!= (const Vector2 &other) const;

    Vector2 operator+ (const Vector2 &other) const;
    Vector2 &operator+= (const Vector2 &other);

    Vector2 operator- (const Vector2 &other) const;
    Vector2 &operator-= (const Vector2 &other);

    Vector2 operator* (float mul) const;
    Vector2 &operator*= (float mul);

    Vector2 operator/ (float mul) const;
    Vector2 &operator/= (float mul);

    Vector2 operator* (const Vector2 &other) const;
    Vector2 &operator*= (const Vector2 &other);

    Vector2 operator/ (const Vector2 &other) const;
    Vector2 &operator/= (const Vector2 &other);

    Vector2 operator- () const;

    operator Vector2i () const;
    Vector2 absolute () const;

    float length () const;
    float dot (const Vector2 &other) const;
    float cross (const Vector2 &other) const;

    Vector2 normalized () const;
    Vector2 floor () const;
    Vector2 ceil () const;
    Vector2 round () const;

    Vector2 rotate (float radians) const;
    Vector2 scale (const Vector2 &scale) const;
    Vector2 translate (const Vector2 &translate) const;

    bool isZero () const;

    float x = 0, y = 0;
    std::string toString () const;

    float angleBetween (const Vector2 &source, const Vector2 &destination);
    float distanceBetween (const Vector2 &source, const Vector2 &destination);
};
}
