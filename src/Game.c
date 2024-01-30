#include "Game.h"
#include "EntityManager.h"
#include <errno.h>
#include <stdio.h>

sfRenderWindow * m_window;
size_t m_currentFrame = 0;
bool m_running = true;
Entity * m_player;

sfColor m_white = {255,255,255,255};
sfColor m_black = {0,0,0,255};
sfColor m_red   = {255,0,0,255};
sfColor m_green = {0,255,0,255};
sfColor m_blue  = {0,0,255,255};

static void Render();
static void Destroy();
static void spawnPlayer();
static void Movement();
static void UserInput();
static void Init();

void Init()
{
  sfVideoMode mode = {800,600,32};
  m_window = sfRenderWindow_create(mode, "SFML window", sfDefaultStyle, NULL);
  sfRenderWindow_setFramerateLimit(m_window,60);
  em_Add("enemy");
  spawnPlayer();
  em_Update();
}


void g_Run()
{
  Init();

  while (m_running)
  {
    Render();
    Movement();
    UserInput();
    m_currentFrame++;
  }
  Destroy();
}

void spawnPlayer()
{
  m_player = em_Add("player"); 
  m_player->cScore = com_CreateScore(0);
  m_player->cTransform = com_CreateTransform((Vec2) { 0, 0 }, (Vec2) { 0, 0 }, 0);
  m_player->cCollision = com_CreateCollision(32);
  m_player->cInput = com_CreateInput();
  m_player->cShape = com_CreateCircle((Vec2) { 100, 100 }, 32.0, 8, m_blue, 2.0, m_red);
  m_player->cBoundingBox = com_CreateBounding((Vec2) { 64, 64 });
}

void Render()
{
  sfRenderWindow_clear(m_window, m_black);
  Entity * m_entities = em_GetEntities();
  Entity * e;

  for (int i = 0; i < em_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cShape == NULL || e->cTransform == NULL) continue;
    sfShape_setPosition(e->cShape->shape,(sfVector2f){e->cTransform->pos.x,e->cTransform->pos.y});
    sfRenderWindow_drawCircleShape(m_window,e->cShape->circle, NULL);
  }
  sfRenderWindow_display(m_window);
}

void Destroy()
{
  sfRenderWindow_destroy(m_window);
  em_Destroy();
}

void Movement()
{
  m_player->cTransform->vel = (Vec2){0,0};

  if (m_player->cInput->up)
  {
    m_player->cTransform->vel.y = -5;
  }
  if (m_player->cInput->left)
  {
    m_player->cTransform->vel.x = -5;
  }
  if (m_player->cInput->down)
  {
    m_player->cTransform->vel.y = 5;
  }
  if (m_player->cInput->right)
  {
    m_player->cTransform->vel.x = 5;
  }

  Entity * m_entities = em_GetEntities();
  Entity * e;
  
  for (int i = 0; i < em_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cTransform == NULL) continue;
    e->cTransform->pos.x += e->cTransform->vel.x;
    e->cTransform->pos.y += e->cTransform->vel.y;
    e->cTransform->angle += 1.0f;
  }
}

void UserInput()
{
  sfEvent event;
  while(sfRenderWindow_pollEvent(m_window, &event))
  {
    if (event.type == sfEvtClosed)
    {
      m_running = false;
    }

    if (event.type == sfEvtMouseButtonPressed)
    {
      if (event.mouseButton.button == sfMouseLeft)
      {
        printf("Left mouse button pressed\n");
        // spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
      }
      if (event.mouseButton.button == sfMouseRight)
      {
        printf("Right mouse button pressed\n");
        // spawnSpecialWeapon(m_player);
      }
    }
    if (event.type == sfEvtKeyPressed)
    {
      switch (event.key.code)
      {
        case sfKeyW:
          printf("W pressed\n");
          m_player->cInput->up = true;
          break;
        case sfKeyA:
          printf("A pressed\n");
          m_player->cInput->left = true;
          break;
        case sfKeyS:
          printf("S pressed\n");
          m_player->cInput->down = true;
          break;
        case sfKeyD:
          printf("D pressed\n");
          m_player->cInput->right = true;
          break;
        case sfKeySpace:
          printf("Space pressed\n");
          // setPaused(!m_paused);
          break;
        default:
          break;
      }
    }

    if (event.type == sfEvtKeyReleased)
    {
      switch (event.key.code)
      {
        case sfKeyW:
          printf("W released\n");
          m_player->cInput->up = false;
          break;
        case sfKeyA:
          printf("A released\n");
          m_player->cInput->left = false; 
          break;
        case sfKeyS:
          printf("S released\n");
          m_player->cInput->down = false;
          break;
        case sfKeyD:
          printf("D released\n");
          m_player->cInput->right = false;
          break;

        default:
          break;

      }
    }
  }
}
