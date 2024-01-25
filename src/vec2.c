#include "vec2.h"

vec2 vec2_add(vec2 a, vec2 b)
{
  vec2 result = {a.x + b.x, a.y + b.y};
  return result;
}

vec2 vec2_sub(vec2 a, vec2 b)
{
  vec2 result = {a.x - b.x, a.y - b.y};
  return result;
}

vec2 vec2_mul(vec2 a, float b)
{
  vec2 result = {a.x * b, a.y * b};
  return result;
}

vec2 vec2_div(vec2 a, float b)
{
  vec2 result = {a.x / b, a.y / b};
  return result;
} 

float vec2_mag(vec2 a)
{
  return sqrt(a.x * a.x + a.y * a.y);
}

vec2 vec2_norm(vec2 a)
{
  float mag = vec2_mag(a);
  vec2 result = {a.x / mag, a.y / mag};
  return result;
}

float vec2_dot(vec2 a, vec2 b)
{
  return a.x * b.x + a.y * b.y;
}

float vec2_dist(vec2 a, vec2 b)
{
  return vec2_mag(vec2_sub(a, b));
}

float vec2_angle(vec2 a)
{
  return atan2(a.y, a.x);
}

bool vec2_eq(vec2 a, vec2 b)
{
  return a.x == b.x && a.y == b.y;
}

bool vec2_neq(vec2 a, vec2 b)
{
  return a.x != b.x || a.y != b.y;
}