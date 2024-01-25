#pragma once
#include <math.h>
#include <stdbool.h>

typedef struct 
{
  float x;
  float y;
} vec2;

vec2 vec2_add(vec2 a, vec2 b);

vec2 vec2_sub(vec2 a, vec2 b);

vec2 vec2_mul(vec2 a, float b);

vec2 vec2_div(vec2 a, float b);

float vec2_mag(vec2 a);

vec2 vec2_norm(vec2 a);

float vec2_dot(vec2 a, vec2 b);

float vec2_dist(vec2 a, vec2 b);

float vec2_angle(vec2 a);

bool vec2_eq(vec2 a, vec2 b);

bool vec2_neq(vec2 a, vec2 b);

