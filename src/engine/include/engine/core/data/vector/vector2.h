#pragma once

namespace ObsidianEdge
{
class Vector2
{
  public:
    Vector2 ();
    Vector2 (float x, float y);

    ~Vector2 () = default;

    Vector2 operator+ (Vector2 &other) const;
    Vector2 &operator+= (Vector2 &other);

    Vector2 operator- (Vector2 &other) const;
    Vector2 &operator-= (Vector2 &other);

    Vector2 operator* (float mul) const;
    Vector2 &operator*= (float mul);

    Vector2 operator/ (float mul) const;
    Vector2 &operator/= (float mul);

    Vector2 absolute () const;

    float length () const;
    float dot (Vector2 &other) const;
    Vector2 normalized () const;

    float x = 0, y = 0;

    static float angleBetween (Vector2 &source, Vector2 &destination);
    static float distanceBetween (Vector2 &source, Vector2 &destination);
};

}