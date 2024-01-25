#include "game.h"
#include "entity.h"
#include <errno.h>
#include <stdio.h>

sfRenderWindow * m_window;
size_t m_currentFrame = 0;
Entity * m_player;

sfColor m_white = {255,255,255,255};
sfColor m_black = {0,0,0,255};
sfColor m_red   = {255,0,0,255};
sfColor m_green = {0,255,0,255};
sfColor m_blue  = {0,0,255,255};

void Render();
void Destroy();
void spawnPlayer();
void Movement();

void Init()
{
  sfVideoMode mode  = {800,600,32};
  m_window = sfRenderWindow_create(mode, "SFML window", sfDefaultStyle, NULL);
  sfRenderWindow_setFramerateLimit(m_window,60);
  ent_Init();
}


void g_Run()
{
  Init();
  
  ent_Add("enemy");
  spawnPlayer();
  ent_Update();
 

  sfEvent Event;

  while (sfRenderWindow_isOpen(m_window))
  {
    Render();
    Movement();
    while (sfRenderWindow_pollEvent(m_window, &Event)) 
    {
      if (Event.type == sfEvtClosed)
      {
        Destroy();
      }
    }
  }
}

void spawnPlayer()
{
  m_player = ent_Add("player");
  m_player->cScore = malloc(sizeof(CScore));
  *m_player->cScore = (CScore){0};
  m_player->cTransform = malloc(sizeof(CTransform));
  *m_player->cTransform = (CTransform){(vec2){1.0,1.0}, (vec2){1.0,1.0}, 0.0};
  m_player->cCollision = malloc(sizeof(CCollision));
  *m_player->cCollision = (CCollision){0};
  m_player->cInput = malloc(sizeof(CInput));
  *m_player->cInput = (CInput){0};
  m_player->cShape = malloc(sizeof(CShape));
  com_CreateCircle(m_player->cShape, (vec2){100,100}, 32, 8, m_blue);
}

void Render()
{
  sfRenderWindow_clear(m_window, m_black);
  Entity * m_entities = ent_GetEntities();
  Entity * e;

  for (int i = 0; i < ent_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cShape == NULL || e->cTransform == NULL) continue;
    sfShape_setPosition(e->cShape->shape,(sfVector2f){e->cTransform->pos.x,e->cTransform->pos.x});
    sfShape_setRotation(e->cShape->shape,e->cTransform->angle);
    sfRenderWindow_drawCircleShape(m_window,e->cShape->circle, NULL);
  }
  sfRenderWindow_display(m_window);
}

void Destroy()
{
  sfRenderWindow_destroy(m_window);
  ent_Destroy();
}

void Movement()
{
  Entity * m_entities = ent_GetEntities();
  Entity * e;
  
  for (int i = 0; i < ent_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cShape == NULL || e->cTransform == NULL) continue;
    e->cTransform->pos.x += e->cTransform->vel.x;
    e->cTransform->pos.y += e->cTransform->vel.y;
    e->cTransform->angle += 1.0f;
  }
}
