#ifndef __MAINROOM_H
#define __MAINROOM_H

#include "room.h"
#include "dungeon-trap/resources.h"
#include "dungeon-trap/character.h"
#include "dungeon-trap/player.h"
#include "dungeon-trap/enemy.h"

class MainRoom : public Room {
private:
  PlayerAI* playerAI;
  Character* player;

  EnemyAI* enemyAI;
  Character* enemy;
  
  void deletePrevious();
public:
  MainRoom();
  ~MainRoom();
  
  void initialize();
  
  void render(SDL_Renderer* renderer);  
  
  bool runGameLoop();
};

#endif
