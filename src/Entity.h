#pragma once
#include "Vec2.h"
#include "Components.h"
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char tag[32];
  int id;
  bool active;
  CTransform* cTransform;
  CShape* cShape;
  CCollision* cCollision;
  CScore* cScore;
  CLifespan* cLifespan;
  CInput* cInput;
  CBoundingBox * cBoundingBox;
} Entity;

void ent_Destroy(Entity * a);

int ent_GetId(Entity * a);

const char * ent_GetTag(Entity * a);

