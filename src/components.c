#include "components.h"
#include "entity.h"
#include <stdlib.h>

int com_CreateRectangle(CShape * shape, vec2 pos, int width, int height, sfColor FillColor)
{
  sfRectangleShape * rect = sfRectangleShape_create();
  sfRectangleShape_setPosition(rect, (sfVector2f){pos.x,pos.y});
  sfRectangleShape_setSize(rect, (sfVector2f){width,height});
  sfRectangleShape_setFillColor(rect,FillColor);
  *shape = (CShape){(sfShape*)rect,0,rect};
  return 0;
}

int com_CreateCircle(CShape * shape, vec2 pos, float radius, int points, sfColor FillColor)
{
  sfCircleShape * circ = sfCircleShape_create();
  sfCircleShape_setPosition(circ, (sfVector2f){pos.x,pos.y});
  sfCircleShape_setRadius(circ,radius);
  sfCircleShape_setFillColor(circ,FillColor);
  sfCircleShape_setPointCount(circ, points);
  *shape = (CShape){(sfShape*)circ,circ,0};

  return 0;
}
