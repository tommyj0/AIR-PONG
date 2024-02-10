#include "Game.h"
#include "EntityManager.h"
#include "Physics.h"
#include "ini.h"
#include <errno.h>
#include <stdio.h>
#include <time.h>


sfRenderWindow * m_window;
size_t m_currentFrame = 0;
bool m_running = true;
bool m_reset = true;
Entity * m_player, * m_player2;
const int width = 800, height = 600;
sfText * fps_counter, * score1, * score2;
sfFont * font;

sfColor m_white = {255,255,255,255};
sfColor m_black = {0,0,0,255};
sfColor m_red   = {255,0,0,255};
sfColor m_green = {0,255,0,255};
sfColor m_blue  = {0,0,255,255};
sfColor m_dgrey = {50,50,50,255};

Config m_config;

static void Render();
static void Destroy();
static void spawnPlayer();
static void spawnBall();
static void Movement();
static void UserInput();
static void Init();
static void Collision();
static int ReadConfig();
static void UpdateText();


static void Init()
{
  ReadConfig();
  sfVideoMode mode = {m_config.windowConfig.width,m_config.windowConfig.height,32};
  m_window = sfRenderWindow_create(mode, "AIR PONG", sfDefaultStyle, NULL);
  font = sfFont_createFromFile("C:/Dev/VS/COMP4300/2D-Engine/res/Roboto-Regular.ttf");
  fps_counter = sfText_create();
  score1 = sfText_create();
  score2 = sfText_create();
  sfText_setFont(fps_counter, font);
  sfText_setFont(score1, font);
  sfText_setFont(score2, font);
  sfText_setCharacterSize(score1, 60);
  sfText_setCharacterSize(score2, 60);
  sfText_setPosition(score1, (sfVector2f) { 32, 0 });
  sfText_setPosition(score2, (sfVector2f) { width - 64, 0 });
  sfText_setPosition(fps_counter, (sfVector2f) { width - 200, height - sfText_getCharacterSize(fps_counter)});
  sfRenderWindow_setFramerateLimit(m_window,60);
  spawnBall();
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
    Collision();
    UserInput();
    UpdateText();
    m_currentFrame++;

  }
  Destroy();
}

static void ResetBall(int dir)
{
  Entity * b = em_GetEntitiesByTag(BALL);
  b->cTransform->pos = (Vec2){width / 2, height / 2};
  b->cTransform->vel = dir == 1 ? (Vec2){m_config.ballConfig.speed,0} : (Vec2) { -m_config.ballConfig.speed, 0 };
}

static int INIHandler(void * user, const char * section, const char * name,
                   const char * value)
{
#define MATCH_S(s) strcmp(section, s) == 0
#define MATCH_N(n) strcmp(name, n) == 0
  if (MATCH_S("window"))
  {
    if (MATCH_N("height"))
    { m_config.windowConfig.height = atoi(value); }
    else if (MATCH_N("width"))
    { m_config.windowConfig.width = atoi(value); }
  }
  else if (MATCH_S("paddle"))
  {
    if (MATCH_N("height"))
    { m_config.paddleConfig.height = atoi(value); }
    else if (MATCH_N("width"))
    { m_config.paddleConfig.width = atoi(value); }
  }
  else if (MATCH_S("ball"))
  {
    if (MATCH_N("radius"))
    { m_config.ballConfig.radius = atoi(value); }
    else if (MATCH_N("speed"))
    { m_config.ballConfig.speed = atof(value); }
  }
  else
  { goto readerr; }
  return 1;

readerr:
  return 0;
}

static int ReadConfig()
{

  if (ini_parse("config.ini", INIHandler, NULL) < 0)
  {
    perror("Can't load 'config.ini'");
    return 1;
  }
  printf("Config loaded from 'test.ini':\nWindow: width=%d, height=%d\nBall: radius=%d, speed=%.2f\nPaddle: width=%d, height=%d\n",
         m_config.windowConfig.width, m_config.windowConfig.height , 
         m_config.ballConfig.radius, m_config.ballConfig.speed,
         m_config.paddleConfig.width, m_config.paddleConfig.height);
  return 0;
}

static void UpdateText()
{
  char counter[32];
  char buf[4];
  clock_t curr;
  static clock_t last = 0;
  float fps = 0;
  if (m_currentFrame % 60 == 0)
  {
    //currentTime = sfClock_getElapsedTime(clock);
    curr = clock();
    fps = 60.f / (curr - last);
    fps *= 1e3;
    last = curr;
    sprintf_s(counter, sizeof(counter), "FPS: %.0f", fps);

    sfText_setString(fps_counter, counter);
  }
  sprintf_s(buf, sizeof(buf), "%d", m_player->cScore->score);
  sfText_setString(score1, buf);
  sprintf_s(buf, sizeof(buf), "%d", m_player2->cScore->score);
  sfText_setString(score2, buf);
}

static void spawnPlayer()
{
  m_player = em_Add(DYNAMIC, PLAYER); 
  m_player->cScore = com_CreateScore(0);
  m_player->cTransform = com_CreateTransform((Vec2) { 0, 0 }, (Vec2) { 0, 0 }, 0);
  m_player->cInput = com_CreateInput();
  m_player->cShape = com_CreateRectangle((Vec2) { 0, 0 }, m_config.paddleConfig.width, m_config.paddleConfig.height, m_white);
  m_player->cBoundingBox = com_CreateBounding((Vec2) { m_config.paddleConfig.width, m_config.paddleConfig.height});

  m_player2 = em_Add(DYNAMIC, PLAYER2);
  m_player2->cScore = com_CreateScore(0);
  m_player2->cTransform = com_CreateTransform((Vec2) { width - m_config.paddleConfig.width, 0 }, (Vec2) { 0, 0 }, 0);
  m_player2->cInput = com_CreateInput();
  m_player2->cShape = com_CreateRectangle((Vec2) { 0, 0 }, m_config.paddleConfig.width, m_config.paddleConfig.height, m_white);
  m_player2->cBoundingBox = com_CreateBounding((Vec2) { m_config.paddleConfig.width, m_config.paddleConfig.height});

}

static void spawnBall()
{
  Entity * b = em_Add(DYNAMIC, BALL);
  b->cTransform = com_CreateTransform((Vec2) { width / 2, height / 2 }, (Vec2) { m_config.ballConfig.speed, 0}, 0.0f);
  b->cShape = com_CreateCircle((Vec2) { width / 2, height / 2 }, m_config.ballConfig.radius, 20, m_white, 0, m_white);
  b->cBoundingBox = com_CreateBounding((Vec2) { m_config.ballConfig.radius*2, m_config.ballConfig.radius*2});
}

static void Render()
{
  sfRenderWindow_clear(m_window, m_dgrey);
  Entity * m_entities = em_GetEntities();
  Entity * e;

  for (int i = 0; i < em_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cShape == NULL || e->cTransform == NULL)
    { continue; }
    sfShape_setPosition(e->cShape->shape,(sfVector2f){e->cTransform->pos.x,e->cTransform->pos.y});
    sfRenderWindow_drawShape(m_window,e->cShape->shape, NULL);
    sfRenderWindow_drawText(m_window, fps_counter, NULL);
    sfRenderWindow_drawText(m_window, score1, NULL);
    sfRenderWindow_drawText(m_window, score2, NULL);
  }
  sfRenderWindow_display(m_window);
}

static void Destroy()
{
  sfRenderWindow_destroy(m_window);
  em_Destroy();
}

static void Movement()
{
  Entity * m_entities = em_GetEntities();
  Entity * e;

  for (int i = 0; i < em_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cTransform == NULL) { continue; }
    if (e->cInput == NULL) { goto transforms; }
    e->cTransform->vel = (Vec2){0,0};
    if (e->cInput->up)
    {
      e->cTransform->vel.y = -5;
    }
    if (e->cInput->left)
    {
      e->cTransform->vel.x = -5;
    }
    if (e->cInput->down)
    {
      e->cTransform->vel.y = 5;
    }
    if (e->cInput->right)
    {
      e->cTransform->vel.x = 5;
    }
  transforms:
    e->cTransform->prevpos = e->cTransform->pos;
    e->cTransform->pos = Vec2_add(e->cTransform->pos, e->cTransform->vel);
  }
}

static void Collision()
{
  Entity * m_entities = em_GetEntities();
  Entity * e;
  Entity * ball = em_GetEntitiesByTag(BALL);
  if (ball == NULL)
  { return; }
  if (ball->cTransform == NULL || ball->cBoundingBox == NULL)
  { return; }

  // ball hitting top/bottom 
  if (ball->cTransform->pos.y <= 0)
    { ball->cTransform->vel.y = abs(ball->cTransform->vel.y); }
  else if (ball->cTransform->pos.y + ball->cBoundingBox->size.y >= m_config.windowConfig.height)
    { ball->cTransform->vel.y = -abs(ball->cTransform->vel.y); }

  if (ball->cTransform->pos.x + ball->cBoundingBox->size.x <= 0)
  {
    m_player2->cScore->score++;
    ResetBall(-1);
  }
  else if (ball->cTransform->pos.x  >= m_config.windowConfig.width)
  {
    m_player->cScore->score++;
    ResetBall(1);
  }
  
  for (int i = 0; i < em_GetTotalEntities(); ++i)
  {
    e = m_entities + i;
    if (e->cBoundingBox == NULL || e->cTransform == NULL) 
    { continue; }
    if (ent_GetTag(e) != BALL)
    {
      // paddle hitting top/bottom
      if (e->cTransform->pos.y < 0 || e->cTransform->pos.y + e->cBoundingBox->size.y >= m_config.windowConfig.height)
      { e->cTransform->pos = e->cTransform->prevpos; }
      // ball hitting paddle 
      Vec2 overlap = phy_GetOverlap(ball,e);
      if (overlap.x > 0 || overlap.y > 0)
      {
        float ball_mid = ball->cTransform->pos.y + ball->cBoundingBox->size.y / 2;
        float paddle_mid = e->cTransform->pos.y + e->cBoundingBox->size.y / 2;
        float diff = ball_mid - paddle_mid;
        diff = (diff * (M_PI*0.9)) / (ball->cBoundingBox->size.y + e->cBoundingBox->size.y);
        float angle = ent_GetTag(e) == PLAYER2 ? -diff + M_PI : diff;
        ball->cTransform->vel = Vec2_Polar(Vec2_mag(ball->cTransform->vel) + 0.5, Vec2_angle(ball->cTransform->vel));
        ball->cTransform->vel = Vec2_setRotate(ball->cTransform->vel, angle);
      }
    }
  }
}

static void UserInput()
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
      }
      if (event.mouseButton.button == sfMouseRight)
      {
        printf("Right mouse button pressed\n");
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
        case sfKeyS:
          printf("S pressed\n");
          m_player->cInput->down = true;
          break;
        case sfKeyUp:
          printf("Up Arrow Pressed\n");
          m_player2->cInput->up = true;
          break;
        case sfKeyDown:
          printf("Down Arrow Pressed\n");
          m_player2->cInput->down = true;
          break;
        case sfKeyR:
          printf("Reseting game...\n");
          ResetBall(1);
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
        case sfKeyUp:
          printf("Up Arrow released\n");
          m_player2->cInput->up = false;
          break;
        case sfKeyDown:
          printf("Down Arrow released\n");
          m_player2->cInput->down = false;
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
