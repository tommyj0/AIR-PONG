#include "Physics.h"

Vec2 phy_GetOverlap(Entity * a, Entity * b)
{
  if (a->cTransform == NULL || b->cTransform == NULL ||
      a->cBoundingBox == NULL || b->cBoundingBox == NULL)
  {
    return (Vec2) { 0, 0 };
  }
  Vec2 aPos = a->cTransform->pos;
  Vec2 bPos = b->cTransform->pos;
  Vec2 aSize = a->cBoundingBox->size;
  Vec2 bSize = b->cBoundingBox->size;

  Vec2 delta = {(float)fabs(aPos.x - bPos.x), (float)fabs(aPos.y - bPos.y)};
  float overlapX = (aSize.x / 2 + bSize.x / 2) - delta.x;
  float overlapY = (aSize.y / 2 + bSize.y / 2) - delta.y;
  if (overlapX <= 0 || overlapY <= 0)
  {
    return (Vec2) { 0, 0 };
  }
  return (Vec2){overlapX,overlapY};
}

Vec2 phy_GetPrevOverlap(Entity * a, Entity * b)
{
  if (a->cTransform == NULL || b->cTransform == NULL ||
      a->cBoundingBox == NULL || b->cBoundingBox == NULL)
  {
    return (Vec2) { 0, 0 };
  }

  Vec2 aPos = a->cTransform->prevpos;
  Vec2 bPos = b->cTransform->prevpos;
  Vec2 aSize = a->cBoundingBox->size;
  Vec2 bSize = b->cBoundingBox->size;

  Vec2 delta = {(float)fabs(aPos.x - bPos.x), (float)fabs(aPos.y - bPos.y)};
  float overlapX = (aSize.x / 2 + bSize.x / 2) - delta.x;
  float overlapY = (aSize.y / 2 + bSize.y / 2) - delta.y;
  if (overlapX <= 0 || overlapY <= 0)
  {
    return (Vec2) { 0, 0 };
  }

  return (Vec2) { overlapX, overlapY };
}