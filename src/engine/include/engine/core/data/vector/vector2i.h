#pragma once

namespace ObsidianEdge
{
class Vector2i
{
  public:
    Vector2i ();
    Vector2i (int x, int y);

    ~Vector2i () = default;

    Vector2i operator+ (Vector2i &other) const;
    Vector2i &operator+= (Vector2i &other);

    Vector2i operator- (Vector2i &other) const;
    Vector2i &operator-= (Vector2i &other);

    Vector2i operator* (float mul) const;
    Vector2i &operator*= (float mul);

    Vector2i operator/ (float mul) const;
    Vector2i &operator/= (float mul);

    Vector2i absolute () const;

    int length () const;
    int dot (Vector2i &other) const;
    Vector2i normalized () const;

    int x = 0, y = 0;

    static int angleBetween (Vector2i &source, Vector2i &destination);
    static int distanceBetween (Vector2i &source, Vector2i &destination);
};
}