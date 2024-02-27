#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#define PI 3.14159f
#include <stdbool.h>

typedef struct 
{
  float x;
  float y;
} Vec2;

Vec2 Vec2_add(Vec2 a, Vec2 b);

Vec2 Vec2_sub(Vec2 a, Vec2 b);

Vec2 Vec2_mul(Vec2 a, float b);

Vec2 Vec2_div(Vec2 a, float b);

float Vec2_mag(Vec2 a);

Vec2 Vec2_norm(Vec2 a);

float Vec2_dot(Vec2 a, Vec2 b);

float Vec2_dist(Vec2 a, Vec2 b);

float Vec2_angle(Vec2 a);

bool Vec2_eq(Vec2 a, Vec2 b);

bool Vec2_neq(Vec2 a, Vec2 b);

Vec2 Vec2_setRotate(Vec2 a, float angle);

Vec2 Vec2_Polar(float mag, float angle);
