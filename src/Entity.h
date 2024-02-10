#pragma once
#include "Vec2.h"
#include "Components.h"
#include <stdlib.h>
#include <string.h>


typedef enum 
{
  PLAYER,
  PLAYER2,
  BRICK,
  CLOUDBIG,
  GROUND,
  CEILING,
  BUSHBIG,
  QUESTION,
  BUSHSMALL,
  FLAGPOLE,
  PIPESMALL,
  BLOCK,
  BUSH,
  COIN,
  CLOUDSMALL,
  BULLET,
  SMALLBUSH,
  PIPE,
  BUSHER,
  GOOMBA,
  BCLOUD,
  BALL,
  LAST
} eLevelEntities;

typedef enum 
{
  DYNAMIC,
  TILE,
  DEC,
} eEntitiesType;

typedef struct
{
  eLevelEntities tag;
  eEntitiesType id;
  bool active;
  CTransform* cTransform;
  CShape* cShape;
  CScore* cScore;
  CLifespan* cLifespan;
  CInput* cInput;
  CBoundingBox * cBoundingBox;
} Entity;

void ent_Destroy(Entity * a);

eEntitiesType ent_GetId(Entity * a);

eLevelEntities ent_GetTag(Entity * a);

