#include "Components.h"

#include "Utils.h"

CScore * com_CreateScore(int initVal)
{
  CScore * score = safe_malloc(sizeof(CScore));
  score->score = initVal;

  return score;
}

CInput * com_CreateInput()
{
  CInput * input = safe_malloc(sizeof(CInput));
  *input = (CInput){.canJump = true, .canShoot = true};

  return input;
}

CTransform * com_CreateTransform(Vec2 pos, Vec2 vel, float angle)
{
  CTransform * transform = safe_malloc(sizeof(CTransform));
  *transform = (CTransform){.pos = pos, .vel = vel, .angle = angle};

  return transform;
}

CShape * com_CreateRectangle(Vec2 pos, float width, float height,
                             sfColor FillColor)
{
  CShape * shape = safe_malloc(sizeof(CShape));
  sfRectangleShape * rect = sfRectangleShape_create();
  sfRectangleShape_setPosition(rect, (sfVector2f){pos.x, pos.y});
  sfRectangleShape_setSize(rect, (sfVector2f){width, height});
  sfRectangleShape_setFillColor(rect, FillColor);
  *shape = (CShape){.shape = (sfShape *)rect, .rect = rect};

  return shape;
}

CShape * com_CreateCircle(Vec2 pos, float radius, int points, sfColor FillColor,
                          float thickness, sfColor OutColor)
{
  CShape * shape = safe_malloc(sizeof(CShape));
  sfCircleShape * circ = sfCircleShape_create();
  sfCircleShape_setPosition(circ, (sfVector2f){pos.x, pos.y});
  sfCircleShape_setRadius(circ, radius);
  sfCircleShape_setFillColor(circ, FillColor);
  sfCircleShape_setPointCount(circ, points);
  sfCircleShape_setOutlineThickness(circ, thickness);
  sfCircleShape_setOutlineColor(circ, OutColor);
  *shape = (CShape){.shape = (sfShape *)circ, .circle = circ};

  return shape;
}

CBoundingBox * com_CreateBounding(Vec2 size)
{
  CBoundingBox * bounds = safe_malloc(sizeof(CBoundingBox));
  *bounds = (CBoundingBox){.size = size};
  bounds->size = size;

  return bounds;
}
