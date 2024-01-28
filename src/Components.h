#pragma once
#include "Vec2.h"
#include "SFML/Graphics.h"

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
  Vec2 vel;
  float angle;
} CTransform;

////////////////////////////////////////////////////////////
/// \brief shape for circle
///
/// \param circle something
////////////////////////////////////////////////////////////
typedef struct 
{
  sfShape * shape;
  sfCircleShape * circle;
  sfRectangleShape * rect;
} CShape;

////////////////////////////////////////////////////////////
/// \brief radius for circle collision
/// 
/// \param radius
////////////////////////////////////////////////////////////
typedef struct 
{
  float radius;
} CCollision;

////////////////////////////////////////////////////////////
/// \brief score for entity
/// 
/// \param score
////////////////////////////////////////////////////////////
typedef struct 
{
  int score;
} CScore;

////////////////////////////////////////////////////////////
/// \brief lifespan tracker
/// 
/// \param total
/// \param remaining
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

CScore *  com_CreateScore(int initVal);

CCollision * com_CreateCollision(float rad);

CShape * com_CreateRectangle(Vec2 pos, int width, int height, sfColor FillColor);

CShape * com_CreateCircle(Vec2 pos, float radius, int points, sfColor FillColor);




