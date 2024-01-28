#include "Physics.h"

Vec2 phy_GetOverlap(Entity * a, Entity * b)
{
  Vec2 aPos = a->cTransform->pos;
  Vec2 bPos = b->cTransform->pos;
  Vec2 aSize = a->cBoundingBox->size;
  Vec2 bSize = b->cBoundingBox->size;

  Vec2 delta = {abs(aPos.x - bPos.x), abs(aPos.y - bPos.y)};
  float overlapX = (aSize.x / 2 + bSize.x / 2) - delta.x;
  float overlapY = (aSize.y / 2 + bSize.y / 2) - delta.y;
  return (Vec2){overlapX,overlapY};
}

Vec2 phy_GetPrevOverlap(Entity * a, Entity * b)
{
  Vec2 aPos = a->cTransform->prevpos;
  Vec2 bPos = b->cTransform->prevpos;
  Vec2 aSize = a->cBoundingBox->size;
  Vec2 bSize = b->cBoundingBox->size;

  Vec2 delta = {abs(aPos.x - bPos.x), abs(aPos.y - bPos.y)};
  float overlapX = (aSize.x / 2 + bSize.x / 2) - delta.x;
  float overlapY = (aSize.y / 2 + bSize.y / 2) - delta.y;
  return (Vec2) { overlapX, overlapY };
}