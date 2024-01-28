#pragma once
#include "Vec2.h"
#include "Components.h"
#include <stdlib.h>
#include <string.h>
#define MAX_ENTITIES 300

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

typedef struct 
{
  Entity* entities;
  Entity* entitiesToAdd;
  int total;
} EntityManager;

////////////////////////////////////////////////////////////
/// \brief initialise the entity manager
/// 
////////////////////////////////////////////////////////////
void ent_Init();

////////////////////////////////////////////////////////////
/// \brief add entity to manager
/// 
/// \param tag string 
////////////////////////////////////////////////////////////
Entity * ent_Add(const char * tag);

////////////////////////////////////////////////////////////
/// \brief returns an array of entities with given tag
/// 
/// \param tag string 
/// \param size pass size_t* to get the array length
////////////////////////////////////////////////////////////
Entity * ent_GetEntitiesByTag(const char* tag, size_t * size);

////////////////////////////////////////////////////////////
/// \brief returns an array of entities in given ID range
/// 
////////////////////////////////////////////////////////////
Entity * ent_GetEntitiesById(int id1, int id2, size_t * size);

Entity * ent_GetEntities();

int ent_GetTotalEntities();

void ent_Update();

void ent_Destroy();

