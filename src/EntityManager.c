#include "EntityManager.h"
#include "Utils.h"

#define MAX_ENTITIES 300

EntityManager m_entityManager;
size_t m_entities_to_add;

static void Init();

void Init()
{
  m_entities_to_add = 0;
  m_entityManager.total = 0;
  m_entityManager.entities = safe_malloc(sizeof(Entity) * MAX_ENTITIES);
  m_entityManager.entitiesToAdd = safe_malloc(sizeof(Entity) * MAX_ENTITIES);
}

Entity * em_Add(const char * tag)
{
  if (m_entityManager.entities == NULL || m_entityManager.entitiesToAdd == NULL)
  {
    Init();
  }
  Entity * entity = safe_malloc(sizeof(Entity));
  entity->active = true;
  entity->cTransform = NULL;
  entity->cShape = NULL;
  entity->cCollision = NULL;
  entity->cScore = NULL;
  entity->cLifespan = NULL;
  entity->cInput = NULL;
  entity->cBoundingBox = NULL;
  strcpy_s(entity->tag,sizeof(entity->tag), tag);
  m_entityManager.entitiesToAdd[m_entities_to_add++] = *entity;
  free(entity);
  return (m_entityManager.entitiesToAdd + m_entities_to_add - 1);
}

void removeDeadEntities(Entity * entity)
{
  for (int i = 0; i < m_entityManager.total; ++i)
  {
    Entity * entity = &m_entityManager.entities[i];
    if (!entity->active)
    {
      m_entityManager.entities[i] = m_entityManager.entities[i + 1];
      m_entityManager.entities[i].id = i;
      m_entityManager.total--;
    }
  }
  return;
}

void em_Update()
{
  for (size_t i = 0; i < m_entities_to_add; ++i)
  {
    Entity * entity = &m_entityManager.entitiesToAdd[i];
    entity->id = m_entityManager.total;
    m_entityManager.entities[m_entityManager.total++] = *entity;
  }
  m_entities_to_add = 0;

}

Entity * em_GetEntitiesByTag(const char * tag, size_t * size)
{
  size_t count = 0;
  Entity * max_entities = safe_malloc(sizeof(Entity) * MAX_ENTITIES);

  for (int i = 0; i < m_entityManager.total; ++i)
  {
    Entity * entity = &m_entityManager.entities[i];
    if (strcmp(entity->tag, tag) == 0)
    {
      max_entities[count++] = *entity;
    }
  }
  *size = count;
  Entity * entities = safe_malloc(sizeof(Entity) * count);
  memcpy(entities, max_entities, count);
  free(max_entities);
  return entities;

}

Entity * em_GetEntitiesById(int id1, int id2, size_t * size)
{
  size_t count = 0;
  Entity * max_entities = safe_malloc(sizeof(Entity) * MAX_ENTITIES);
  id2 = id2 > m_entityManager.total ? m_entityManager.total : id2;

  for (int i = 0; i < m_entityManager.total; ++i)
  {
    Entity * entity = &m_entityManager.entities[i];
    if (entity->id >= id1 && entity->id <= id2)
    {
      max_entities[count++] = *entity;
    }
  }
  *size = count;
  Entity * entities = safe_malloc(sizeof(Entity) * count);
  memcpy(entities, max_entities, count);
  free(max_entities);
  return entities;
}

Entity * em_GetEntities()
{
  return m_entityManager.entities;
}

int em_GetTotalEntities()
{
  return m_entityManager.total;
}

void em_Destroy()
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