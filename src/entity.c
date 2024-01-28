#include "Entity.h"
#include <stdio.h>

EntityManager m_entityManager = { 0 };
size_t m_entities_to_add = 0;

void ent_Init()
{
  m_entityManager.total = 0;
  m_entityManager.entities = malloc(sizeof(Entity) * MAX_ENTITIES);
  m_entityManager.entitiesToAdd = malloc(sizeof(Entity) * MAX_ENTITIES);
}

Entity * ent_Add(const char * tag)
{
  Entity entity;
  entity.active = true;
  entity.cTransform = NULL;
  entity.cShape = NULL;
  entity.cCollision = NULL;
  entity.cScore = NULL;
  entity.cLifespan = NULL;
  entity.cInput = NULL;
  entity.cBoundingBox = NULL;
  strcpy_s(entity.tag,sizeof(tag), tag);
  m_entityManager.entitiesToAdd[m_entities_to_add++] = entity;
  return (m_entityManager.entitiesToAdd + m_entities_to_add - 1);
}

void removeDeadEntities(Entity * entity)
{
  for (int i = entity->id; i < m_entityManager.total; ++i)
  {
    m_entityManager.entities[i] = m_entityManager.entities[i + 1];
    m_entityManager.entities[i].id = i;
  }
  m_entityManager.total--;
  return;
}

void ent_Update()
{
  for (size_t i = 0; i < m_entities_to_add; ++i)
  {
    Entity* entity = &m_entityManager.entitiesToAdd[i];
    entity->id = m_entityManager.total;
    m_entityManager.entities[m_entityManager.total++] = *entity;
  }
  m_entities_to_add = 0;
  for (int i = 0; i < m_entityManager.total; ++i)
  {
    Entity* entity = &m_entityManager.entities[i];
    if (!entity->active)
    {
      removeDeadEntities(entity);
    }
  }
}

Entity * ent_GetEntitiesByTag(const char* tag, size_t * size)
{
  size_t count = 0;
  Entity * max_entities = malloc(sizeof(Entity)*MAX_ENTITIES);
  
  for (int i = 0; i < m_entityManager.total; ++i)
  {
    Entity* entity = &m_entityManager.entities[i];
    if (strcmp(entity->tag, tag) == 0)
    {
      max_entities[count++] = *entity;
    }
  }
  *size = count;
  Entity * entities = malloc(sizeof(Entity)*count);
  memcpy(entities, max_entities, count);
  free(max_entities);
  return entities;
  
}

Entity * ent_GetEntitiesById(int id1, int id2, size_t * size)
{
  size_t count = 0;
  Entity * max_entities = malloc(sizeof(Entity)*MAX_ENTITIES);
  id2 = id2 > m_entityManager.total? m_entityManager.total : id2;

  for (int i = 0; i < m_entityManager.total; ++i)
  {
    Entity * entity = &m_entityManager.entities[i];
    if (entity->id >= id1 && entity->id <= id2)
    {
      max_entities[count++] = *entity;
    }
  }
  *size = count;
  Entity * entities = malloc(sizeof(Entity)*count);
  memcpy(entities, max_entities, count);
  free(max_entities);
  return entities; 
}

Entity * ent_GetEntities()
{
  return m_entityManager.entities;
}

int ent_GetTotalEntities()
{
  return m_entityManager.total;
}

void ent_Destroy()
{
  Entity * e;
  for (int i = 0; i < m_entityManager.total; ++i)
  {
    e = m_entityManager.entities + i;
    free(e->cShape);
    free(e->cTransform);
    free(e->cCollision);
    free(e->cInput);
    free(e->cScore);
    free(e->cLifespan);
    free(e->cBoundingBox);
  }
  free(m_entityManager.entities);
  free(m_entityManager.entitiesToAdd);
}
