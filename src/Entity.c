#include "Entity.h"

#include "EntityManager.h"
#include "Utils.h"

void ent_Destroy(Entity* a)
{
  a->active = false;
}

eEntitiesType ent_GetId(Entity* a)
{
  return a->id;
}

eLevelEntities ent_GetTag(Entity* a)
{
  return a->tag;
}
