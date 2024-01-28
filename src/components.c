#include "Components.h"
#include "Entity.h"
#include <stdlib.h>

CScore *  com_CreateScore(int initVal)
{
  CScore * score = malloc(sizeof(CScore));
  score->score = initVal;
  return score;
}

CInput * com_CreateInput()
{
  CInput * input = malloc(sizeof(CInput));
  input->up = false;
  input->down = false;
  input->left = false;
  input->right = false;
  input->shoot = false;
  input->canJump = true;
  input->canShoot = true;
  return input;
}

CCollision * com_CreateCollision(float rad)
{
  CCollision * col = malloc(sizeof(CCollision));
  col->radius = rad;
  return col;
}

CTransform * com_CreateTransform(Vec2 pos, Vec2 vel, float angle)
{
  CTransform * transform = malloc(sizeof(CTransform));
  transform->pos = (Vec2){0,0};
  transform->prevpos = (Vec2){0,0};
  transform->vel = (Vec2){0,0};
  transform->angle = 0;
  return transform;

}

CShape * com_CreateRectangle(Vec2 pos, int width, int height, sfColor FillColor)
{
  CShape * shape = malloc(sizeof(CShape));
  sfRectangleShape * rect = sfRectangleShape_create();
  sfRectangleShape_setPosition(rect, (sfVector2f){pos.x,pos.y});
  sfRectangleShape_setSize(rect, (sfVector2f){width,height});
  sfRectangleShape_setFillColor(rect,FillColor);
  *shape = (CShape){(sfShape*)rect,0,rect};
  return shape;
}

CShape * com_CreateCircle(Vec2 pos, float radius, int points, sfColor FillColor)
{
  CShape * shape = malloc(sizeof(CShape));
  sfCircleShape * circ = sfCircleShape_create();
  sfCircleShape_setPosition(circ, (sfVector2f){pos.x,pos.y});
  sfCircleShape_setRadius(circ,radius);
  sfCircleShape_setFillColor(circ,FillColor);
  sfCircleShape_setPointCount(circ, points);
  *shape = (CShape){(sfShape*)circ,circ,0};

  return shape;
}
