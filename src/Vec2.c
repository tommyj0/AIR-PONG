#include "Vec2.h"

Vec2 Vec2_add(Vec2 a, Vec2 b)
{
  Vec2 result = {a.x + b.x, a.y + b.y};
  return result;
}

Vec2 Vec2_sub(Vec2 a, Vec2 b)
{
  Vec2 result = {a.x - b.x, a.y - b.y};
  return result;
}

Vec2 Vec2_mul(Vec2 a, float b)
{
  Vec2 result = {a.x * b, a.y * b};
  return result;
}

Vec2 Vec2_div(Vec2 a, float b)
{
  Vec2 result = {a.x / b, a.y / b};
  return result;
}

float Vec2_mag(Vec2 a)
{
  return sqrt(a.x * a.x + a.y * a.y);
}

Vec2 Vec2_norm(Vec2 a)
{
  float mag = Vec2_mag(a);
  Vec2 result = {a.x / mag, a.y / mag};
  return result;
}

float Vec2_dot(Vec2 a, Vec2 b)
{
  return a.x * b.x + a.y * b.y;
}

float Vec2_dist(Vec2 a, Vec2 b)
{
  return Vec2_mag(Vec2_sub(a, b));
}

float Vec2_angle(Vec2 a)
{
  return atan2(a.y, a.x);
}

bool Vec2_eq(Vec2 a, Vec2 b)
{
  return a.x == b.x && a.y == b.y;
}

bool Vec2_neq(Vec2 a, Vec2 b)
{
  return a.x != b.x || a.y != b.y;
}

Vec2 Vec2_setRotate(Vec2 a, float angle)
{
  return Vec2_mul((Vec2){cos(angle), sin(angle)}, Vec2_mag(a));
}

Vec2 Vec2_Polar(float mag, float angle)
{
  return (Vec2){mag * cosf(angle), mag * sinf(angle)};
}
