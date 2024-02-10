#pragma once
#include "SFML/Graphics.h"

typedef struct
{
  int width;
  int height;
} WindowConfig;

typedef struct
{
  int width;
  int height;
} PaddleConfig;

typedef struct
{
  int radius;
  float speed;
} BallConfig;

typedef struct
{
  PaddleConfig paddleConfig;
  BallConfig ballConfig;
  WindowConfig windowConfig;
} Config;
////////////////////////////////////////////////////////////
/// \brief main game loop
/// 
////////////////////////////////////////////////////////////
void g_Run();