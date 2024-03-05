#pragma once
#include "SFML/Graphics.h"
#include "Vec2.h"

////////////////////////////////////////////////////////////
/// \brief describes movement and rotation of an entity
///
/// \param pos 2D position
/// \param vel 2D velocity
/// \param angle float angle in rad
////////////////////////////////////////////////////////////
typedef struct
{
  Vec2 pos;
  Vec2 prevpos;
  Vec2 scale;
  Vec2 vel;
  float angle;
} CTransform;

////////////////////////////////////////////////////////////
/// \brief shape for circle
///
/// \param shape ptr
/// \param circle ptr
/// \param rect ptr
////////////////////////////////////////////////////////////
typedef struct
{
  sfShape * shape;
  sfCircleShape * circle;
  sfRectangleShape * rect;
} CShape;

////////////////////////////////////////////////////////////
/// \brief score for entity
///
/// \param score - you'll never guess what this is
////////////////////////////////////////////////////////////
typedef struct
{
  int score;
} CScore;

////////////////////////////////////////////////////////////
/// \brief lifespan tracker
///
/// \param total
/// \param remaining - decrement remaining until Entity dies
////////////////////////////////////////////////////////////
typedef struct
{
  int total;
  int remaining;
} CLifespan;

////////////////////////////////////////////////////////////
/// \brief input of entity
///
////////////////////////////////////////////////////////////
typedef struct
{
  bool up;
  bool down;
  bool left;
  bool right;
  bool shoot;
  bool canShoot;
  bool canJump;
} CInput;

typedef struct
{
  Vec2 size;
} CBoundingBox;

CTransform * com_CreateTransform(Vec2 pos, Vec2 vel, float angle);

CInput * com_CreateInput();

CScore * com_CreateScore(int initVal);

CShape * com_CreateRectangle(Vec2 pos, float width, float height,
                             sfColor FillColor);

CShape * com_CreateCircle(Vec2 pos, float radius, int points, sfColor FillColor,
                          float thickness, sfColor OutColor);

CBoundingBox * com_CreateBounding(Vec2 size);
