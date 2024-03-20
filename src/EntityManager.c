#include "EntityManager.h"

#include <stdlib.h>

#include "Utils.h"

#define MAX_ENTITIES 300

static EntityManager m_entityManager;
static size_t m_entities_to_add;
static size_t m_passed_count;

static void Init()
{
  m_entities_to_add = 0;
  m_entityManager.total = 0;
  m_entityManager.entities = safe_malloc(sizeof(Entity) * MAX_ENTITIES);
  m_entityManager.entitiesToAdd = safe_malloc(sizeof(Entity) * MAX_ENTITIES);
  m_entityManager.entitiesToPass = safe_malloc(sizeof(Entity) * MAX_ENTITIES);
}

Entity * em_Add(eEntitiesType id, eLevelEntities tag)
{
  if (m_entityManager.entities == NULL ||
      m_entityManager.entitiesToAdd == NULL) {
    Init();
  }
  Entity entity = {.active = true, .tag = tag, .id = id};
  m_entityManager.entitiesToAdd[m_entities_to_add++] = entity;
  return (m_entityManager.entitiesToAdd + m_entities_to_add - 1);
}

static void RemoveDeadEntities()
{
  for (int i = 0; i < m_entityManager.total; ++i) {
    Entity * entity = &m_entityManager.entities[i];
    if (!entity->active) {
      m_entityManager.entities[i] = m_entityManager.entities[i + 1];
      m_entityManager.total--;
    }
  }
  return;
}

void em_Update()
{
  for (size_t i = 0; i < m_entities_to_add; ++i) {
    Entity * entity = &m_entityManager.entitiesToAdd[i];
    entity->id = m_entityManager.total;
    m_entityManager.entities[m_entityManager.total++] = *entity;
  }
  m_entities_to_add = 0;
  RemoveDeadEntities();
}

Entity * em_GetEntitiesByTag(eLevelEntities tag)
{
  m_passed_count = 0;

  for (int i = 0; i < m_entityManager.total; ++i) {
    if (m_entityManager.entities[i].tag == tag) {
      m_entityManager.entitiesToPass[m_passed_count++] =
          m_entityManager.entities[i];
    }
  }
  return m_entityManager.entitiesToPass;
}

Entity * em_GetEntitiesById(eEntitiesType id)
{
  m_passed_count = 0;

  for (int i = 0; i < m_entityManager.total; ++i) {
    if (m_entityManager.entities[i].id == id) {
      m_entityManager.entitiesToPass[m_passed_count++] =
          m_entityManager.entities[i];
    }
  }
  return m_entityManager.entitiesToPass;
}

size_t em_GetPassedCount()
{
  return m_passed_count;
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
  for (int i = 0; i < m_entityManager.total; ++i) {
    e = m_entityManager.entities + i;
    free(e->cShape);
    free(e->cTransform);
    free(e->cInput);
    free(e->cScore);
    free(e->cLifespan);
    free(e->cBoundingBox);
  }
  free(m_entityManager.entities);
  free(m_entityManager.entitiesToAdd);
  free(m_entityManager.entitiesToPass);
}
